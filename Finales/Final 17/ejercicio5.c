#include <stdio.h>
#include <string.h>

#define MAX_LETRAS 50

int main(){
    FILE* lista1 = fopen("materia1.txt", "r");
    FILE* lista2 = fopen("materia2.txt", "r");
    FILE* volcado = fopen("volcado.txt", "w");
    char nombre_primer_lista[MAX_LETRAS];
    char nombre_segunda_lista[MAX_LETRAS];
    int leido_lista_2=0;

    if(!lista1){
        perror("Error");
        return 0;
    }
    if(!lista2){
        perror("Error");
        fclose(lista1);
        return 0;
    }
    if(!volcado){
        perror("Error");
        fclose(lista1);
        fclose(lista2);
        return 0;
    }
    fread(&nombre_primer_lista, sizeof(MAX_LETRAS),1,lista1);
    fread(&nombre_segunda_lista, sizeof(MAX_LETRAS),1,lista2);
    while(!feof(lista1)&&!feof(lista2)){
        if(strcmp(nombre_primer_lista, nombre_segunda_lista)==0){
            fread(&nombre_primer_lista, sizeof(MAX_LETRAS),1,lista1);
            fread(&nombre_segunda_lista, sizeof(MAX_LETRAS),1,lista2);
        }
        else if(strcmp(nombre_primer_lista, nombre_segunda_lista)<0){
            fwrite(&nombre_primer_lista, sizeof(MAX_LETRAS), 1, volcado);
            fread(&nombre_primer_lista, sizeof(MAX_LETRAS),1,lista1);
        }else{
            fread(&nombre_segunda_lista, sizeof(MAX_LETRAS),1,lista2);
        }
    }
    fclose(volcado);
    fclose(lista2);
    fclose(lista1);
    printf("Listo aaaanadooo");
    return 0;
}