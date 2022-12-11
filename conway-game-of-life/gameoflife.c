#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

int dirs[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1}, {0, 1},
    {1, -1}, {1, 0}, {1, 1}
};

int check_if_index_valid(Image* image, int row, int col) {
    if (row >= 0 && row < image->rows && col >= 0 && col < image->cols) {
        return 1;
    }
    return 0;
}

void process_bits(uint8_t bits, uint8_t* cnts) {
    for (uint32_t i = 0; i < 8; i++) {
        cnts[i] += (bits >> i) & 1;
    }
}

uint8_t get_color(uint8_t v,  uint8_t* cnts, uint32_t rule) {
    uint8_t new_v = 0;
    for (uint32_t i = 0; i < 8; i++) {
        uint32_t cur_rule = rule;
        if (((v >> i) & 1) == 1) {
            cur_rule >>= 9;
        }
        if ((cur_rule & (1 << cnts[i])) != 0) {
            new_v = new_v | (1 << i);
        }
    }
    return new_v;
}

// Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
// Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
// and the left column as adjacent to the right column.
Color* evaluateOneCell(Image* image, int row, int col, uint32_t rule)
{
	Color* processed = (Color*) malloc(sizeof(Color));

    uint8_t r_cnts[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t g_cnts[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t b_cnts[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    for (uint32_t i = 0; i < 8; i++) {
        int cur_row = row + dirs[i][0];
        int cur_col = col + dirs[i][1];

        if (check_if_index_valid(image, cur_row, cur_col)) {
            process_bits(image->image[cur_row][cur_col].R, r_cnts);
            process_bits(image->image[cur_row][cur_col].G, g_cnts);
            process_bits(image->image[cur_row][cur_col].B, b_cnts); 
        }
    }

    processed->R = get_color(image->image[row][col].R, r_cnts, rule);
    processed->G = get_color(image->image[row][col].G, g_cnts, rule);
    processed->B = get_color(image->image[row][col].B, b_cnts, rule);

    return processed;
}

// The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
// You should be able to copy most of this from steganography.c
Image* life(Image* image, uint32_t rule)
{
    uint32_t rows = image->rows;
    uint32_t cols = image->cols;

    Image* processed = malloc(sizeof(Image));
    processed->rows = rows;
    processed->cols = cols;
    processed->image = malloc(rows * sizeof(Image*));
    for (uint32_t i = 0; i < rows; i++) {
        processed->image[i] = malloc(cols * sizeof(Image));
        for (uint32_t j = 0; j < cols; j++) {
            Color* processed_color = evaluateOneCell(image, i, j, rule);
            processed->image[i][j] = *processed_color;
            free(processed_color);
        }
    }

    return processed;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char** argv)
{
    if (argc != 3) {
        printf("usage: ./gameOfLife filename rule\n");
        printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
        printf("rule is a hex number beginning with 0x; Life is 0x1808.\n");
        exit(-1);
    }

    Image* image = readData(argv[1]);
    uint32_t rule = strtol(argv[2], NULL, 16);
    Image* processed = life(image, rule);
    writeData(processed);
    freeImage(image);
    freeImage(processed);
}
