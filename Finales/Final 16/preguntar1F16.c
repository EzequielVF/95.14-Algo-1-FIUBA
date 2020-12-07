#include <stdio.h>
#include <string.h>

typedef struct cursada{
    char alumno[MAX_ALUMNO];
    int id_materia;
}cursada_t;

typedef struct materia{
    int id_materia;
    char descripcion[MAX_DESCRIPCION];
}materia_t;

int genera_cursada(dumbledore, minerva){
    cursada_t lista_dumbledore;
    cursada_t lista_minerva;
    FILE* cursada = fopen("cursada.dat","w");
    if(!cursada){
        return -1;
    }
    fread(&lista_dumbledore, sizeof(cursada_t), 1, dumbledore);
    fread(&lista_minerva, sizeof(cursada_t), 1, minerva);
    while(!feof(dumbledore) && !feof(minerva)){
        if(strcmp(lista_dumbledore.alumno, lista_minerva.alumno)<0){
            fwrite(&lista_dumbledore, sizeof(cursada_t), 1, cursada);
            fread(&lista_dumbledore, sizeof(cursada_t), 1, dumbledore);
        }
        else if(strcmp(lista_dumbledore.alumno, lista_minerva.alumno)>0){
            fwrite(&lista_minerva, sizeof(cursada_t), 1, cursada);
            fread(&lista_minerva, sizeof(cursada_t), 1, minerva);
        }
    }
    while(!feof(dumbledore)){
        fwrite(&lista_dumbledore, sizeof(cursada_t), 1, cursada);
        fread(&lista_dumbledore, sizeof(cursada_t), 1, dumbledore);
    }
    while(!feof(minerva)){
        fwrite(&lista_minerva, sizeof(cursada_t), 1, cursada);
        fread(&lista_minerva, sizeof(cursada_t), 1, minerva);
    }
    return 0;
}

materia_t buscar_nombre_materia(FILE* materia,int id){
    materia_t materia_inf;
    fseek( materia, (id-1)*sizeof(materia_t), SEEK_SET);
}

void listar_alumnos_materias(FILE* cursada, FILE* materia){////////////////////////////////////////////////////////////////////
    cursada_t alumno_leido;
    char alumno_actual[MAX_ALUMNO];
    materia_t materia_inf;

    printf("------------------------------/n");
    fread(&alumno_leido, sizeof(cursada_t), 1, cursada);
    while(!feof(cursada)){
        strcpy(alumno_actual, alumno_leido.alumno);
        printf("%s", alumno_actual);
        while(!feof(cursada)&& strcmp(alumno_actual, alumno_leido.alumno)==0){
            materia_inf = buscar_nombre_materia(materia, alumno_leido.id_materia);
            printf("%s", materia_inf.descripcion);
            fread(&alumno_leido, sizeof(cursada_t), 1, cursada);
        }
        printf("------------------------------/n");
    }
}