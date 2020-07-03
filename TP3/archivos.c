#include"archivos.h"

const int ID_MIN = 1;
const int ID_MAX = 5;
const int OBRERO = 1;
const int APRENDIZ= 2;
const int GUERRERO = 3;
const int LIDER = 4;
const int GENERAL = 5;
const int PARAMETROS_LEIDOS = 4;
const int MIN_MISIONES_GUERRERO = 10;
const int MIN_MISIONES_LIDER = 100;
const int MIN_MISIONES_GENERAL= 250;
const int MIN_EDAD_LIDER = 40;
const int MIN_EDAD_GENERAL = 50;
const int MAX_EDAD_LIDER = 50;
const int MAX_EDAD_GENERAL = 60;
const int MUERTO = -1;
const int INTEGRAR_MISION_NOMBRE_DEFINIDO = 6;
const int NO_FALTA_NADIE = 0;

bool listar_enanos(int id_buscado){
    rango_t rango_aux;
    enano_t enano_aux;
    int leido=0;
    if((id_buscado >= ID_MIN ) && (id_buscado <= ID_MAX)){
        FILE* rangos = fopen("rangos.dat","r");
        if(!rangos){
            return false;
        }
        FILE* enanos = fopen("censo.csv", "r");
        if(!enanos){
            fclose(rangos);
            return false;
        }
        fread(&rango_aux, sizeof(rango_t),1 , rangos);
        while(!feof (rangos)){
            if((rango_aux.id)==id_buscado){
                printf("%s\n", rango_aux.nombre);
                printf("%s\n", rango_aux.descripcion);
            }
            fread(&rango_aux, sizeof(rango_t),1 , rangos);
        }
        
        leido = fscanf(enanos, "%[^;];%i;%i;%i", enano_aux.nombre, &enano_aux.edad, &enano_aux.cantidad_misiones, &enano_aux.id_rango);
        while(leido==PARAMETROS_LEIDOS){
            if((enano_aux.id_rango) == id_buscado){
                printf("%s %i %i\n", enano_aux.nombre, enano_aux.edad, enano_aux.cantidad_misiones);
            }
            leido = fscanf(enanos, "%[^;];%i;%i;%i", enano_aux.nombre, &enano_aux.edad, &enano_aux.cantidad_misiones, &enano_aux.id_rango);
        }
        fclose(rangos);
        fclose(enanos);
        printf("Listado de enanos exitosos!!\n");
    }
    else{
        printf("Rango de ID invalido!!\n");
    }
    return true;
}

bool promover_enanos(){
    int leido = 0;
    enano_t enano_aux;
    FILE* enanos = fopen("censo.csv", "r");
    if(!enanos){
        return false;
    }
    FILE* volcado = fopen("volcado.csv", "w");
    if(!volcado){
        fclose(enanos);
        return false;
    }
    leido = fscanf(enanos, "%[^;];%i;%i;%i", enano_aux.nombre, &enano_aux.edad, &enano_aux.cantidad_misiones, &enano_aux.id_rango);
    while(leido==PARAMETROS_LEIDOS){
        if(((enano_aux.id_rango) == APRENDIZ) && (enano_aux.cantidad_misiones > MIN_MISIONES_GUERRERO) && (enano_aux.edad != MUERTO)){
            enano_aux.id_rango=GUERRERO;
        }
        else if(((enano_aux.id_rango) == GUERRERO) && (enano_aux.cantidad_misiones > MIN_MISIONES_LIDER) && (enano_aux.edad >= MIN_EDAD_LIDER) && (enano_aux.edad <= MAX_EDAD_LIDER)){
            enano_aux.id_rango=LIDER;
        }
        else if(((enano_aux.id_rango) == LIDER) && (enano_aux.cantidad_misiones > MIN_MISIONES_GENERAL) && (enano_aux.edad >= MIN_EDAD_GENERAL) && (enano_aux.edad <= MAX_EDAD_GENERAL)){
            enano_aux.id_rango=GENERAL;
        }
        fprintf(volcado, "%s;%i;%i;%i", enano_aux.nombre, enano_aux.edad, enano_aux.cantidad_misiones, enano_aux.id_rango);
        leido = fscanf(enanos, "%[^;];%i;%i;%i", enano_aux.nombre, &enano_aux.edad, &enano_aux.cantidad_misiones, &enano_aux.id_rango);
    }
    fclose(enanos);
    fclose(volcado);
    remove("censo.csv");
    rename("volcado.csv", "censo.csv");
    printf("Proceso de promocion realizado con exito!!\n");
    return true;
}

