#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tga.h"

int rozdil_dvou_pixelu(Pixel p1, Pixel p2) {
    return abs(p1.red - p2.red) + abs(p1.green - p2.green) + abs(p1.blue - p2.blue); //abs = absolutni hodnota
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    char *input_file = NULL;
    int input_file_c = 0;

    char *output_file = NULL;
    int output_file_c = 0;

    int block_size;
    int block_size_c = 0;

    int max_diff;
    int max_diff_c = 0;

//KOMPRESE-------------------------------------------------------------------------------------------------
    if (strcmp(argv[1], "compress") == 0) {
        //VSTUPY-------------------------------------------------------------------------------------------------
        for (int i = 2; i < argc; i++)
        {
            // INPUT
            if(strcmp(argv[i], "--input") == 0) {
                if (input_file_c == 1 || i + 1 >= argc) return 1;
                input_file = argv[i + 1];
                input_file_c = 1;
                i++;
                continue;
            }
            
            // OUTPUT
            if(strcmp(argv[i], "--output") == 0) {
                if (output_file_c == 1 || i + 1 >= argc) return 1;
                output_file = argv[i + 1];
                output_file_c = 1;
                i++;
                continue;
            }

            // BLOCK SIZE
            if(strcmp(argv[i], "--block-size") == 0) {
                if (block_size_c == 1 || i + 1 >= argc) return 1;
                block_size = atoi(argv[i + 1]);
                block_size_c = 1;
                i++;
                continue;
            }

            // MAX DIFF
            if(strcmp(argv[i], "--max-diff") == 0) {
                if (max_diff_c == 1 || i + 1 >= argc) return 1;
                max_diff = atoi(argv[i + 1]);
                max_diff_c = 1;
                i++;
                continue;
            }
            return 1;
        }
        if (input_file_c == 0 || output_file_c == 0 || block_size_c == 0 || max_diff_c == 0) return 1;

        //LOGIKA-------------------------------------------------------------------------------------------------

        int width, height;
        if (check_tga_header(input_file, block_size, &width, &height) != 0) {
            return 1;
        }

        Pixel *pixels = load_tga_pixels(input_file, width, height);

        FILE *f_o = fopen(output_file, "wb"); //otevreme file pro zapis po bytech

        word width_short = (word)width; //ma to 2byty bo je to short
        word height_short = (word)height;
        word block_size_short = (word)block_size;
        
        fwrite(&width_short, 2, 1, f_o); //odkud bereme / velikost 2 bo to jsou ty 2 byty word / zapsat 1 / kam to dat
        fwrite(&height_short, 2, 1, f_o); // --||--
        fwrite(&block_size_short, 2, 1, f_o); // --||--

        int velikost_komprese = 6; //2Byty sirka + 2B vyska + 2Byty velikost bloku = 6Bytu

        for (int i = 0; i < height; i = i + block_size) {
            for (int j = 0; j < width; j = j + block_size) {
                Pixel sekvencni_pixel;
                int delka = 0;
                int prvni_v_bloku = 1;

                for (int y = i; y < i + block_size; y++) {
                    for (int x = j; x < j + block_size; x++) {

                        Pixel aktualni_pixel = pixels[y * width + x]; //prvni pixel index 0

                        if (prvni_v_bloku) {
                            sekvencni_pixel = aktualni_pixel;
                            delka = 1;
                            prvni_v_bloku = 0;
                        } else {
                            int rozdil = rozdil_dvou_pixelu(aktualni_pixel, sekvencni_pixel);

                            if (rozdil <= max_diff && delka < 255) {
                                delka++;
                            } else {
                                fwrite(&sekvencni_pixel, sizeof(Pixel), 1, f_o);
                                fwrite(&delka, 1, 1, f_o);
                                velikost_komprese += 4; //3byty (sizeof(Pixel)) + 1byte delka = 4Bytu

                                sekvencni_pixel = aktualni_pixel;
                                delka = 1;
                            }
                        }
                    }
                }
                fwrite(&sekvencni_pixel, sizeof(Pixel), 1, f_o);
                fwrite(&delka, 1, 1, f_o);
                velikost_komprese += 4; //3byty (sizeof(Pixel)) + 1byte delka = 4
            }
        }
        fclose(f_o);

        //STATY-------------------------------------------------------------------------------------------------
        int input_file_velikost = width * height * 3; // Velikost obrazku (input_file) * 3(barvy RGB)
        float pomer_kompresse_procenta = ((float)velikost_komprese / (float)input_file_velikost) * 100.0f; //bo je to zaokrouhlene na 1 deset. misto
        printf("Statistiky komprese:\n");
        printf("Puvodni velikost: %d bytu\n", input_file_velikost);
        printf("Velikost po kompresi: %d bytu\n", velikost_komprese);
        printf("Pomer komprese v procentech: %.1f procent\n", pomer_kompresse_procenta); // %.0f zaokrouhli na cele cislo
        free(pixels);

//DEKOMPRESE-------------------------------------------------------------------------------------------------

    }
    else if (strcmp(argv[1], "decompress") == 0){
        //VSTUPY-------------------------------------------------------------------------------------------------
        for (int i = 2; i < argc; i++)
        {
            // INPUT
            if(strcmp(argv[i], "--input") == 0) {
                if (input_file_c == 1 || i + 1 >= argc) return 1;
                input_file = argv[i + 1];
                input_file_c = 1;
                i++;
                continue;
            }
            // OUTPUT
            if(strcmp(argv[i], "--output") == 0) {
                if (output_file_c == 1 || i + 1 >= argc) return 1;
                output_file = argv[i + 1];
                output_file_c = 1;
                i++;
                continue;
            }
            return 1;
        }  
        if (input_file_c == 0 || output_file_c == 0) return 1;

        //LOGIKA-------------------------------------------------------------------------------------------------
        FILE *f_in = fopen(input_file, "rb");
        if (f_in == NULL) return 1;

        word width_short;
        word height_short;
        word block_size_short;

        fread(&width_short, 2, 1, f_in);
        fread(&height_short, 2, 1, f_in);
        fread(&block_size_short, 2, 1, f_in);
        
        int width = (int)width_short;
        int height = (int)height_short;
        int block_size = (int)block_size_short;

        Pixel *pixels = (Pixel*)malloc(sizeof(Pixel) * width * height);

        for (int i = 0; i < height; i = i + block_size) {
            for (int j = 0; j < width; j = j + block_size) {
                
                int nacteno_pixelu_v_bloku = 0;
                int celkem_pixelu_v_bloku = block_size * block_size;

                while (nacteno_pixelu_v_bloku < celkem_pixelu_v_bloku) {
                    Pixel barva;
                    byte delka; //stejna jako u kompresi

                    fread(&barva, sizeof(Pixel), 1, f_in);
                    fread(&delka, 1, 1, f_in);

                    for (int k = 0; k < delka; k++) {
                        int radek = nacteno_pixelu_v_bloku / block_size; // Radek v ramci bloku
                        int sloupec = nacteno_pixelu_v_bloku % block_size; // Sloupec v ramci bloku

                        int radek_obrazek = i + radek; // Radek v ramci celeho obrazku
                        int sloupec_obrazek = j + sloupec; // Sloupec v ramci celeho obrazku

                        pixels[radek_obrazek * width + sloupec_obrazek] = barva; // ulozeni barvy do konkretni souradinice pixelu
                        nacteno_pixelu_v_bloku++;
                    }
                }
            }
        }
        fclose(f_in);

        FILE *f_out = fopen(output_file, "wb");
        TGAHeader header = {0}; // pro jistotu nastavime vsechny byty na 0 aby nedoslo k nahodnym hodnotam
        
        header.image_type = 2; // 2 = RGB obrazek
        header.depth = 24; // 3 * 8 bitu = 24 bitu na pixel
        header.descriptor = 32; //Obrazek zacina vlevo nahore, aby nebyl vzhuru nohama
        header.width[0] = width % 256; //stejne jak u zjistovani vysky a sirky obrazku... metoda pomoci krabicek[0]
        header.width[1] = width / 256;
        header.height[0] = height % 256;
        header.height[1] = height / 256;

        fwrite(&header, sizeof(TGAHeader), 1, f_out); //Nejdřív zapíšeme hlavičku (těch 18 bytů s informacemi o rozměrech)
        fwrite(pixels, sizeof(Pixel), width * height, f_out); //??

        fclose(f_out);
        free(pixels);

        printf("Dekomprese hotova!");
    }    
    else return 1;
    
    return 0;
}