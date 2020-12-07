int factorial(int numero){
    if(numero == 0 || numero == 1){
        return 1;
    }
    return (numero * factorial(numero-1));
}