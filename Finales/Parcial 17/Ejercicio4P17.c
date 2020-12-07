bool estan_ordenados(float vasos[MAX_VASOS], int tope_v, int posicion){
    if(posicion>=tope_v-1){
        return true;
    }
    if(vasos(posicion)>(posicion+1)){
        return false;
    }
    return estan_ordenados(vasos, tope_v, posicion+1);
}