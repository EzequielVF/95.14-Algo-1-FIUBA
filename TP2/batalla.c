#include"perfil.h"
#include"batalla.h"

#define LLEGADAS_VICTORIA 5

const int TOPE_PERSONAJES_INICIALES= 3;
const int VIDA_ARQUEROS= 200;
const int ATAQUE_ARQUEROS=10;
const int VIDA_SOLDADOS=100;
const int ATAQUE_SOLDADOS=50;
const int ENERGIA_COMIENZO=5;
const int COSTO_SOLDADOS=3;
const int COSTO_ARQUERO=8;
const int FILA_MAX_ELFO=8;
const int FILA_MIN_ELFO=5;
const int FILA_MAX_URUK=4;
const int FILA_MIN_URUK=1;
const int VIDA_MIN=0;
const int PRIMER_FILA=0;
const int ULTIMA_FILA=9;
const int PRIMER_COLUMNA=0;
const int ULTIMA_COLUMNA=9;
const int MAX_ENERGIA=10;
const int RANGO_NUMERO_ALEATORIO_ARQUEROS=4;
const int RANGO_COLUMNA_ALEATORIO=10;
const int RANGO_NUMERO_ALEATORIO_PLUS=6;
const int DISTANCIA_MAX_ATAQUE_ARQUEROS=3;
const int DOS_JUGADORES=2;
const int UN_JUGADOR=1;
const char VACIO = '-';
const char ROHAN ='R';
const char ISENGARD ='I';
const char ELFO ='E';
const char HOMBRE ='H';
const char URUK ='U';
const char ORCO ='O';
const char ARQUEROS='A';

/*
 * Pre: Recibe una matriz cargada apropiadamente.
 * Post: Imprime su estado actual.
 */
void imprimir_campo_de_juego(juego_t* juego){
	for (int i = 0; i < MAX_TERRENO_FIL; i++){
		for (int j = 0; j < MAX_TERRENO_COL; j++){
			printf("%c",juego->terreno[i][j]);
		}
		printf("\n");
	}
}
/*
 * Post:Inicializa todos los valores de la matriz terreno.
 */
void rellenar_campo_de_juego(juego_t* juego){
	for (int i = 0; i < MAX_TERRENO_FIL; i++){
		for (int j = 0; j < MAX_TERRENO_COL; j++){
			juego->terreno[i][j]=VACIO;
		}
	}
}
/*
 * Post: Controla que los jugadores no pasen el limite puntos de energia.
 */
void actualizar_contador_energia(juego_t* juego){
	if(juego->energia_isengard>=MAX_ENERGIA){
		juego->energia_isengard=MAX_ENERGIA;
	}
	if(juego->energia_rohan>=MAX_ENERGIA){
		juego->energia_rohan=MAX_ENERGIA;
	}
}
/*
 * Pre: Recibe los vectores de Rohan y isengard perfectamente cargados.
 * Post: Carga la ubicacion actual de los personajes en la matriz.
 */
void actualizar_matriz(juego_t* juego){
	rellenar_campo_de_juego(juego);
	for(int i=0; i<juego->cantidad_rohan; i++){
		if((juego->rohan[i].llego_alfinal==false) && (juego->rohan[i].esta_vivo==true)){
		juego->terreno[juego->rohan[i].fila][juego->rohan[i].columna]=(juego->rohan[i].codigo);
		}
	}
	for(int i=0; i<juego->cantidad_isengard; i++){
		if((juego->isengard[i].llego_alfinal==false) && (juego->isengard[i].esta_vivo==true)){
			juego->terreno[juego->isengard[i].fila][juego->isengard[i].columna]=(juego->isengard[i].codigo);
		}
	}
}
 /*
  *
  */
void mostrar_informacion_juego(juego_t* juego){
	system("clear");
	actualizar_contador_energia(juego);
	printf("Energia Isengard = %d\n",juego->energia_isengard);
	printf("Llegadas Isengard = %d\n",juego->llegadas_isengard);
	printf("Bonus Isengard =%d\n", juego->plus_isengard);
	imprimir_campo_de_juego(juego);
	printf("Energia Rohan = %d\n",juego->energia_rohan);
	printf("Llegadas Rohan = %d\n",juego->llegadas_rohan);
	printf("Bonus Rohan = %d\n", juego->plus_rohan);
}
/*
 * Pre: Recibe el bando del jugador_1 y su intensidad y el bando del jugador_2 y su intensidad.
 * Post: Imprime el bando correspondiente a cada jugador, ademas en caso necesario determina el bando que le tocara a la maquina.
 */
