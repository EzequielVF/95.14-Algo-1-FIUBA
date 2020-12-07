char analizarBalance(char** matriz, int tope) {

    int cantidad_cuadros_superior = 0;
    int cantidad_cuadros_inferior = 0;
    char tipo_balance;

    for (int i = 0; i < tope; i++) {

        for (int j = 0; j < tope; j++) {

            // parte superior
            if (i < j && matriz[i][j] == CUADRO) {

                cantidad_cuadros_superior++;
            }

            // parte inferior
            else if (i > j && matriz[i][j] == CUADRO) {

                cantidad_cuadros_inferior++;
            }
        }
    }
    
    if ((cantidad_cuadros_superior - cantidad_cuadros_inferior) > DIFERENCIA_BALANCE
        || (cantidad_cuadros_inferior - cantidad_cuadros_superior) > DIFERENCIA_BALANCE) {

        tipo_balance = DESBALANCEADA;
    }

    else  {

        tipo_balance = BALANCEADA;
    }

    return tipo_balance;
}
