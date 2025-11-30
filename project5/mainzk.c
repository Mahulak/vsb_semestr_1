#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void funkce(char *pole, int rows, int cols){
        
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                printf("%c", pole[i * cols + j]);       
            }
            printf("\n");
        } 
    }

    int main(){

        int pocetzelv = 1;

        int rows = 0;
        int cols = 0;
        char akce;

        scanf("%d ", &rows);
        scanf("%d", &cols);

        char *pole = (char *)malloc(rows * cols * sizeof(char));

        memset(pole, '.', rows * cols);

        /*char *poleZ[3];
        poleZ[0] = 'z';
        poleZ[1] = 'z';
        poleZ[2] = 'z';*/

        pole[0] = 'z';
        pole[1] = 'z';
        pole[2] = 'z';
        
        int zelva_row[3]; //
        int zelva_col[3]; //
        int rotace[3]; //

        int pomocna = 0;

        int zr[3];
        int zc[3];

        while(scanf(" %c", &akce) == 1)
        {
            for (int i = 0; i < pocetzelv; i++)
            {
                zr[i] = zelva_row[i]; //
                zc[i] = zelva_col[i]; //
            }

            switch (akce)
            {
            case 'r':
                for (int i = 0; i < pocetzelv; i++)
                {
                    if (rotace[i] == 0)
                    {
                        rotace[i] = 270;
                    }
                    else
                    {
                        rotace[i] -= 90;
                    }  
                }        
                break;
            case 'l':
                for (int i = 0; i < pocetzelv; i++)
                {
                    if (rotace[i] == 270)
                    {
                        rotace[i] = 0;
                    }
                    else
                    {
                        rotace[i] += 90;
                    }       
                }      
                break;
            case 'o':
                for (int i = 0; i < pocetzelv; i++)
                {
                    pomocna = 1;
                    if (pole[zelva_row[i] * cols + zelva_col[i]] == 'o')
                    {
                        pole[zelva_row[i] * cols + zelva_col[i]] = '.';
                    }
                    else
                    {
                        pole[zelva_row[i] * cols + zelva_col[i]] = 'o';
                    }
                }
                break;

            case 'm':
                for (int i = 0; i < pocetzelv; i++)
                {
                    if (rotace[i] == 0)     
                    {
                        zelva_col[i] += 1;
                    }
                    else if(rotace[i] == 180) 
                    {
                        zelva_col[i] -= 1;
                    }
                    else if(rotace[i] == 90) 
                    {
                        zelva_row[i] -= 1;
                    }
                    else if(rotace[i] == 270) 
                    {
                        zelva_row[i] += 1;
                    }

                    //teleportace
                    if (zelva_row[i] >= rows)
                    {
                        zelva_row[i] = 0;
                    }
                    else if(zelva_col[i] >= cols)
                    {
                        zelva_col[i] = 0;
                    }
                    else if(zelva_row[i] <= -1)
                    {
                        zelva_row[i] = rows-1;
                    }
                    else if(zelva_col[i] <= -1)
                    {
                        zelva_col[i] = cols-1;
                    }

                    if (pomocna == 1 && pole[zr[i] * cols + zc[i]] == 'o')
                    {
                        pole[zr[i] * cols + zc[i]] = 'o';
                        pomocna = 0;
                    }
                    else
                    {
                        pole[zr[i] * cols + zc[i]] = '.';
                    }

                    pole[zelva_row[i] * cols + zelva_col[i]] = 'z'; 
                    
                    if (rotace[i] == 0)     
                    {
                        zelva_col[i] += 1;
                    }
                    else if(rotace[i] == 180) 
                    {
                        zelva_col[i] -= 1;
                    }
                    else if(rotace[i] == 90) 
                    {
                        zelva_row[i] -= 1;
                    }
                    else if(rotace[i] == 270) 
                    {
                        zelva_row[i] += 1;
                    }

                    //teleportace
                    if (zelva_row[i] >= rows)
                    {
                        zelva_row[i] = 0;
                    }
                    else if(zelva_col[i] >= cols)
                    {
                        zelva_col[i] = 0;
                    }
                    else if(zelva_row[i] <= -1)
                    {
                        zelva_row[i] = rows-1;
                    }
                    else if(zelva_col[i] <= -1)
                    {
                        zelva_col[i] = cols-1;
                    }

                    if (pomocna == 1 && pole[zr[i] * cols + zc[i]] == 'o')
                    {
                        pole[zr[i] * cols + zc[i]] = 'o';
                        pomocna = 0;
                    }
                    else
                    {
                        pole[zr[i] * cols + zc[i]] = '.';
                    }
                
                    pole[zelva_row[i] * cols + zelva_col[i]] = 'z';   
                }                                   
                break;
            case 'x':
                funkce(pole, rows, cols);
                break;

            case 'f':
                pocetzelv++;                
                break;
            default:
                break;

        free(pole);
        return 0;
            }
        }
    }
    