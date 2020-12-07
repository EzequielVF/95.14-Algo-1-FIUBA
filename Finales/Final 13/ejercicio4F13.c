#include<stdio.h>

void desbloquear_droide(int inicio, int incremento, int final){
    if(inicio>final){
        return;
    }else{
        printf("%d", inicio);
    }
    desbloquear_droide(inicio+incremento, incremento, final);
}

int main(){
    int inicio=18;
    int fin=87;
    int incremento=10;
    desbloquear_droide(inicio, incremento, fin);
}