bool integrantes_mision(int guerreros, int lideres, int generales, char nombre[], int argumentos){
    enano_t enano_aux;
    int leido=0;
    int guerreros_restantes= guerreros;
    int lideres_restantes= lideres;
    int generales_restantes= generales;

    FILE* mision = fopen(nombre, "r");
    if(!mision){
        FILE* mision = fopen(nombre, "w");
        if(mision){
            FILE* enanos = fopen("censo.csv", "r");
            if(enanos){
                leido = fscanf(enanos, "%[^;];%i;%i;%i", enano_aux.nombre, &enano_aux.edad, &enano_aux.cantidad_misiones, &enano_aux.id_rango);
                while(leido == PARAMETROS_LEIDOS){
                    if((enano_aux.id_rango == GUERRERO) && (guerreros_restantes > NO_FALTA_NADIE)){
                        fwrite(&enano_aux, sizeof(enano_t),1 , mision);
                        guerreros_restantes--;
                    }
                    else if((enano_aux.id_rango == LIDER) &&(lideres_restantes > NO_FALTA_NADIE)){
                        fwrite(&enano_aux, sizeof(enano_t),1 , mision);
                        lideres_restantes--;
                    }
                    else if((enano_aux.id_rango == GENERAL) && (generales_restantes >NO_FALTA_NADIE)){
                        fwrite(&enano_aux, sizeof(enano_t),1 , mision);
                        generales_restantes--;
                    }
                    leido = fscanf(enanos, "%[^;];%i;%i;%i",enano_aux.nombre, &enano_aux.edad, &enano_aux.cantidad_misiones, &enano_aux.id_rango);
                }
                if((generales_restantes > NO_FALTA_NADIE) || (guerreros_restantes > NO_FALTA_NADIE) || (lideres_restantes > NO_FALTA_NADIE)){
                    printf("Cantidad insuficiente de hombres, abortamos preparativos\n");
                    if(argumentos == INTEGRAR_MISION_NOMBRE_DEFINIDO){
                        remove(nombre);
                    }else{
                        remove("mision.dat");
                    }
                }else{
                    printf("Mision generada con exito!!\n");
                }
            fclose(mision);
            fclose(enanos);
            } 
            else{
                fclose(mision);
            }
        }
        else{
            return false;
        }
    }
    else{
        printf("Ya existe la mision, abortamos preparativos\n");
        return false;
    }
    return true; 
}

bool actualizar_censo(char nombre[]){
    int leido=0;
    enano_t de_censo;
    enano_t de_mision;

    FILE* mision = fopen(nombre, "r");
    if(!mision){
        printf("No se pudo abrir el registro de mision, abortando proceso.\n");
        return false;
    }else{
        FILE* enanos = fopen("censo.csv", "r");
        if(!enanos){
            fclose(mision);
            return false;
        }else{
            FILE* volcado = fopen("volcado.csv", "w");
            if(!volcado){
                fclose(enanos);
                fclose(mision);
                return false;
            }else{
                fread(&de_mision, sizeof(enano_t),1 , mision);
                leido = fscanf(enanos, "%[^;];%i;%i;%i",de_censo.nombre, &de_censo.edad, &de_censo.cantidad_misiones, &de_censo.id_rango);
                while((!feof (mision))&&(leido==PARAMETROS_LEIDOS)){
                    if((strcmp(de_mision.nombre,de_censo.nombre)<COINCIDENCIA)&&(de_mision.edad!=MUERTO)){
                        fprintf(volcado,"%s;%i;%i;%i", de_mision.nombre, de_mision.edad, de_mision.cantidad_misiones, de_mision.id_rango);
                        fread(&de_mision, sizeof(enano_t),1 , mision);
                    }
                    else if((strcmp(de_mision.nombre,de_censo.nombre) > COINCIDENCIA) && (de_mision.edad!= MUERTO)){
                        fprintf(volcado, "%s;%i;%i;%i", de_censo.nombre, de_censo.edad, (de_censo.cantidad_misiones+1), de_censo.id_rango);
                        leido = fscanf(enanos, "%[^;];%i;%i;%i", de_censo.nombre, &de_censo.edad, &de_censo.cantidad_misiones, &de_censo.id_rango);
                    }else if((strcmp(de_mision.nombre,de_censo.nombre)== COINCIDENCIA) && (de_mision.edad!= MUERTO)){
                        fprintf(volcado,"%s;%i;%i;%i", de_censo.nombre, de_censo.edad, (de_censo.cantidad_misiones+1), de_censo.id_rango);
                        fread(&de_mision, sizeof(enano_t),1 , mision);
                        leido = fscanf(enanos, "%[^;];%i;%i;%i", de_censo.nombre, &de_censo.edad, &de_censo.cantidad_misiones, &de_censo.id_rango);
                    }else{
                        fread(&de_mision, sizeof(enano_t),1 , mision);
                           leido = fscanf(enanos, "%[^;];%i;%i;%i", de_censo.nombre, &de_censo.edad, &de_censo.cantidad_misiones, &de_censo.id_rango);
                    }
                }
                while(leido==PARAMETROS_LEIDOS){
                    fprintf(volcado, "%s;%i;%i;%i", de_censo.nombre, de_censo.edad, de_censo.cantidad_misiones, de_censo.id_rango);
                    leido = fscanf(enanos, "%[^;];%i;%i;%i", de_censo.nombre, &de_censo.edad, &de_censo.cantidad_misiones, &de_censo.id_rango);
                }
                while(!feof (mision)){
                    fprintf(volcado, "%s;%i;%i;%i", de_mision.nombre, de_mision.edad, (de_mision.cantidad_misiones+1), de_mision.id_rango);
                    fread(&de_mision, sizeof(enano_t),1 , mision);
                }
                fclose(volcado);
                fclose(mision);
                fclose(enanos);
                remove("censo.csv");
                rename("volcado.csv", "censo.csv");
                printf("Censo actualizado perfectamente!!\n");
            }
        }
    }
    return true;
}