void determinar_bando_jugadores(juego_t* juego, char tipo, int intensidad, int* intensidad_rival){
	system("clear");
	if((tipo==ROHAN) && (juego->cantidad_jugadores==DOS_JUGADORES)){
		printf("El Jugador 1 es Rohan y tiene un plus de %d puntos.\n",juego->plus_rohan);
		printf("El Jugador 2 es Isengard y tiene un plus de %d puntos.\n",juego->plus_isengard);
		printf("\n");
	}
	else if((tipo==ISENGARD) && (juego->cantidad_jugadores==DOS_JUGADORES)){
		printf("El Jugador 1 es Isengard y tiene un plus de %d puntos.\n",juego->plus_isengard);
		printf("El Jugador 2 es Rohan y tiene un plus de %d puntos.\n",juego->plus_rohan);
		printf("\n");
	}
	else if((tipo==ROHAN) && (juego->cantidad_jugadores==UN_JUGADOR)){
		printf("El Jugador 1 es Rohan y tiene un plus de %d puntos.\n",juego->plus_rohan);
		printf("La maquina es Isengard y tiene un plus de %d puntos.\n",juego->plus_isengard);
		juego->bando_pc=ISENGARD;
		printf("\n");
	}
	else if((tipo==ISENGARD) && (juego->cantidad_jugadores==UN_JUGADOR)){
		printf("El Jugador 1 es Isengard y tiene un plus de %d puntos.\n",juego->plus_isengard);
		printf("La maquina es Rohan y tiene un plus de %d puntos.\n",juego->plus_rohan);
		juego->bando_pc=ROHAN;
		printf("\n");
	}
}
/*
 * Post: Inicializa la cantidad de jugadores en esta partida. 
 */
void preguntar_cantidad_jugadores(juego_t* juego){
	int jugadores_deseados=0;
	printf("¿La partida sera de un solo jugador vs la maquina o de dos jugadores?(Ingrese (1 o 2) la cantidad de jugadores).\n");
	scanf(" %d", &jugadores_deseados);
	while((jugadores_deseados<1) || (jugadores_deseados>2)){
		printf("Porfavor ingrese una cantidad valida de jugadores, 1 para jugar solo, 2 para jugar con un amigo.\n");
		scanf(" %d", &jugadores_deseados);
	}
	juego->cantidad_jugadores=jugadores_deseados;
}
/*
 * Recibe el tipo y la intensidad del jugador_1.
 * Determina el plus del jugador_1 y jugador_2.
 */
void cargar_plus(juego_t* juego, char tipo, int intensidad, int* intensidad_rival){
	int numero_aleatorio=(rand()%RANGO_NUMERO_ALEATORIO_PLUS);
	if(tipo==ROHAN){
		juego->plus_rohan=(intensidad*numero_aleatorio);
		numero_aleatorio=(rand()%RANGO_NUMERO_ALEATORIO_PLUS);
		juego->plus_isengard=(((*intensidad_rival)-intensidad)*numero_aleatorio);
	}
	else if(tipo==ISENGARD){
		juego->plus_isengard=(intensidad*numero_aleatorio);
		numero_aleatorio=(rand()%RANGO_NUMERO_ALEATORIO_PLUS);
		juego->plus_rohan=(((*intensidad_rival)-intensidad)*numero_aleatorio);
	}
}
/*
 * Post: Inicializará los valores de los contadores, dejándolos en un estado inicial válido.
 */
void iniciar_contadores(juego_t* juego){
	juego->energia_rohan=ENERGIA_COMIENZO;
	juego->cantidad_rohan=0;
	juego->llegadas_rohan=0;
	juego->energia_isengard=ENERGIA_COMIENZO;
	juego->cantidad_isengard=0;
	juego->llegadas_isengard=0;
	juego->pc_coloco_este_turno=false;
	if(juego->cantidad_jugadores==DOS_JUGADORES){
		juego->bando_pc=VACIO;
	}
}
/*
 * Post: Se encarga de generar los Elfos y a los Uruks iniciales en una posicion aleatoria del lado correcto.
 */
