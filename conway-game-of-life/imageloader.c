#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

// Opens a .ppm P3 image file, and constructs an Image object. 
Image* readData(char* filename) 
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        exit(-1);
    }

    char format[3];
    uint32_t cols, rows, scale;
    fscanf(fp, "%s %u %u %u", format, &cols, &rows, &scale);

    Image* img = (Image*) malloc(sizeof(Image));
    img->cols = cols;
    img->rows = rows;
    img->image = (Color**) malloc(rows * sizeof(Color*));
    for (uint32_t i = 0; i < rows; i++) {
        img->image[i] = (Color*) malloc(cols * sizeof(Color));
        for (uint32_t j = 0; j < cols; j++) {
            fscanf(fp, "%hhu %hhu %hhu", &img->image[i][j].R, &img->image[i][j].G, &img->image[i][j].B);
        }
    }

    fclose(fp);

    return img;
}

// Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image* image)
{
    uint32_t cols = image->cols;
    uint32_t rows = image->rows;
    Color** colors = image->image;

    printf("P3\n");
    printf("%u %u\n", cols, rows);
    printf("255\n");
    for (uint32_t i = 0; i < rows; i++) {
        for (uint32_t j = 0; j < cols - 1; j++) {
            printf("%3u %3u %3u   ", colors[i][j].R, colors[i][j].G, colors[i][j].B);
        }
        printf("%3u %3u %3u", colors[i][cols - 1].R, colors[i][cols - 1].G, colors[i][cols - 1].B);
        printf("\n");
    }
}

// Frees an image
void freeImage(Image* image)
{
    uint32_t rows = image->rows;	
    Color** colors = image->image;
    for (uint32_t i = 0; i < rows; i++) {
        free(colors[i]);
    }
    free(colors);
    free(image);
}
