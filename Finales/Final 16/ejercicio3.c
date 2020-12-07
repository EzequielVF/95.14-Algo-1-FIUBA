bool es_par(int numero){
    if(numero%2==0){
        return true;
    }
}

void imprimir_pares(int numeros[MAX], int tope, int posicion){
    if(posicion == tope){
        return;
    }
    if(es_par(numeros[posicion])){
        printf("%d", numeros[posicion]);
    }
    imprimir_pares( numeros, tope, posicion+1)
}