void cargador_personajes_iniciales(juego_t* juego, personaje_t personaje){
	int fila_deseada=0;
	int columna_deseada=0;
	for(int i=0;i<TOPE_PERSONAJES_INICIALES;i++){
		juego->cantidad_rohan++;
		juego->rohan[i].codigo=ELFO;
		juego->rohan[i].llego_alfinal=false;
		juego->rohan[i].esta_vivo=true;
		juego->rohan[i].atacando=false;
		juego->rohan[i].vida=(VIDA_ARQUEROS-(juego->plus_rohan));
		juego->rohan[i].ataque=(ATAQUE_ARQUEROS+(juego->plus_rohan));
		fila_deseada=(rand()%RANGO_NUMERO_ALEATORIO_ARQUEROS + FILA_MIN_ELFO);
		columna_deseada=(rand()%RANGO_COLUMNA_ALEATORIO);
		while(juego->terreno[fila_deseada][columna_deseada]==ELFO){
			fila_deseada=(rand()%RANGO_NUMERO_ALEATORIO_ARQUEROS + FILA_MIN_ELFO);
			columna_deseada=(rand()%RANGO_COLUMNA_ALEATORIO);
		}
		juego->rohan[i].fila=fila_deseada;
		juego->rohan[i].columna=columna_deseada;
		juego->terreno[fila_deseada][columna_deseada]=ELFO;
	}
	for(int j=0;j<TOPE_PERSONAJES_INICIALES;j++){
		juego->cantidad_isengard++;
		juego->isengard[j].codigo=URUK;
		juego->isengard[j].llego_alfinal=false;
		juego->isengard[j].esta_vivo=true;
		juego->isengard[j].atacando=false;
		juego->isengard[j].vida=(VIDA_ARQUEROS-(juego->plus_isengard));
		juego->isengard[j].ataque=(ATAQUE_ARQUEROS+(juego->plus_isengard));
		fila_deseada=(rand()%RANGO_NUMERO_ALEATORIO_ARQUEROS + FILA_MIN_URUK);
		columna_deseada=(rand()%RANGO_COLUMNA_ALEATORIO);
		while(juego->terreno[fila_deseada][columna_deseada]==URUK){
			fila_deseada=(rand()%RANGO_NUMERO_ALEATORIO_ARQUEROS + FILA_MIN_URUK);
			columna_deseada=(rand()%RANGO_COLUMNA_ALEATORIO);
		}
		juego->isengard[j].fila=fila_deseada;
		juego->isengard[j].columna=columna_deseada;
		juego->terreno[fila_deseada][columna_deseada]=URUK;
	}
}
/*
 * Post: Devuelve una fila y columna validas en las cuales puede posicionarser un elfo.
 */
void cargar_elfo(char* tipo, int* fila, int* columna, juego_t* juego){
	int fila_deseada=0;
	int columna_deseada=0;

	printf("¿En que fila deseas colocarlos?(Entre la 5 y la 8).\n");
	scanf(" %d", &fila_deseada);
	while((fila_deseada<FILA_MIN_ELFO) || (fila_deseada>FILA_MAX_ELFO)){
		printf("Fila erronea, intente nuevamente entre la fila 5 y la 8.\n");
		scanf(" %d", &fila_deseada);
	}
	printf("¿En que columna deseas colocarlos?(Entre la 0 y la 9).\n");
	scanf(" %d", &columna_deseada);
	while((columna_deseada<PRIMER_COLUMNA) || (columna_deseada>ULTIMA_COLUMNA)){
		printf("Columna erronea, intente nuevamente entre la columna 0 y la 9.\n");
		scanf(" %d", &columna_deseada);
	}
	while(juego->terreno[fila_deseada][columna_deseada]==ELFO){
		printf("Posicion ocupada, intente nuevamente.\n");
		printf("¿En que fila deseas colocarlos?(Entre la 5 y la 8).\n");
		scanf(" %d", &fila_deseada);
		while((fila_deseada<FILA_MIN_ELFO) || (fila_deseada>FILA_MAX_ELFO)){
			printf("Fila erronea, intente nuevamente entre la fila 5 y la 8.\n");
			scanf(" %d", &fila_deseada);
		}
		printf("¿En que columna deseas colocarlos?(Entre la 0 y la 9).\n");
		scanf(" %d", &columna_deseada);
		while((columna_deseada<PRIMER_COLUMNA) || (columna_deseada>ULTIMA_COLUMNA)){
			printf("Columna erronea, intente nuevamente entre la columna 0 y la 9.\n");
			scanf(" %d", &columna_deseada);
		}
	}
	(*fila)=fila_deseada;
	(*columna)=columna_deseada;
}
/*
 * Post: Devuelve una fila y columna validas en las cuales puede posicionarse un hombre.
 */
void cargar_hombre(char* tipo, int* fila, int* columna, juego_t* juego){
	int columna_deseada=0;

	printf("¿En que columna deseas colocarlo?(Del 0 al 9).\n");
	scanf(" %d", &columna_deseada);
	while((columna_deseada<PRIMER_COLUMNA) || (columna_deseada>ULTIMA_COLUMNA)){
		printf("Columna erronea, intente nuevamente entre la columna 0 y la 9.\n");
		scanf(" %d", &columna_deseada);
	}
	while((juego->terreno[ULTIMA_FILA][columna_deseada])==HOMBRE){
		printf("Posicion ocupada, intente nuevamente.\n");
		printf("¿En que columna deseas colocarlos?(Entre la 0 y la 9).\n");
		scanf(" %d", &columna_deseada);
		while((columna_deseada<PRIMER_COLUMNA) || (columna_deseada>ULTIMA_COLUMNA)){
			printf("Columna erronea, intente nuevamente entre la columna 0 y la 9.\n");
			scanf(" %d", &columna_deseada);
		}
	}
	(*fila)=ULTIMA_FILA;
	(*columna)=columna_deseada;
}
/*
 * Post: Devuelve una fila y columna valida en las cuales puede posicionarse un uruk.
 */
