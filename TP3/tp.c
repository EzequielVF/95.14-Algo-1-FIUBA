#include"archivos.h"

int main(int argc, char *argv[]){
    if(strcmp(argv[1], "listar_enanos") == COINCIDENCIA){
        if(argc == 3){
            listar_enanos(atoi(argv[2]));
        }
        else{
            printf("Cantidad invalida de argumentos.\n");
        }
    }
    else if(strcmp(argv[1], "promover_enanos") == COINCIDENCIA){
        if(argc == 2){
            promover_enanos();
        }
        else{
            printf("Cantidad invalida de argumentos.\n");
        }
    }
    else if(strcmp(argv[1], "integrantes_mision") == COINCIDENCIA){
        if(argc == 6){
            integrantes_mision(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), argv[5], argc);
        }
        else if(argc == 5){
            integrantes_mision(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), "mision.dat", argc);
        }
        else{
            printf("Cantidad invalida de argumentos.\n");
        }
    }
    else if(strcmp(argv[1], "actualizar_censo") == COINCIDENCIA){
        if(argc == 3){
            actualizar_censo(argv[2]);
        }
        else{
            printf("Cantidad invalida de argumentos.\n");
        }
    }
    return 0;
}