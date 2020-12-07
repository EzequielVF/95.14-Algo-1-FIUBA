int sumar_ahorros(int chanchito[], int tope){
    if(tope<=1){
        return chanchito[tope-1];
    }
    return chanchito[tope-1] + sumar_ahorros(chanchito, tope-1);
}