void cargar_uruk(char* tipo, int* fila, int* columna, juego_t* juego){
	int fila_deseada=0;
	int columna_deseada=0;

	printf("¿En que fila deseas colocarlos?(Entre la 1 y la 4).\n");
	scanf(" %d", &fila_deseada);
	while((fila_deseada<FILA_MIN_URUK) || (fila_deseada>FILA_MAX_URUK)){
		printf("Fila erronea, intente nuevamente entre la fila 1 y la 4.\n");
		scanf(" %d", &fila_deseada);
	}
	printf("¿En que columna deseas colocarlos?(Entre la 0 y la 9).\n");
	scanf(" %d", &columna_deseada);
	while((columna_deseada<PRIMER_COLUMNA) || (columna_deseada>ULTIMA_COLUMNA)){
		printf("Columna erronea, intente nuevamente entre la columna 0 y la 9.\n");
		scanf(" %d", &columna_deseada);
	}
	while(juego->terreno[fila_deseada][columna_deseada]==URUK){
		printf("Posicion ocupada, intente nuevamente.\n");
		printf("¿En que fila deseas colocarlos?(Entre la 1 y la 4).\n");
		scanf(" %d", &fila_deseada);
		while((fila_deseada<FILA_MIN_URUK) || (fila_deseada>FILA_MAX_URUK)){
			printf("Fila erronea, intente nuevamente entre la fila 1 y la 4.\n");
			scanf(" %d", &fila_deseada);
		}
		printf("¿En que columna deseas colocarlos?(Entre la 0 y la 9).\n");
		scanf(" %d", &columna_deseada);
		while((columna_deseada<PRIMER_COLUMNA) || (columna_deseada>ULTIMA_COLUMNA)){
			printf("Columna erronea, intente nuevamente entre la columna 0 y la 9.\n");
			scanf(" %d", &columna_deseada);
		}
	}
	(*fila)=fila_deseada;
	(*columna)=columna_deseada;
}
/*
 * Post: Devuelve una fila y columna valida en las cuales puede posicionarse un orco.
 */
void cargar_orco(char* tipo, int* fila, int* columna, juego_t* juego){
	int columna_deseada=0;
	int fila_deseada=0;

	printf("¿En que columna deseas colocarlo?(Del 0 al 9)\n");
	scanf(" %d", &columna_deseada);
	while((columna_deseada<PRIMER_COLUMNA) || (columna_deseada>ULTIMA_COLUMNA)){
		printf("Columna erronea, intente nuevamente entre la columna 0 y la 9.\n");
		scanf(" %d", &columna_deseada);
	}
	while((juego->terreno[fila_deseada][columna_deseada])==ORCO){
		printf("Posicion ocupada, intente nuevamente.\n");
		printf("¿En que columna deseas colocarlos?(Entre la 0 y la 9).\n");
		scanf(" %d", &columna_deseada);
		while((columna_deseada<PRIMER_COLUMNA) || (columna_deseada>ULTIMA_COLUMNA)){
			printf("Columna erronea, intente nuevamente entre la columna 0 y la 9.\n");
			scanf(" %d", &columna_deseada);
		}
	}
	(*columna)=columna_deseada;
	(*fila)=PRIMER_FILA;
}
/*
 * 
 */
