#include <stdio.h>

int pocitej_cifry(int cislo) {
    int pocet_cifer = 0;

    if (cislo == 0) return 1;

    while (cislo > 0) {
        cislo = cislo / 10;
        pocet_cifer++;
    }
    
    return pocet_cifer;
}

int main () {

    char histogram;
    int n = 0;
    int m = 0;

    int cislo = 0;

    scanf("%c\n", &histogram);
    scanf("%d ", &n);
    scanf("%d\n", &m);

    int pole[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    int nej_pocet_cifer = pocitej_cifry(m + 8);

    switch (histogram)
    {
    case 'h': 
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &cislo);

            if (cislo > -1+m && cislo < 10+m) 
            {
                pole[cislo-m]++; 
            }    
            else
            {
                pole[9]++;
            }
        }

        for (int i = 0; i < 10; i++)
        {
            if(i == 9) 
            {
                printf("invalid: ");
                for (int j = 0+m; j < pole[9]+m; j++) 
                {
                    printf("#");
                }
            }
            else
            {
                if (pocitej_cifry(i+m) < nej_pocet_cifer)
                {
                    printf(" %d ", i+m); 
                    for (int j = 0+m; j < pole[i]+m; j++) 
                    {
                        printf("#");
                    }
                    printf("\n");
                }
                else
                {
                    printf("%d ", i+m); 
                    for (int j = 0+m; j < pole[i]+m; j++) 
                    {
                        printf("#");
                    }
                    printf("\n");
                }
            
            }
        }
        break;
    case 'v':
        printf("Nemam");
    
    default:
    printf("Neplatny mod vykresleni");
        break;
    }

    return 0;
}