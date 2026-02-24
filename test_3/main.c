#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int velka_pismena(char *buffer){
    for (int i = 0; i < strlen(buffer); i++)
    {
       if (islower(buffer[i])) return 1;
    }   
}

int main(int argc, char *argv[]) {
    int rozmer = atoi(argv[1]);
    int pocet_slov = atoi(argv[2]);

    char *krizovka = (char *)malloc(rozmer * rozmer * sizeof(char));
    int *maska = (int *)malloc(rozmer * rozmer * sizeof(int));

    // Ruční vynulování masky (náhrada za calloc)
    for (int i = 0; i < rozmer * rozmer; i++) {
        maska[i] = 0;
    }

    char buffer[128];
    for (int i = 0; i < rozmer; i++) {
        if (fgets(buffer, sizeof(buffer), stdin)) { //pisu cely radek
            if (velka_pismena(buffer) == 1) return 1;
            for (int j = 0; j < rozmer; j++) {
                krizovka[i * rozmer + j] = buffer[j];
            }
        }
    }
    printf("Krizovka nactena.\n");
    

    // 4. Načítání slov a jejich vyhledávání
    for (int i = 0; i < pocet_slov; i++) {
        if (fgets(buffer, sizeof(buffer), stdin)) {
            // Odstranění znaku odřádkování (\n)
            buffer[strcspn(buffer, "\n")] = '\0';
            int delka = strlen(buffer);
            if (delka == 0) continue;

            // HLEDÁNÍ HORIZONTÁLNĚ (zleva doprava)
            for (int r = 0; r < rozmer; r++) {
                // Hledáme, kde by slovo mohlo začínat (musí se vejít do řádku)
                for (int s = 0; s <= rozmer - delka; s++) {
                    int shoda = 1;
                    for (int k = 0; k < delka; k++) {
                        if (krizovka[r * rozmer + (s + k)] != buffer[k]) {
                            shoda = 0;
                            break;
                        }
                    }
                    // Pokud slovo odpovídá, označíme pozice v masce
                    if (shoda) {
                        for (int k = 0; k < delka; k++) {
                            maska[r * rozmer + (s + k)] = 1;
                        }
                    }
                }
            }

            // HLEDÁNÍ VERTIKÁLNĚ (shora dolů)
            for (int s = 0; s < rozmer; s++) {
                // Hledáme, kde by slovo mohlo začínat (musí se vejít do sloupce)
                for (int r = 0; r <= rozmer - delka; r++) {
                    int shoda = 1;
                    for (int k = 0; k < delka; k++) {
                        if (krizovka[(r + k) * rozmer + s] != buffer[k]) {
                            shoda = 0;
                            break;
                        }
                    }
                    // Pokud slovo odpovídá, označíme pozice v masce
                    if (shoda) {
                        for (int k = 0; k < delka; k++) {
                            maska[(r + k) * rozmer + s] = 1;
                        }
                    }
                }
            }
        }
    }

    // 5. Výpis tajenky
    for (int i = 0; i < rozmer * rozmer; i++) {
        if (maska[i] == 0) {
            putchar(krizovka[i]);
        }
    }
    printf("\n");

    // 6. Uvolnění paměti
    free(krizovka);
    free(maska);

    return 0;
}