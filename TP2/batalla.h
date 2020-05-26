#ifndef __BATALLA_H__
#define __BATALLA_H__

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include"perfil.h"
#include"batalla.h"

#define MAX_TERRENO_FIL 10
#define MAX_TERRENO_COL 10
#define MAX_PERSONAJES 100

typedef struct personaje {
	char codigo;
	int vida;
	int ataque;
	int fila;
	int columna;
	bool llego_alfinal;
	bool esta_vivo;
	bool atacando;
	// Pueden agregar los campos que deseen
} personaje_t;

typedef struct juego {
	bool personajes_base_generados;
	char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL];
	personaje_t rohan[MAX_PERSONAJES];
	int cantidad_rohan;
	int llegadas_rohan;
	int plus_rohan;
	int energia_rohan;
	personaje_t isengard[MAX_PERSONAJES];
	int cantidad_isengard;
	int llegadas_isengard;
	int plus_isengard;
	int energia_isengard;
	int cantidad_jugadores;
	char bando_pc;
	bool pc_coloco_este_turno;
	// Pueden agregar los campos que deseen
} juego_t;

/*
 * Inicializará todos los valores del juego, dejándolo en un estado 
 * inicial válido.
 */
void inicializar_juego(juego_t* juego);
/*
 * Entregara un tipo,fila, y columna valido en el cual podra
 * cargarse un campeon.
 */
void preguntar_pc(juego_t* juego, char* tipo, int* fila, int* columna, bool* cargar);
/*
 * Le pedira al jugador del bando de Rohan un tipo, fila, columna valido
 * en el cual puede cargarse un campeon.
 */
void preguntar_rohan(char* tipo, int* fila, int* columna, juego_t* juego, bool* cargar);
/*
 * Le pedira al jugador del bando Isengard un tipo, fila, columna valido
 * en el cual puede cargarse un campeon.
 */
void preguntar_isengard(char* tipo, int* fila, int* columna, juego_t* juego, bool* cargar);
/*
 * Se encarga de mostrar por pantalla el estado actual de la matriz y de
 * marcadores importantes.
 */
void mostrar_informacion_juego(juego_t* juego);
/*
 * Se cargan perfectamente todos los stats de un personaje.
 */
personaje_t crear_personaje(char* tipo, int* fila, int* columna, juego_t* juego);
/*
 * Recibirá un personaje, con todos sus campos correctamente cargados y
 * lo dará de alta en el juego, sumándolo al vector correspondiente,
 * posicionándolo también en la matriz.
 */
void posicionar_personaje(juego_t* juego, personaje_t personaje);

/*
 * Realizará la jugada del personaje del bando recibido que
 * se encuentra en la posición posicion_personaje.
 * Se moverá o atacará dependiento lo que corresponda.
 * Actualizará el juego según los efectos del movimiento del
 * personaje, matar rivales, actualizar la matriz, restar vida, etc.
 */
void jugar(juego_t* juego, char bando, int posicion_personaje);
/*
 * Verifica los dos contadores de llegadas.
 * Identifica de quien es el contador victorioso y imprime el bando.
 */
void detectar_ganador(juego_t* juego);

#endif /* __BATALLA_H__ */