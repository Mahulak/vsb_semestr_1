#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void format_number(int cislo, char *result) {
    char temp[20];
    int len, i, j, pocet;
    
    sprintf(temp, "%d", cislo);
    len = strlen(temp);
    
    int underscores = (len - 1) / 3;
    int result_len = len + underscores;
    
    j = result_len - 1;
    pocet = 0;
    
    for (i = len - 1; i >= 0; i--) {
        result[j--] = temp[i];
        pocet++;
        if (pocet % 3 == 0 && i != 0) result[j--] = '_';
    }    
    result[result_len] = '\0';
}

typedef struct{
    int index_dne;
    char nazev_akcie[20];
    float hodnota_zacatek;
    float hodnota_konec;
    float hodnota_rozdil;
    int pocet_obchodu;
    char v_pocet_obchodu[20];
} Zaznam;

int main(int argc, char *argv[])
{
    if (argc != 3 || argc == 1){        
        printf("Wrong parameters\n");
        exit(1);
    }   

    char *nazev_akcie_param = argv[1];
    int pocet_radku = atoi(argv[2]);
    int h_index_dne = 0;
    char h_nazev_akcie[20];
    float h_hodnota_zacatek = 0;
    float h_hodnota_konec = 0;
    float h_hodnota_rozdil = 0;
    int h_pocet_obchodu = -1;
    char h_v_pocet_obchodu[20];
    if(pocet_radku <= 0 || strlen(nazev_akcie_param) <= 1) exit(1);

    Zaznam *zaznamAkcie = (Zaznam *)malloc(pocet_radku* sizeof(Zaznam));
    
    char radek[101];
    char *p;

    for (int i = 0; i < pocet_radku; i++){
        fgets(radek, sizeof(radek), stdin);
        p = strtok(radek, ",");
        zaznamAkcie[i].index_dne = atoi(p);
        p = strtok(NULL, ",");
        strncpy(zaznamAkcie[i].nazev_akcie, p, sizeof(zaznamAkcie[i].nazev_akcie) - 1);
        zaznamAkcie[i].nazev_akcie[sizeof(zaznamAkcie[i].nazev_akcie) - 1] = '\0';
        p = strtok(NULL, ",");
        zaznamAkcie[i].hodnota_zacatek = atof(p);
        p = strtok(NULL, ",");
        zaznamAkcie[i].hodnota_konec = atof(p);
        zaznamAkcie[i].hodnota_rozdil = zaznamAkcie[i].hodnota_konec - zaznamAkcie[i].hodnota_zacatek;
        p = strtok(NULL, "\n");
        zaznamAkcie[i].pocet_obchodu = atoi(p);
        
        format_number(zaznamAkcie[i].pocet_obchodu, zaznamAkcie[i].v_pocet_obchodu);
        // format_number(zaznamAkcie[i].pocet_obchodu, tmp);
        // strcpy(zaznamAkcie[i].v_pocet_obchodu, tmp);

        if(zaznamAkcie[i].pocet_obchodu > h_pocet_obchodu && strcmp(zaznamAkcie[i].nazev_akcie, nazev_akcie_param) == 0){
            h_index_dne = zaznamAkcie[i].index_dne;            
            strncpy(h_nazev_akcie, zaznamAkcie[i].nazev_akcie, sizeof(h_nazev_akcie) - 1);
            h_nazev_akcie[sizeof(h_nazev_akcie) - 1] = '\0';
            h_hodnota_zacatek = zaznamAkcie[i].hodnota_zacatek;
            h_hodnota_konec = zaznamAkcie[i].hodnota_konec;
            h_hodnota_rozdil = zaznamAkcie[i].hodnota_rozdil;
            h_pocet_obchodu = zaznamAkcie[i].pocet_obchodu;
            format_number(h_pocet_obchodu, h_v_pocet_obchodu);

        }
        
        //printf("%d %s %.2f %.2f %d\n", zaznamAkcie[i].index_dne, zaznamAkcie[i].nazev_akcie, zaznamAkcie[i].hodnota_zacatek, zaznamAkcie[i].hodnota_konec, zaznamAkcie[i].pocet_obchodu);
    }

    printf("<html>\n<body>\n");
    if (h_pocet_obchodu != -1) {
        printf("<div>\n");
        printf("<h1>%s: highest volume</h1>\n", h_nazev_akcie);
        printf("<div>Day: %d</div>\n", h_index_dne);
        printf("<div>Start price: %.2f</div>\n", h_hodnota_zacatek);
        printf("<div>End price: %.2f</div>\n", h_hodnota_konec);
        printf("<div>Volume: %s</div>\n", h_v_pocet_obchodu); 
        printf("</div>\n");        
    } else {
        printf("<div>\n");
        printf("Ticker AMC was not found\n");
        printf("</div>\n");
    }
    printf("<table>\n");
    printf("<thead>\n");
    printf("<tr><th>Day</th><th>Ticker</th><th>Start</th><th>End</th><th>Diff</th><th>Volume</th></tr>\n");
    printf("</thead>\n");
    printf("<tbody>\n");

    for (int i = pocet_radku-1; i >= 0; i--)
    {
        if (strcmp(zaznamAkcie[i].nazev_akcie, nazev_akcie_param) == 0){
            printf("<tr>\n");
            printf("\t<td><b>%d</b></td>\n", zaznamAkcie[i].index_dne);
            printf("\t<td><b>%s</b></td>\n", zaznamAkcie[i].nazev_akcie);
            printf("\t<td><b>%.2f</b></td>\n", zaznamAkcie[i].hodnota_zacatek);
            printf("\t<td><b>%.2f</b></td>\n", zaznamAkcie[i].hodnota_konec);
            printf("\t<td><b>%.2f</b></td>\n", zaznamAkcie[i].hodnota_rozdil);
            printf("\t<td><b>%s</b></td>\n", zaznamAkcie[i].v_pocet_obchodu);
            printf("</tr>\n");
        }
        else{
            printf("<tr>\n");
            printf("\t<td>%d</td>\n", zaznamAkcie[i].index_dne);
            printf("\t<td>%s</td>\n", zaznamAkcie[i].nazev_akcie);
            printf("\t<td>%.2f</td>\n", zaznamAkcie[i].hodnota_zacatek);
            printf("\t<td>%.2f</td>\n", zaznamAkcie[i].hodnota_konec);
            printf("\t<td>%.2f</td>\n", zaznamAkcie[i].hodnota_rozdil);
            printf("\t<td>%s</td>\n", zaznamAkcie[i].v_pocet_obchodu);
            printf("</tr>\n");
        } 
    }
    printf("</tbody>\n");
    printf("</table>\n");
    printf("</body>\n");
    printf("</html>\n");

    //printf("%d. %s\n", pocet_radku, nazev_akcie_param);
    //printf("%s", h_nazev_akcie);
    free(zaznamAkcie);
    return 0;
}