void preguntar_rohan(char* tipo, int* fila, int* columna, juego_t* juego, bool* cargar){
	char respuesta_rohan='p';
	char tipo_deseado='p';

	printf("Rohan ¿Deseas posicionar tropas este turno?(S/N)\n");
	scanf(" %c", &respuesta_rohan);
	while((respuesta_rohan!='S') && (respuesta_rohan!='N')){
		printf("¿Deseas posicionar tropas este turno?(S/N)\n");
		scanf(" %c", &respuesta_rohan);
	}
	if(respuesta_rohan=='S'){
		printf("De que tipo ¿Hombre(3 puntos) o Elfo (8 puntos)?(Use las iniciales para seleccionar.)\n");
		scanf(" %c", &tipo_deseado);
		while((tipo_deseado!=HOMBRE) && (tipo_deseado!=ELFO)){
			printf("De que tipo ¿Hombre(3 puntos) o Elfo (8 puntos)?(Use las iniciales para seleccionar.)\n");
			scanf(" %c", &tipo_deseado);
		}
		if((tipo_deseado==ELFO) && ((juego->energia_rohan)>=COSTO_ARQUERO)){
			juego->energia_rohan-=COSTO_ARQUERO;
			(*tipo)=ELFO;
			(*cargar)=true;
			cargar_elfo(tipo, fila, columna, juego);
		}
		else if((tipo_deseado==ELFO) && ((juego->energia_rohan)<COSTO_ARQUERO) && ((juego->energia_rohan)>=COSTO_SOLDADOS)){
			printf("Disculpa pero no tienes energia suficiente para lanzar un Elfo, ¿deseas lanzar un hombre?(S/N)\n");
			scanf(" %c", &respuesta_rohan);
			while((respuesta_rohan!='S') && (respuesta_rohan!='N')){
				printf("¿Deseas posicionar tropas este turno?(S/N)\n");
				scanf(" %c", &respuesta_rohan);
			}
			if(respuesta_rohan=='S'){
				juego->energia_rohan-=COSTO_SOLDADOS;
				(*tipo)=HOMBRE;
				(*cargar)=true;
				cargar_hombre(tipo, fila, columna, juego);
			}
			else if(respuesta_rohan=='N'){
				printf("Perfecto guardaras energia para tu siguiente turno.\n");
			}
		}
		else if((tipo_deseado==ELFO) && ((juego->energia_rohan)<COSTO_SOLDADOS)){
			printf("Disculpa no tiene suficiente energia para posicionar un Elfo, tampoco para posicionar a un hombre asique termina tu turno.\n");
		}
		else if((tipo_deseado==HOMBRE) && ((juego->energia_rohan)>=COSTO_SOLDADOS)){
			juego->energia_rohan-=COSTO_SOLDADOS;
			(*tipo)=HOMBRE;
			(*cargar)=true;
			cargar_hombre(tipo, fila, columna, juego);	
		}
		else if((tipo_deseado==HOMBRE) && ((juego->energia_rohan)<COSTO_SOLDADOS)){
			printf("No cuentas con energia suficiente para lanzar un Hombre, termina tu turno.\n");
		}
	}
	else if(respuesta_rohan=='N'){
		printf("Okay, guardas energias para tu proximo turno.\n");
	}
	(juego->energia_rohan)++;
}
/*
 * 
 */
void preguntar_isengard(char* tipo, int* fila, int* columna, juego_t* juego, bool* cargar){
	char respuesta_isengard='p';
	char tipo_deseado='p';

	printf("Isengard ¿Deseas posicionar tropas este turno?(S/N)\n");
	scanf(" %c", &respuesta_isengard);
	while((respuesta_isengard!='S') && (respuesta_isengard!='N')){
		printf("¿Deseas posicionar tropas este turno?(S/N)\n");
		scanf(" %c", &respuesta_isengard);
	}
	if(respuesta_isengard=='S'){
		printf("De que tipo ¿Orco(3 puntos) o Uruk-hai (8 puntos)?(Use las iniciales para seleccionar, cualquier otro caracter termina tu turno.)\n");
		scanf(" %c", &tipo_deseado);
		while((tipo_deseado!=ORCO) && (tipo_deseado!=URUK)){
			printf("De que tipo ¿Orco(3 puntos) o Uruk(8 puntos)?(Use las iniciales para seleccionar.)\n");
			scanf(" %c", &tipo_deseado);
		}
		if((tipo_deseado==URUK) && ((juego->energia_isengard)>=COSTO_ARQUERO)){
			juego->energia_isengard-=COSTO_ARQUERO;
			(*tipo)=URUK;
			(*cargar)=true;
			cargar_uruk(tipo, fila, columna, juego);
		}
		else if((tipo_deseado==URUK) && ((juego->energia_isengard)<COSTO_ARQUERO) && ((juego->energia_isengard)>=COSTO_SOLDADOS)){
			printf("Disculpa pero no tienes energia suficiente para lanzar un Uruk, ¿deseas lanzar un Orco?(S/N)\n");
			scanf(" %c", &respuesta_isengard);
			while((respuesta_isengard!='S') && (respuesta_isengard!='N')){
				printf("¿Deseas posicionar tropas este turno?(S/N)\n");
				scanf(" %c", &respuesta_isengard);
			}
			if(respuesta_isengard=='S'){
				juego->energia_isengard-=COSTO_SOLDADOS;
				(*tipo)=ORCO;
				(*cargar)=true;
				cargar_orco(tipo, fila, columna, juego);
			}
			else if(respuesta_isengard=='N'){
				printf("Perfecto guardaras energia para tu siguiente turno.\n");
			}
		}
		else if((tipo_deseado==URUK) && ((juego->energia_isengard)<COSTO_SOLDADOS)){
			printf("Disculpa no tiene suficiente energia para posicionar un Uruk, tampoco para posicionar a un Orco asique termina tu turno.\n");
		}
		else if((tipo_deseado==ORCO) && ((juego->energia_isengard)>=COSTO_SOLDADOS)){
			juego->energia_isengard-=COSTO_SOLDADOS;
			(*tipo)=ORCO;
			(*cargar)=true;
			cargar_orco(tipo, fila, columna, juego);	
		}
		else if((tipo_deseado==ORCO) && ((juego->energia_isengard)<COSTO_SOLDADOS)){
			printf("No cuentas con energia suficiente para lanzar un Orco, termina tu turno.\n");
		}
	}
	else if(respuesta_isengard=='N'){
		printf("Okay, guardas energias para tu proximo turno.\n");
	}
	(juego->energia_isengard)++;
}
/*
 * 
 */
