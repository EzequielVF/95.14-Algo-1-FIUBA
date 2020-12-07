char decide_tipo_pared(pared[MAX_ALT][MAX_ANCHO], int tope_altura, int tope_ancho){
    int total_cuadros=0;
    int cuadros_q_hablan=0;
    int cuadros_mudos=0;
    char pared;

    for(int i=0; i<tope_altura, i++){
        for(int j=0; j<tope_ancho, j++){
            if(pared[i][j]=='N'){
                total_cuadros++;
                cuadros_mudos++;
            }else{
                total_cuadros++;
                cuadros_q_hablan++;
            }
        }
    }
    if((cuadros_q_hablan/total_cuadros*100)>50){
        pared=CHARLATANA;
    }else if((cuadros_q_hablan/total_cuadros*100)<25){
        pared=MUDA;
    }else{
        pared=INDECISA;
    }
    return pared;
}