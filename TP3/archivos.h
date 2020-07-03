#ifndef __ARCHIVOS_H__
#define __ARCHIVOS_H__

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

#define MAX_NOMBRE 10
#define MAX_RANGO 15
#define MAX_DESCRIPCION 150
#define MAX_MISION 30
#define COINCIDENCIA 0


typedef struct enano{
    char nombre[MAX_NOMBRE];
    int edad;
    int cantidad_misiones;
    int id_rango;
}enano_t;

typedef struct rango{
    int id;
    char nombre[MAX_RANGO];
    char descripcion[MAX_DESCRIPCION];
}rango_t;

/*
 * Pre: Recibe un ID de rango valida.
 * Post: Imprime por pantalla el nombre del rango, su descripcion y todos los enanos pertenecientes a dicho rango.
 */
bool listar_enanos(int id_buscado);

/*
 * Post: Revisa la lista de enanos presentes y los promueve si cumplen las condiciones necesarias.
 */
bool promover_enanos();

/*
 * Pre: Recibe la cantidad necesaria de enanos de cada rango necesarios para la mision, el nombre de la misma y la cantidad de argumentos recibidos.
 * Post: Genera el archivo de la mision si se cumple con la cantidad de enanos requerida, si no se cumple con la cantidad el archivo se elimina y si la mision ya estaba creada abortara el proceso de creacion y no modificara el archivo ya existente.
 */
bool integrantes_mision(int guerreros, int lideres, int generales, char nombre[], int argumentos);

/*
 * Pre: Recibe el archivo de una mision con sus participantes.
 * Post: Elimina a los enanos que no volvieron en la mision ademas de añadir a los que se habian perdido, si el archivo a revisar no existe aborta el proceso.
 */
bool actualizar_censo(char nombre[]);

#endif /* __ARCHIVOS_H__ */