personaje_t crear_personaje(char* tipo, int* fila, int* columna, juego_t* juego){
	personaje_t personaje;

	personaje.fila=(*fila);
	personaje.columna=(*columna);
	personaje.esta_vivo=true;
	personaje.llego_alfinal=false;
	personaje.atacando=false;
	personaje.codigo=(*tipo);
	
	if((*tipo)==ELFO){
		personaje.vida=(VIDA_ARQUEROS-(juego->plus_rohan));
		personaje.ataque=(ATAQUE_ARQUEROS+(juego->plus_rohan));
	}
	else if((*tipo)==URUK){
		personaje.vida=(VIDA_ARQUEROS-(juego->plus_isengard));
		personaje.ataque=(ATAQUE_ARQUEROS+(juego->plus_isengard));
	}
	else if((*tipo)==HOMBRE){
		personaje.vida=(VIDA_SOLDADOS-(juego->plus_rohan));
		personaje.ataque=(ATAQUE_SOLDADOS+(juego->plus_rohan));	
	}
	else if((*tipo)==ORCO){
		personaje.vida=(VIDA_SOLDADOS-(juego->plus_isengard));
		personaje.ataque=(ATAQUE_SOLDADOS+(juego->plus_isengard));
	}
	return personaje;
}
/*
 * Pre: Recibe las posiciones de un arquero (elfo/uruk) y del enemigo objetivo.
 * Post: Devuelve la distancia manhathan entre ellos.
 */
int distancia_manhattan(int fila_atacante, int fila_atacado, int columna_atacado, int columna_atacante){
	return (abs((fila_atacante)-(fila_atacado))+abs((columna_atacante)-(columna_atacado)));
}
/*
 * Pre: Recibe un elfo perfectamente cargado.
 * Post: Se encarga de restarle vida a los enemigos que se encuentren dentro del rango de ataque del elfo determinado por posicion_personaje.
 */
void ataque_elfos(juego_t* juego, int posicion_personaje){
	int distancia_puntos=0;
	int fila_atacante=0;
	int fila_atacado=0;
	int columna_atacante=0;
	int columna_atacado=0;

	if((juego->rohan[posicion_personaje].codigo==ELFO) && (juego->rohan[posicion_personaje].esta_vivo==true)){
		for(int j=0;j<(juego->cantidad_isengard);j++){
			fila_atacante=(juego->rohan[posicion_personaje].fila);
			columna_atacante=(juego->rohan[posicion_personaje].columna);
			fila_atacado=(juego->isengard[j].fila);
			columna_atacado=(juego->isengard[j].columna);

			distancia_puntos=distancia_manhattan(fila_atacante, fila_atacado, columna_atacado, columna_atacante);
			if((distancia_puntos<=DISTANCIA_MAX_ATAQUE_ARQUEROS) && (juego->isengard[j].llego_alfinal==false) && (juego->isengard[j].esta_vivo==true)){
				(juego->isengard[j].vida)-=(juego->rohan[posicion_personaje].ataque);
			}
			if((juego->isengard[j].vida)<=VIDA_MIN){
				juego->isengard[j].esta_vivo=false;
			}
		}
	}
}
/*
 * 
 */
void preguntar_pc(juego_t* juego, char* tipo, int* fila, int* columna, bool* cargar){
	if(juego->pc_coloco_este_turno==false){
		if(juego->bando_pc==ROHAN){
			juego->energia_rohan++;
			if(juego->energia_rohan>=COSTO_SOLDADOS){
				juego->energia_rohan-=COSTO_SOLDADOS;
				(*tipo)=HOMBRE;
				(*cargar)=true;
				(*columna)=rand()%RANGO_COLUMNA_ALEATORIO;
				(*fila)=ULTIMA_FILA;
				while(juego->terreno[(*fila)][(*columna)]==HOMBRE){
					(*columna)=rand()%RANGO_COLUMNA_ALEATORIO;
				}
			}
		}
		else if(juego->bando_pc==ISENGARD){
			juego->energia_isengard++;
			if(juego->energia_isengard>=COSTO_SOLDADOS){
				juego->energia_isengard-=COSTO_SOLDADOS;
				(*tipo)=ORCO;
				(*cargar)=true;
				(*columna)=rand()%RANGO_COLUMNA_ALEATORIO;
				(*fila)=PRIMER_FILA;
				while(juego->terreno[(*fila)][(*columna)]==ORCO){
					(*columna)=rand()%RANGO_COLUMNA_ALEATORIO;
				}
			}
		}
	}
}
/*
 * Pre: Recibe un uruk perfectamente cargado.
 * Post: Se encarga de restarle vida a los enemigos que se encuentren dentro del rango de ataque del uruk determinado por posicion_personaje.
 */
