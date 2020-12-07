#include <stdio.h>
#define MAX_NOMBRE 20

void promediar_notas(nota_t notas[MAX_NOTAS], int tope_notas, promedio_t promedios[MAX_PROMEDIOS], int* tope_promedios){
    char alumno_actual[MAX_NOMBRE];
    char materia_actual[MAX_NOMBRE];
    int cantidad_materias=0;
    float promedio;
    (*tope_promedios)=0;
    int i=0;
    while(i<tope_notas){
        strcpy(alumno_actual, notas[i].nombre);
        strcpy(promedios[(*tope_promedios)].nombre, alumno_actual);
        promedio=0;
        cantidad_materias=0;
        while((i<tope_notas)&&(strcmp(alumno_actual,notas[i].nombre)==0)){
            promedio+=notas[i].nota;
            cantidad_materias++;
            i++;
        }
        promedio/=cantidad_materias;
        promedios[*tope_promedios]=promedio;
        (*tope_promedios)++,
    }
}
