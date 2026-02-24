#ifndef TGA_H
#define TGA_H

#include <stdio.h>

typedef unsigned char byte; //1 byte
typedef unsigned short word; //2 byty

typedef struct{
    byte blue;
    byte green;
    byte red;
} Pixel;

typedef struct {
    byte id_length;
    byte color_map_type;
    byte image_type;
    byte color_map[5];
    byte x_origin[2];
    byte y_origin[2];
    byte width[2];
    byte height[2];
    byte depth;
    byte descriptor;
} TGAHeader;

int check_tga_header(const char *filename, int block_size, int *width_druha, int *height_druha);

Pixel* load_tga_pixels(const char *filename, int width, int height);

#endif