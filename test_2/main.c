#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Nutne pro isupper a isdigit

// Opravena hlavicka: prijimame char*, ne char**
// Funkce musi neco vracet i kdyz je to spravne (return 1)
int overit_predmet(char *ptr){
    for (int i = 0; i < strlen(ptr); i++){
        if (!isupper(ptr[i])) return 0;
    }
    return 1; // Vsechno OK
}

int overit_login(char *ptr){
    int len = strlen(ptr);
    for (int i = 0; i < 3; i++){
        if (!isupper(ptr[i])) return 0;
    }
    for (int i = 3; i < len; i++){
        if (!isdigit(ptr[i])) return 0;
    }
    return 1; // Vsechno OK
}

typedef struct{
    int id;
    int rok;
    char predmet[50];
    char login[50]; // Zvetseno pro jistotu
    char uloha[100];
    int body;
    int validni;
} Zaznam;

int main(int argc, char *argv[]){
    if (argc != 2) return 1;
    int e = atoi(argv[1]);
    if(e < 0) return 1; // e muze byt 0, ale nesmi byt zaporne

    // Pokud je 0 zaznamu, ukoncime hned (malloc(0) neni bezpecny)
    if (e == 0) {
        printf("Celkem nevalidnich zaznamu: 0\n");
        return 0;
    }

    char buffer[1024]; // 100 znaku je malo, radeji vic
    char *ptr;
    int pocet_nevalidnich = 0;
    
    Zaznam *zaznam = (Zaznam *)malloc(e * sizeof(Zaznam));

    for (int i = 0; i < e; i++){
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
        
        // Odstraneni \n na konci radku bufferu, aby nedelal bordel
        buffer[strcspn(buffer, "\n")] = 0;

        zaznam[i].validni = 1;

        // 1. ID
        ptr = strtok(buffer, ";");
        if (ptr == NULL) { zaznam[i].validni = 0; pocet_nevalidnich++; continue; }
        zaznam[i].id = atoi(ptr);

        // 2. Rok
        ptr = strtok(NULL, ";");
        if (ptr == NULL) { zaznam[i].validni = 0; pocet_nevalidnich++; continue; }
        int r = atoi(ptr); // Prevedeme na cislo
        if (r < 2022 || r > 2024) { // Porovnavame cislo
            zaznam[i].validni = 0; 
            pocet_nevalidnich++; 
            continue; 
        }
        zaznam[i].rok = r;

        // 3. Predmet
        ptr = strtok(NULL, ";");
        if (ptr == NULL) { zaznam[i].validni = 0; pocet_nevalidnich++; continue; }
        // Opraveno strlen(ptr) a pridany zavorky {}
        if (strlen(ptr) < 2 || strlen(ptr) > 8) { 
            zaznam[i].validni = 0; 
            pocet_nevalidnich++; 
            continue; 
        }
        if (overit_predmet(ptr) == 0) { 
            zaznam[i].validni = 0; 
            pocet_nevalidnich++; 
            continue; 
        }        
        strcpy(zaznam[i].predmet, ptr);
        
        // 4. Login
        ptr = strtok(NULL, ";");
        if (ptr == NULL) { zaznam[i].validni = 0; pocet_nevalidnich++; continue; }
        if (strlen(ptr) < 5 || strlen(ptr) > 7) { 
            zaznam[i].validni = 0; 
            pocet_nevalidnich++;
            continue;
        }
        if(overit_login(ptr) == 0) {
            zaznam[i].validni = 0;
            pocet_nevalidnich++;
            continue; 
        }
        strcpy(zaznam[i].login, ptr);

        // 5. Uloha
        ptr = strtok(NULL, ";");
        if (ptr == NULL || strlen(ptr) == 0) { 
            zaznam[i].validni = 0; 
            pocet_nevalidnich++; 
            continue; 
        }        
        strcpy(zaznam[i].uloha, ptr);

        // 6. Body
        ptr = strtok(NULL, "\n");
        if (ptr == NULL) { zaznam[i].validni = 0; pocet_nevalidnich++; continue; }
        zaznam[i].body = atoi(ptr);
    }

    // --- VYPIS 2022 ---
    printf("# Zaznamy roku 2022\n"); // Nadpis musi byt PRED cyklem
    int soucet_zapornych = 0;
    for (int i = 0; i < e; i++){
        if (zaznam[i].validni == 1 && zaznam[i].rok == 2022){
            printf("ID %d: predmet %s, ukol %s, student %s: %db\n", zaznam[i].id, zaznam[i].predmet, zaznam[i].uloha, zaznam[i].login, zaznam[i].body);
            // Scitame pouze zaporne body
            if (zaznam[i].body < 0) {
                soucet_zapornych += zaznam[i].body;
            }
        }
    }
    printf("Pocitadlo rozdanych zapornych bodu (2022): %db\n", soucet_zapornych); // Soucet AZ PO cyklu
    printf("\n");

    // --- VYPIS 2023 ---
    printf("# Zaznamy roku 2023\n");
    soucet_zapornych = 0; // Vynulovat pro dalsi rok
    for (int i = 0; i < e; i++){
        if (zaznam[i].validni == 1 && zaznam[i].rok == 2023){
            printf("ID %d: predmet %s, ukol %s, student %s: %db\n", zaznam[i].id, zaznam[i].predmet, zaznam[i].uloha, zaznam[i].login, zaznam[i].body);
            if (zaznam[i].body < 0) {
                soucet_zapornych += zaznam[i].body;
            }
        }
    }
    printf("Pocitadlo rozdanych zapornych bodu (2023): %db\n", soucet_zapornych);
    printf("\n");

    // --- VYPIS 2024 ---
    printf("# Zaznamy roku 2024\n");
    soucet_zapornych = 0;
    for (int i = 0; i < e; i++){
        if (zaznam[i].validni == 1 && zaznam[i].rok == 2024){
            printf("ID %d: predmet %s, ukol %s, student %s: %db\n", zaznam[i].id, zaznam[i].predmet, zaznam[i].uloha, zaznam[i].login, zaznam[i].body);
            if (zaznam[i].body < 0) {
                soucet_zapornych += zaznam[i].body;
            }
        }
    }
    printf("Pocitadlo rozdanych zapornych bodu (2024): %db\n", soucet_zapornych);
    printf("\n");

    printf("Celkem nevalidnich zaznamu: %d\n", pocet_nevalidnich);

    free(zaznam);
    return 0;
} 