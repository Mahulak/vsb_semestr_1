#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef unsigned char byte;

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
} /*__attribute__((packed))*/TGAHeader;

typedef struct {
    byte blue;
    byte green;
    byte red;
} Pixel;

typedef struct {
    int width, height;
    TGAHeader header;
    Pixel *data;
} TGAImage;
//--------------------------------------------------------------------------------------------------------------------
void free_tga(TGAImage *img){
    if (img){
        if (img->data != NULL){
            free(img->data);
        }
        free(img);
    }
}

TGAImage* load_tga(char *filename){
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;
    
    TGAImage *img = (TGAImage*)malloc(sizeof(TGAImage));
    fread(&img->header, sizeof(TGAHeader), 1, file);

    img->width = 0;
    img->height = 0;
    memcpy(&img->width, img->header.width, 2);
    memcpy(&img->height, img->header.height, 2);

    int pixel_count = img->width * img->height;    
    img->data = (Pixel*)malloc(sizeof(Pixel) * pixel_count);
    fread(img->data, sizeof(Pixel), pixel_count, file);

    fclose(file);
    return img;
}

int save_tga(const char *filename, TGAImage *img) {
    FILE *file = fopen(filename, "wb");

    fwrite(&img->header, sizeof(TGAHeader), 1, file);
    fwrite(img->data, sizeof(Pixel), img->width * img->height, file);

    fclose(file);
    return 1;
}

void draw_char(TGAImage *img, TGAImage *pismeno, int start_x, int start_y) { //vypisovani pismen na obrazek
    for (int i = 0; i < pismeno->height; i++) {
        for (int j = 0; j < pismeno->width; j++) {
            Pixel p = pismeno->data[i * pismeno->width + j]; //prevod 2D souřadnic na 1D pole.
            if (p.red != 0 || p.green != 0 || p.blue != 0) img->data[(start_y + i) * img->width + (start_x + j)] = p; //kresleni pismena na obrazek, pokud neni pixel cerny
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
    if (argc != 4){
        printf("Wrong parameters\n");
        exit(1);
    }

    char *input_path = argv[1];
    char *fonts_dir = argv[3];

    TGAImage *fonts[26];
    char font_path[1000];

    TGAImage *input_img = load_tga(input_path);
    if (input_img == NULL){
        printf("Could not load image\n");
        exit(1);
    }

    for (int i = 0; i < 26; i++){
        char pismeno = 'A'+ i;
        snprintf(font_path, sizeof(font_path), "%s/%c.tga", fonts_dir, pismeno);

        fonts[i] = load_tga(font_path);
        if (!fonts[i]) {
            free_tga(input_img);
            for (int j = 0; j < i; j++) {
                free_tga(fonts[j]); //odstraneni jiz nactenych fontu
            }
            exit(1);
        }
    }

    int top, bottom;
    scanf("%d %d", &top, &bottom);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    int dohromady_radku = top + bottom;

    char buff_radky_pismena[20][101]; //radky / pismena
    for (int i = 0; i < dohromady_radku; i++){
        fgets(buff_radky_pismena[i], 101, stdin);
    }   

    //prevedeni malych pismen na velka a odstraneni nepovoleny znaku
    for (int i = 0; i < dohromady_radku; i++){
        int zapis = 0;
        for (int j = 0; buff_radky_pismena[i][j] != '\0'; j++){
            char znak = buff_radky_pismena[i][j];

            if (znak >= 'a' && znak <= 'z'){
                buff_radky_pismena[i][zapis] = toupper(znak);
                zapis++;
            }
            else if((znak >= 'A' && znak <= 'Z') || znak == ' '){
                buff_radky_pismena[i][zapis] = znak;
                zapis++;
            }
        }
        buff_radky_pismena[i][zapis] = '\0';        
    }
//--------------------------------------------------------------------------------------------------------------------   
    int pozice_y = 10;
    int char_width = 20;
    int char_height = 34;
    int line_spacing = 5;
    
    //nahore radky
    for (int i = 0; i < top && i < dohromady_radku; i++) {
        int delka_radku = strlen(buff_radky_pismena[i]);        
        int pozice_x = (input_img->width - (delka_radku * char_width)) / 2; //tam kde zacnu vypisovat radky pismeno po pismenu

        for (int j = 0; buff_radky_pismena[i][j] != '\0'; j++) {
            if(buff_radky_pismena[i][j] != ' ') draw_char(input_img, fonts[buff_radky_pismena[i][j] - 65], pozice_x, pozice_y); //65 ascii hodnota znaku 'A'
            pozice_x += char_width;
        }
        pozice_y += char_height + line_spacing;
    }

    //dole radky
    int bottom_height_needed = bottom * (char_height + line_spacing);
    pozice_y = input_img->height - bottom_height_needed - 10;

    for (int i = top; i < dohromady_radku; i++) {        
        int delka_radku = strlen(buff_radky_pismena[i]);
        int pozice_x = (input_img->width - (delka_radku * char_width)) / 2; //tam kde zacnu vypisovat radky pismeno po pismenu

        for (int j = 0; buff_radky_pismena[i][j] != '\0'; j++) {
            if(buff_radky_pismena[i][j] != ' ') draw_char(input_img, fonts[buff_radky_pismena[i][j] - 65], pozice_x, pozice_y);
            pozice_x += char_width;
        }
        pozice_y += char_height + line_spacing;
    }
//--------------------------------------------------------------------------------------------------------------------
    save_tga(argv[2], input_img);
    for (int i = 0; i < 26; i++) {
        free_tga(fonts[i]);
    }
    free_tga(input_img);
    return 0;
}