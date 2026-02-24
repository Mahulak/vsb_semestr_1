#include <stdio.h>
#include <stdlib.h>
#include "tga.h"

int check_tga_header(const char *filename, int block_size, int *width_druha, int *height_druha) {
    FILE *f_in = fopen(filename, "rb"); //read binary

    TGAHeader header;
    if (fread(&header, sizeof(TGAHeader), 1, f_in) != 1) {
        fclose(f_in);
        return 1;
    }

    int width = header.width[0] + (header.width[1] * 256); //vzorec (krabicka[0] + krabicka[1]*256)
    int height = header.height[0] + (header.height[1] * 256);

    *width_druha = width; //priradit hodnoty na vystup
    *height_druha = height;

    if (header.depth != 24) {
        fclose(f_in);
        return 1;
    }
    if (width % block_size != 0 || height % block_size != 0) { //zjisteni zda obrazek se da rozdelit do konretnich bloku
        fclose(f_in);
        return 1;
    }

    fclose(f_in);
    return 0;
}

Pixel* load_tga_pixels(const char *filename, int width, int height) {
    FILE *f = fopen(filename, "rb");
    if (!f) return NULL;
    fseek(f, sizeof(TGAHeader), SEEK_SET); //jelikoz file otevirame znovu tak zaciname zase na pozici 0 takze musime preskocit vsech tech 18 ci vice bytu

    Pixel *data = (Pixel*)malloc(sizeof(Pixel) * width * height);
    fread(data, sizeof(Pixel), width * height, f);

    fclose(f);
    return data;
}