void ataque_uruks(juego_t* juego, int posicion_personaje){
	int distancia_puntos=0;
	int fila_atacante=0;
	int fila_atacado=0;
	int columna_atacante=0;
	int columna_atacado=0;

	if((juego->isengard[posicion_personaje].esta_vivo==true) && (juego->isengard[posicion_personaje].codigo==URUK)){
		for(int j=0;j<(juego->cantidad_rohan);j++){
			fila_atacante=(juego->isengard[posicion_personaje].fila);
			columna_atacante=(juego->isengard[posicion_personaje].columna);
			fila_atacado=(juego->rohan[j].fila);
			columna_atacado=(juego->rohan[j].columna);

			distancia_puntos=distancia_manhattan(fila_atacante, fila_atacado, columna_atacado, columna_atacante);
			if((distancia_puntos<=DISTANCIA_MAX_ATAQUE_ARQUEROS) && (juego->rohan[j].llego_alfinal==false) && (juego->rohan[j].esta_vivo==true)){
				(juego->rohan[j].vida)-=(juego->isengard[posicion_personaje].ataque);
			}
			if((juego->rohan[j].vida)<=VIDA_MIN){
				juego->rohan[j].esta_vivo=false;
			}
		}
	}		
}
/*
 * Pre: Recibe un hombre perfectamente cargado.
 * Post: Se encarga de cambiar la posicion del hombre dentro del vector de Rohan.
 */
void mover_hombres(juego_t* juego, int posicion_personaje){
	if((juego->rohan[posicion_personaje].fila)>=PRIMER_FILA+1){
		(juego->rohan[posicion_personaje].fila)-=1;
	}
	if((juego->rohan[posicion_personaje].fila==PRIMER_FILA) && (juego->rohan[posicion_personaje].esta_vivo==true)){
		juego->llegadas_rohan++;
		(juego->rohan[posicion_personaje].codigo)=VACIO;
		(juego->rohan[posicion_personaje].llego_alfinal)=true;	
	}
}
/*
 * Pre: Recibe un orco perfectamente cargado.
 * Post: Se encarga de cambiar la posicion del orco dentro del vector de Isengard.
 */
void mover_orcos(juego_t* juego, int posicion_personaje){
	if((juego->isengard[posicion_personaje].fila)<=ULTIMA_FILA-1){
		(juego->isengard[posicion_personaje].fila)+=1;
	}
	if(((juego->isengard[posicion_personaje].fila)==ULTIMA_FILA) && ((juego->isengard[posicion_personaje].esta_vivo)==true)){
		(juego->llegadas_isengard)++;
		(juego->isengard[posicion_personaje].codigo)=VACIO;
		(juego->isengard[posicion_personaje].llego_alfinal)=true;
	}
}
/*
 * Pre: Recibe un hombre perfectamente cargado.
 * Post: Se encarga de restarle vida a al primer enemigo que se encuentre dentro de su rango.
 */
void atacar_hombres(juego_t* juego, int posicion_personaje){
	int columna_hombre=(juego->rohan[posicion_personaje].columna);
	int fila_hombre=(juego->rohan[posicion_personaje].fila);
	int fila_enemigo=0;
	int columna_enemigo=0;
	int contador=0; 
	bool enemigo_cercano=false;
	bool enemigo_encontrado=false;

	if((juego->rohan[posicion_personaje].esta_vivo==true) && (juego->rohan[posicion_personaje].llego_alfinal==false)){
		for(int i= (fila_hombre-1); i<=(fila_hombre+1); i++){
			for(int j=(columna_hombre-1); j<=(columna_hombre+1); j++){
				if((i>=PRIMER_FILA) && (i<=ULTIMA_FILA) && (j>=PRIMER_COLUMNA) && (j<=ULTIMA_COLUMNA)){
					if(((juego->terreno[i][j]==ORCO)||(juego->terreno[i][j]==URUK))&&(enemigo_cercano==false)){
						enemigo_cercano=true;
						fila_enemigo=i;
						columna_enemigo=j;
					}
				}
			}
		}
		if(enemigo_cercano==true){
			while(enemigo_encontrado==false && contador < juego->cantidad_isengard){
				if((juego->isengard[contador].fila==fila_enemigo) && (juego->isengard[contador].columna==columna_enemigo) && (juego->isengard[contador].esta_vivo==true) && (juego->isengard[contador].llego_alfinal==false)){
					juego->isengard[contador].vida-=juego->rohan[posicion_personaje].ataque;
					juego->rohan[posicion_personaje].atacando=true;
					enemigo_encontrado=true;
				}
				if((juego->isengard[contador].vida)<=VIDA_MIN){
					juego->isengard[contador].esta_vivo=false;
				}
				contador++;
			}
		}
		if(enemigo_cercano==false){
			juego->rohan[posicion_personaje].atacando=false;
		}
	}
}
/*
 * Pre: Recibe un orco perfectamente cargado.
 * Post: Se encarga de restarle vida al primer enemigo dentro de su rango de ataque.
 */
