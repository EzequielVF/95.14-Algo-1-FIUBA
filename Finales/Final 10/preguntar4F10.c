void imprimir_pares(int vector[MAX_NUMEROS], int tope, int posicion){
    if(posicion>tope){
        return;
    }
    if(vector[posicion]%2==0){
        printf("%d",vector[posicion]);
    }
    imprimir_pares(vector, tope, posicion+1);
}
