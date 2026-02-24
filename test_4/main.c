#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktura pro ingredienci ve skladu
typedef struct {
    char nazev[101];
    int pocet;
} Ingredience;

int main(int argc, char *argv[]) {
    // 1. Parametry příkazové řádky
    int n_ingredience = atoi(argv[1]);
    int n_recepty = atoi(argv[2]);

    // 2. Alokace skladu ingrediencí
    Ingredience *sklad = (Ingredience *)malloc(n_ingredience * sizeof(Ingredience));

    char buffer[256]; // Buffer pro čtení řádků

    // 3. Načtení skladu ingrediencí
    for (int i = 0; i < n_ingredience; i++) {
        if (fgets(buffer, sizeof(buffer), stdin)) {
            // Rozdělení podle čárky: Název,Počet
            char *jmeno = strtok(buffer, ",");
            char *pocet_str = strtok(NULL, "\n");
            
            if (jmeno && pocet_str) {
                strcpy(sklad[i].nazev, jmeno);
                sklad[i].pocet = atoi(pocet_str);
            }
        }
    }

    int nejlepsi_index = -1;
    int max_porci = -1;

    // 4. Zpracování receptů
    for (int r = 0; r < n_recepty; r++) {
        if (fgets(buffer, sizeof(buffer), stdin)) {
            // První část receptu: počet druhů ingrediencí;
            char *ptr = strtok(buffer, ";");
            if (!ptr) continue;
            int druhu_v_receptu = atoi(ptr);

            int porci_tohoto_receptu = 2147483647; // Nastavíme na velké číslo (INT_MAX)

            for (int i = 0; i < druhu_v_receptu; i++) {
                char *ingr_jmeno = strtok(NULL, ",");
                char *ingr_potreba_str = strtok(NULL, ";\n"); // Oddělovač může být ; nebo konec řádku

                if (ingr_jmeno && ingr_potreba_str) {
                    int potreba = atoi(ingr_potreba_str);
                    int nalezeno = 0;
                    int dostupne_mnozstvi = 0;

                    // Najdeme ingredienci ve skladu
                    for (int j = 0; j < n_ingredience; j++) {
                        if (strcmp(sklad[j].nazev, ingr_jmeno) == 0) {
                            dostupne_mnozstvi = sklad[j].pocet;
                            nalezeno = 1;
                            break;
                        }
                    }

                    // Výpočet porcí pro tuto konkrétní ingredienci
                    int moznych_porci = 0;
                    if (nalezeno) {
                        moznych_porci = dostupne_mnozstvi / potreba;
                    } else {
                        moznych_porci = 0; // Ingredience vůbec není ve skladu
                    }

                    // Celkový počet porcí receptu je dán jeho NEJSLABŠÍ ingrediencí (minimum)
                    if (moznych_porci < porci_tohoto_receptu) {
                        porci_tohoto_receptu = moznych_porci;
                    }
                }
            }

            // Pokud jsme nenašli žádnou ingredienci, porce jsou 0
            if (porci_tohoto_receptu == 2147483647) porci_tohoto_receptu = 0;

            // Hledáme globálně nejlepší recept
            if (porci_tohoto_receptu > max_porci) {
                max_porci = porci_tohoto_receptu;
                nejlepsi_index = r + 1; // Indexy jsou od 1
            }
        }
    }

    // 5. Výpis výsledku
    if (nejlepsi_index != -1 && max_porci > 0) {
        printf("Recept %d lze uvarit %dx\n", nejlepsi_index, max_porci);
    } else {
        printf("Zadny recept nelze uvarit :(\n");
    }

    // 6. Uvolnění paměti
    free(sklad);

    return 0;
}