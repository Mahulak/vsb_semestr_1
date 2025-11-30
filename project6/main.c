#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int vrat_pocet_mezer_v_retezci(char *retezec)
{
    int pocet = 0;

    for (int j = 0; j < (int)strlen(retezec); j++)
    {
        if (retezec[j] == ' ') pocet++;
    }
    return pocet;
}

int vrat_pocet_malych_pismen_v_retezci(char *retezec)
{
    int pocet = 0;

    for (int j = 0; j < (int)strlen(retezec); j++)
    {
        if ((int)retezec[j] >= 97) pocet++;
    }
    return pocet;
}

int vrat_pocet_velkych_pismen_v_retezci(char *retezec)
{
    int pocet = 0;

    for (int j = 0; j < (int)strlen(retezec); j++)
    {
        if ((int)retezec[j] >= 65 && (int)retezec[j] <= 90) pocet++;
    }
    return pocet;
}

int main ()
{
    int pocet_radku;

    char n[10];
    fgets(n, sizeof n, stdin);
    pocet_radku = atoi(n);
    // printf("%d\n", pocet_radku);

    char *slovo;
    int pocet_slov = 0; 
    int pocet_mezer = 0;
    int pocet_mezer_po = 0;
    int lower_case_pred = 0;
    int lower_case_po = 0; 
    int upper_case_pred = 0;
    int upper_case_po = 0;

    // char radek[pocet_radku][52];
    char radek[500][51];

    for (int x = 0; x < pocet_radku; x++)
    {
        fgets(radek[x], sizeof(radek[x]), stdin);
    }

    for (int i = 0; i < pocet_radku; i++)
    {
        pocet_slov = 0;
        lower_case_po = 0;
        upper_case_po = 0;
        pocet_mezer = 0;
        pocet_mezer_po = 0;

        lower_case_pred = vrat_pocet_malych_pismen_v_retezci(radek[i]);
        upper_case_pred = vrat_pocet_velkych_pismen_v_retezci(radek[i]);
        pocet_mezer = vrat_pocet_mezer_v_retezci(radek[i]);

        // printf("\nprvni slovo: %s\n", slovo);
        // printf("pozice: %d\n", strcspn(radek[i], "\n"));
        radek[i][strcspn(radek[i], "\n")] = 0;
        slovo = strtok(radek[i], " ");

        while (slovo != NULL) {
            pocet_slov++;

            // printf("%s", slovo);

            /* znema velka mala */
            int jeVelke = 0;
            for (int j = 0; j < (int)strlen(slovo); j++)
            {
                if ((int)slovo[j] < 97)
                {
                    jeVelke = 1;
                    break;
                }
            }

            if (jeVelke == 1)
            {
                for (int j = 0; j < (int)strlen(slovo); j++) 
                {
                    if (j == 0) {
                        slovo[j] = toupper(slovo[j]); 
                    } 
                    else 
                    {
                        slovo[j] = tolower(slovo[j]);
                    }
                }
            } 
            else 
            {
                for (int j = 0; j < (int)strlen(slovo); j++)
                {
                    slovo[j] = toupper(slovo[j]); 
                }
            }

            /* redukce opakovani */
            int a = 0;
            char slovo_po[51];
            for (int j = 0; j < (int)strlen(slovo); j++)
            {
                if (slovo[j+1] != slovo[j])
                {
                    slovo_po[a++] = slovo[j];
                }
            }
            slovo_po[a] = 0;
            slovo = slovo_po;

            lower_case_po += vrat_pocet_malych_pismen_v_retezci(slovo);
            upper_case_po += vrat_pocet_velkych_pismen_v_retezci(slovo);

            if (pocet_slov != 1)
            {
                printf(" %s", slovo);
                pocet_mezer_po++;
            }
            else printf("%s", slovo);

            slovo = strtok(NULL, " ");           
        }
        printf("\n");
        printf("lowercase: %d -> %d\n", lower_case_pred, lower_case_po);
        printf("uppercase: %d -> %d\n", upper_case_pred, upper_case_po);
        printf("spaces: %d -> %d\n", pocet_mezer, pocet_mezer_po);
        if (i < pocet_radku - 1) printf("\n");
    }
    return 0;
}