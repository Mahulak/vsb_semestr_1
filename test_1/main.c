#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    char slovo[50];
    int skore;
    int pocet;
} Token;

int main(int argc, char *argv[]){
    if (argc != 2) return 1;
    
    int t = atoi(argv[1]);
    if(t < 0) return 1;

    Token *token = NULL;
    if (t > 0) {
        token = (Token *)malloc(t * sizeof(Token));
    }

    // --- 1. Otevření souboru pro ZÁPIS ("w" = write) ---
    // Pokud soubor neexistuje, vytvoří se.
    const char *nazev_souboru = "vystup.txt";
    FILE *f = fopen(nazev_souboru, "w");
    
    if (f == NULL) {
        // Kdyby se nepovedlo vytvorit soubor (napr. prava zapisu)
        if (token != NULL) free(token);
        return 1;
    }

    char buffer[1024];
    char *ptr;

    // Načtení tokenů ze vstupu
    for (int i = 0; i < t; i++){
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
        buffer[strcspn(buffer, "\n")] = 0;

        ptr = strtok(buffer, ",");
        if (ptr != NULL) strcpy(token[i].slovo, ptr);
        
        ptr = strtok(NULL, "\n");
        if (ptr != NULL) token[i].skore = atoi(ptr);
        
        token[i].pocet = 0;
    }

    int cislo_dopisu = 0;
    int dopis_probiha = 0;

    // Čtení dopisů
    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {   
        if(strncmp(buffer, "---", 3) == 0){
            if (dopis_probiha == 0){
                dopis_probiha = 1;
                cislo_dopisu++;
            }
            else {
                // --- KONEC DOPISU ---
                // Zapisujeme do souboru 'f' misto na obrazovku
                fprintf(f, "Letter #%d\n", cislo_dopisu);
                
                int total_skore = 0;
                for (int i = 0; i < t; i++)
                {
                    if (token[i].pocet > 0)
                    {
                        int akt_skore = token[i].skore * token[i].pocet;
                        fprintf(f, "Token '%s': %d occurrences, AI score: %d\n", token[i].slovo, token[i].pocet, akt_skore);
                        total_skore += akt_skore;
                        
                        token[i].pocet = 0; 
                    }
                }
                fprintf(f, "Total AI score: %d\n", total_skore);
                fprintf(f, "\n"); 
                
                dopis_probiha = 0;
            }
            continue; 
        }

        if (dopis_probiha == 1) {
            // Rozsekání řádku (pozor na tu mezeru v uvozovkách!)
            char *slovo_na_radku = strtok(buffer, " .,!?\n");
            
            while (slovo_na_radku != NULL) {
                for (int i = 0; i < t; i++){
                    // Porovnáváme celá slova
                    if (strcmp(slovo_na_radku, token[i].slovo) == 0) {
                        token[i].pocet++;
                    }
                }
                slovo_na_radku = strtok(NULL, " .,!?\n");
            }
        }
    }

    // DŮLEŽITÉ: Zavřeme soubor, aby se data fyzicky uložila na disk
    fclose(f);

    // --- 2. Otevření souboru pro ČTENÍ ("r" = read) ---
    f = fopen(nazev_souboru, "r");
    if (f != NULL) {
        // Čteme po řádcích do bufferu, dokud to jde
        while (fgets(buffer, sizeof(buffer), f) != NULL) {
            printf("%s", buffer); // Vytiskneme načtený řádek
        }
        fclose(f);
        
        remove(nazev_souboru);
    }

    if (token != NULL) free(token);
    return 0;
}
