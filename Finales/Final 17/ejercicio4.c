#include<stdio.h>

int main(){
    FILE* discurso = fopen("discurso.txt", "r");
    FILE* discurso_nuevo = fopen("discurso2.txt", "w");
    int caracter_leido;
    if(!discurso){
        perror("Error");
        return 0;
    }
    if(!discurso_nuevo){
        perror("Error");
        fclose(discurso);
        return 0;
    }
    caracter_leido=fgetc(discurso);
    while(caracter_leido!=EOF){
        if((caracter_leido=='a')||(caracter_leido== 'e')||(caracter_leido=='o')||(caracter_leido=='u')){
            caracter_leido='i';
        }
        fputc(caracter_leido, discurso_nuevo);
        caracter_leido=fgetc(discurso);
    }
    fclose(discurso_nuevo);
    fclose(discurso);
    remove("discurso.txt");
    rename("discurso2.txt", "discurso.txt");
    return 0;
}