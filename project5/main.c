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

        int rows = 0;
        int cols = 0;
        char akce;

        scanf("%d ", &rows);
        scanf("%d", &cols);

        char *pole = (char *)malloc(rows * cols * sizeof(char));

        memset(pole, '.', rows * cols);

        //zelva 1
        char z1 = 'z'; 
        pole[0] = z1;
        
        int zelva_row = 0;
        int zelva_col = 0;
        int rotace = 0;

        int pomocna = 0;

        while(scanf(" %c", &akce) == 1)
        {
            int zr = zelva_row;
            int zc = zelva_col;
            
            switch (akce)
            {
            case 'r':
                if (rotace == 0)
                {
                    rotace = 270;
                }
                else
                {
                    rotace -= 90;
                }           
                break;
            case 'l':
                if (rotace == 270)
                {
                    rotace = 0;
                }
                else
                {
                    rotace += 90;
                }       
                break;
            case 'o':
                pomocna = 1;
                if (pole[zelva_row * cols + zelva_col] == 'o')
                {
                    pole[zelva_row * cols + zelva_col] = '.';
                }
                else
                {
                    pole[zelva_row * cols + zelva_col] = 'o';
                }
                
                break;

            case 'm':
                if (rotace == 0)     
                {
                    zelva_col += 1;
                }
                else if(rotace == 180) 
                {
                    zelva_col -= 1;
                }
                else if(rotace == 90) 
                {
                    zelva_row -= 1;
                }
                else if(rotace == 270) 
                {
                    zelva_row += 1;
                }

                //teleportace
                if (zelva_row >= rows)
                {
                    zelva_row = 0;
                }
                else if(zelva_col >= cols)
                {
                    zelva_col = 0;
                }
                else if(zelva_row <= -1)
                {
                    zelva_row = rows-1;
                }
                else if(zelva_col <= -1)
                {
                    zelva_col = cols-1;
                }

                if (pomocna == 1 && pole[zr * cols + zc] == 'o')
                {
                    pole[zr * cols + zc] = 'o';
                    pomocna = 0;
                }
                else
                {
                    pole[zr * cols + zc] = '.';
                }

                pole[zelva_row * cols + zelva_col] = 'z';
                break;
            case 'x':
                funkce(pole, rows, cols);
                exit(0);
                break;
            default:
                break;
            }
        }

        free(pole);
        return 0;
    }