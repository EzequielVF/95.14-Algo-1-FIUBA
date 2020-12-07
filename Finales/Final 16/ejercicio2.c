char determina_ganador(char tablero[MAX_FILAS][MAX_COLUMNAS]){
    int fichas_harry=0;
    int fichas_ron=0;
    char ganador;
    for(int i=0; i<MAX_FILAS; i++){
        for(int j=0; j<MAX_COLUMNAS; j++){
            if(tablero[i][j]=='R'){
                fichas_harry++;
            }
            else if(tablero[i][j]=='B'){
                fichas_ron++;
            }
        }
    }
    if(fichas_harry>fichas_ron){
        ganador = HARRY;
    }
    else if(fichas_harry<fichas_ron){
        ganador = RON;
    }else{
        ganador = EMPATADOS;
    }
    return ganador;
}