void atacar_orcos(juego_t* juego, int posicion_personaje){
	int columna_orco=(juego->isengard[posicion_personaje].columna);
	int fila_orco=(juego->isengard[posicion_personaje].fila);
	int fila_enemigo=0;
	int columna_enemigo=0;
	int contador=0; 
	bool enemigo_cercano=false;
	bool enemigo_encontrado=false;

	if((juego->isengard[posicion_personaje].esta_vivo==true) && (juego->isengard[posicion_personaje].llego_alfinal==false)){
		for(int i= (fila_orco-1); i<=(fila_orco+1); i++){
			for(int j=(columna_orco-1); j<=(columna_orco+1); j++){
				if((i>=PRIMER_FILA) && (i<=ULTIMA_FILA) && (j>=PRIMER_COLUMNA) && (j<=ULTIMA_COLUMNA)){
					if(((juego->terreno[i][j]==HOMBRE) || (juego->terreno[i][j]==ELFO)) && (enemigo_cercano==false)){
						enemigo_cercano=true;
						fila_enemigo=i;
						columna_enemigo=j;
					}
				}
			}
		}
		if(enemigo_cercano==true){
			while(enemigo_encontrado==false && contador < juego->cantidad_rohan){
				if((juego->rohan[contador].fila==fila_enemigo) && (juego->rohan[contador].columna==columna_enemigo) && (juego->rohan[contador].esta_vivo==true) && (juego->rohan[contador].llego_alfinal==false)){
					juego->rohan[contador].vida-=juego->isengard[posicion_personaje].ataque;
					juego->isengard[posicion_personaje].atacando=true;
					enemigo_encontrado=true;
				}
				if((juego->rohan[contador].vida)<=VIDA_MIN){
					juego->rohan[contador].esta_vivo=false;
				}
				contador++;
			}
		}
		if(enemigo_cercano==false){
			juego->isengard[posicion_personaje].atacando=false;
		}
	}
}
/*
 * 
 */
void inicializar_juego(juego_t* juego){
	char tipo='t';
	personaje_t personaje;
	int intensidad=0;
	int intensidad_rival=10;
	perfil(&tipo, &intensidad);
	cargar_plus(juego, tipo, intensidad, &intensidad_rival);
	preguntar_cantidad_jugadores(juego);
	determinar_bando_jugadores(juego, tipo, intensidad, &intensidad_rival);
	rellenar_campo_de_juego(juego);
	iniciar_contadores(juego);
	cargador_personajes_iniciales(juego, personaje);
}
/*
 * 
 */
void posicionar_personaje(juego_t* juego, personaje_t personaje){
	/*Pongo esto aqui para que se pasen las pruebas*/
	personaje.esta_vivo=true;
	personaje.llego_alfinal=false;
	personaje.atacando=false;
	/*Pongo esto aqui para que se pasen las pruebas*/

	if((personaje.codigo==ELFO) || (personaje.codigo==HOMBRE)){
		juego->rohan[juego->cantidad_rohan]=personaje;
		(juego->cantidad_rohan)++;
	}
	else if((personaje.codigo==URUK) || (personaje.codigo==ORCO)){
		juego->isengard[juego->cantidad_isengard]=personaje;
		(juego->cantidad_isengard)++;
	}

	actualizar_matriz(juego);
}
/*
 * 
 */
void jugar(juego_t* juego, char bando, int posicion_personaje){
	if(bando==ROHAN){
		if(juego->rohan[posicion_personaje].codigo==ELFO){
			ataque_elfos(juego, posicion_personaje);
		}
		else if((juego->rohan[posicion_personaje].codigo)==HOMBRE){
			atacar_hombres(juego, posicion_personaje);
			if(juego->rohan[posicion_personaje].atacando==false){
				mover_hombres(juego, posicion_personaje);
			}
		}
		actualizar_matriz(juego);
	}
	if(bando==ISENGARD){
		if((juego->isengard[posicion_personaje].codigo)==URUK){
			ataque_uruks(juego, posicion_personaje);
		}
		else if((juego->isengard[posicion_personaje].codigo)==ORCO){
			atacar_orcos(juego, posicion_personaje);
			if(juego->isengard[posicion_personaje].atacando==false){
				mover_orcos(juego, posicion_personaje);
			}
		}
		actualizar_matriz(juego);
	}
}
/*
 * 
 */
 void detectar_ganador(juego_t* juego){
	system("clear");
	if(juego->llegadas_rohan>=LLEGADAS_VICTORIA){
		printf("GANO ROJAN!!!\n");
	}
	else if(juego->llegadas_isengard>=LLEGADAS_VICTORIA){
		printf("GANO ISENGARD!!!\n");
	}
}