#include <stdio.h>

int main(){
    int obrazec;
    int a;
    int b;

    // printf("Zadejte obrazec (0-7) *9-bonus:\n");
    // scanf("%d", &obrazec);
    // printf("Zadejte sirku:\n");
    // scanf("%d", &a);
    // printf("Zadejte vysku:\n");
    // scanf("%d", &b);

    scanf("%d%d%d", &obrazec, &a, &b);

    switch (obrazec)
    {
    case 0:
        for (int i = 0; i < b; i++)
        {
            for (int j = 0; j < a; j++)
            {
                printf("x");
            }
            printf("\n");
        }    
        break;
    case 1:
        for (int i = 0; i < a; i++)
        {
            printf("x");
        }
        printf("\n");   
        for (int j = 0; j < b-2; j++)
        {
            printf("x");
            for (int k = 0; k < a-2; k++)
            {
                printf(" ");
            }
            printf("x\n");           
        }
        for (int i = 0; i < a; i++)
        {
            printf("x");
        }        
        break;
    case 2:
        int cislo2 = 0;
        for (int i = 0; i < a; i++)
        {
            printf("x");
        }
        printf("\n");   
        for (int j = 0; j < b-2; j++)
        {
            printf("x");
            for (int k = 0; k < a-2; k++)
            {
                if (cislo2 <= 9)
                {
                    printf("%d", cislo2);
                }
                else
                {
                    cislo2 = 0;
                    printf("%d", cislo2);
                }
                cislo2++;
            }
            printf("x\n");          
        }
        for (int i = 0; i < a; i++)
        {
            printf("x");
        }  
        break;
    case 3:
        for (int i = 0; i < a; i++)
        {
            for (int j = 0; j < i; j++)
            {
                printf(" ");
            }
            printf("x\n");
        }
        break;
    case 4:
        for (int i = 0; i < a; i++)
         {
            for (int j = a-1; j > i; j--)
            {
                printf(" ");
            }
            printf("x\n");
        }
        break;
    case 5:
        int cislo5 = 1;
        for (int i = 0; i < a-1; i++)
         {
            for (int j = a-1; j > i; j--)
            {
                printf(" ");
            }
            printf("x");
            if (i >= 1)
            {
                for (int k = 0; k < cislo5; k++)
                {
                    printf(" ");
                }
                cislo5 = cislo5 + 2;
                printf("x\n");
                
            }
            else{
                printf("\n");
            }                   
        }
        for (int l = 0; l < a * 2 - 1; l++)
        {
            printf("x");
        }             
        break;
    case 6:
        for (int i = 0; i < a; i++)
        {
            printf("x");
        }
        printf("\n");
        for (int k = 0; k < b-1; k++)
        {
            for (int j = 0; j < a/2; j++)
            {
                printf(" ");
            }
            printf("x\n");
        }
        break;
    case 7:
        for (int i = 0; i < a; i++)
        {
            printf("x");
        }
        printf("\n");
        for (int k = 0; k < b/2-1; k++)
        {
            printf("x");
            for (int j = 0; j < a-2; j++)
            {
                printf(" ");
            }
            printf("x\n");
        }
        for (int i = 0; i < a; i++)
        {
            printf("x");
        }
        printf("\n");
        for (int l = 0; l < b/2; l++)
        {
            printf("x\n");
        }
                            
        break;
    case 9:  
        int cislo9 = 0;  
        for (int i = 0; i < a; i++)
        {
            printf("x");
        }
        printf("\n");   
        for (int j = 0; j < b-2; j++)
        {
            printf("x");
            for (int k = 0; k < a-2; k++)
            {
                printf("%d", ((j + k * (b - 2)) % 10));

            }
            printf("x\n");          
        }
        for (int i = 0; i < a; i++)
        {
            printf("x");
        }  
        break;
    default:
        printf("Neznamy obrazec");
        break;
    }
    printf("\n");





    return 0;
}
