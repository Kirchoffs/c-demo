#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

// Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color* evaluateOnePixel(Image* image, int row, int col)
{
    if (row < 0 || col < 0 || row >= image->rows || col >= image->cols) {
        exit(-1);
    }

    Color raw = image->image[row][col];
    Color* processed = (Color*) malloc(sizeof(Color));
    if ((raw.B & 1) == 1) {
        processed->R = 255;
        processed->G = 255;
        processed->B = 255;
    } else {
        processed->R = 0;
        processed->G = 0;
        processed->B = 0;	
    }

    return processed;
}

// Given an image, creates a new image extracting the LSB of the B channel.
Image* steganography(Image* image)
{
    uint32_t row = image->rows;
    uint32_t col = image->cols;
	
    Image* processed = (Image*) malloc(sizeof(Image));
    processed->rows = row;
    processed->cols = col;
    processed->image = (Color**) malloc(row * sizeof(Color*));
    for (uint32_t i = 0; i < row; i++) {
        processed->image[i] = (Color*) malloc(col * sizeof(Color));
        for (uint32_t j = 0; j < col; j++) {
            Color* processed_color = evaluateOnePixel(image, i, j);
            processed->image[i][j] = *processed_color;
            free(processed_color);
        }
    }

    return processed;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning.
*/
int main(int argc, char** argv)
{
	if (argc != 2) {
        exit(-1);
    }

    Image* image = readData(argv[1]);
    Image* processed = steganography(image);
    writeData(processed);

    freeImage(image);
    freeImage(processed);
}
