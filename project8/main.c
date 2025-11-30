#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

int main (int argc, char *argv[])
{
    //POVINNE
    char *input_path = NULL;
    char *needle = NULL;
    int pocet_povinnych = 0;

    //NEPOVINNE
    int ignore_case = 0;
    int is_output_path = 0;
    char *output_path = NULL;

    char radek[101];

    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-i") == 0){
            if (ignore_case == 1){ //je vickrat?
                printf("Parameter -i provided multiple times\n");
                exit(1);
            }
            ignore_case = 1;

        }else if(strcmp(argv[i], "-o") == 0){
            if (is_output_path == 1){ //je vickrat?
                printf("Parameter -o provided multiple times\n");
                exit(1);    
            }
            is_output_path = 1;            
            if (i+1 >= argc){ //nasleduje dalsi parametr?   
                printf("Missing output path\n");
                exit(1);                
            }                   
            if (output_path != NULL){  //je vickrat?
                printf("Too many parameters provided\n");
                exit(1);
            }
            output_path = argv[i+1]; //prirazeni hodnoty z argv[i+1 - nasledujici]
            i++; //bo dalsi parametr je output, ktery je po -o

        }else{
            if (pocet_povinnych == 0){
                input_path = argv[i];
                pocet_povinnych++; 
            }else if(pocet_povinnych == 1){
                needle = argv[i];
                pocet_povinnych++;
            }else{
                printf("Too many parameters provided\n");
                exit(1);
            }          
        }
    }

    if (input_path == NULL){
        printf("Input path not provided\n");
        exit(1);
    }
    if (needle == NULL){
        printf("Needle not provided\n");
        exit(1);
    }
    
    FILE *input_file = fopen(input_path, "r");
    FILE *output_file = NULL;
    if(output_path != NULL) output_file = fopen(output_path, "w");
    if(output_path == NULL) output_file = stdout;

    while(fgets(radek, sizeof(radek), input_file) != NULL){
        if (ignore_case == 0){
            if (strstr(radek, needle)) fprintf(output_file, "%s", radek); //zjistuji zda needle se nachazi v radku
        }else if(ignore_case == 1){
            if (strcasestr(radek, needle)) fprintf(output_file, "%s", radek); //zjistuji zda needle se nachazi v radku s ignorovanim velikosti pisma
        }
    }

    fclose(input_file);
    if (output_file != stdout) fclose(output_file);

    return 0;
}