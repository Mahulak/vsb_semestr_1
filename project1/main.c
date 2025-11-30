#include <stdio.h>

int main() {
    
    int castka = 14820;
    int ban5000 = 0;
    int ban2000 = 0;
    int ban1000 = 0;
    int ban500 = 0;
    int ban200 = 0;
    int ban100 = 0;

    printf("Puvodni castka: %d\n", castka);

    while(castka >= 100)
    {
        if (castka >= 5000)
        {
            castka = castka - 5000;
            ban5000 = ban5000 + 1;
        }
        else if(castka >= 2000)
        {
            castka = castka - 2000;
            ban2000 = ban2000 + 1;
        }
        else if(castka >= 1000)
        {
            castka = castka - 1000;
            ban1000 = ban1000 + 1;
        }
        else if(castka >= 500)
        {
            castka = castka - 500;
            ban500 = ban500 + 1;
        }
        else if (castka >= 200)
        {
            castka = castka - 200;
            ban200 = ban200 + 1;
        }
        else if(castka >= 100)
        {
            castka = castka - 100;
            ban100 = ban100 + 1;
        }    
    }
    printf("Bankovka 5000: %dx\nBankovka 2000: %dx\nBankovka 1000: %dx\nBankovka 500: %dx\nBankovka 200: %dx\nBankovka 100: %dx\n", ban5000, ban2000, ban1000, ban500, ban200, ban100);
    printf("Zbyva: %d\n", castka);

    return 0;
}