#include<stdio.h>
#include<string.h>

#define MAX 50

void mostrar_bocales(char vector[MAX], int tope){
    if(tope<0){
        return;
    }
    if(vector[tope]=='a'||vector[tope]=='e'||vector[tope]=='i'||vector[tope]=='o'||vector[tope]=='u'){
        printf("%c", vector[tope]);
    }
    mostrar_bocales(vector, tope-1);
}

int main(){
    char nombre[MAX];
    strcpy(nombre, "holaaaa, vos decis?");
    mostrar_bocales(nombre, strlen(nombre));
}
