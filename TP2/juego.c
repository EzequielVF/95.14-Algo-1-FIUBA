#include"batalla.h"

#define LLEGADAS_VICTORIA 5
#define ROHAN 'R'
#define ISENGARD 'I'

int main(){
	srand((unsigned)time(NULL));
	juego_t juego;
	personaje_t personaje;
	char bando='m';
	char tipo='p';
	int posicion_personaje=0;
	int fila=0;
	int columna=0;
	bool cargar=false;

	inicializar_juego(&juego);

	while(((juego.llegadas_rohan)<LLEGADAS_VICTORIA)&&((juego.llegadas_isengard)<LLEGADAS_VICTORIA)){
		mostrar_informacion_juego(&juego);
		juego.pc_coloco_este_turno=false;
		
		if((juego.cantidad_jugadores==2)||(juego.bando_pc==ISENGARD)){
			preguntar_rohan(&tipo, &fila, &columna, &juego, &cargar);
			if(cargar==true){
				personaje = crear_personaje(&tipo, &fila, &columna, &juego);
				posicionar_personaje(&juego, personaje);
				cargar=false;
			}
		}
		else if((juego.bando_pc==ROHAN)&&(juego.pc_coloco_este_turno==false)){
			preguntar_pc(&juego, &tipo, &fila, &columna, &cargar);
			if(cargar==true){
				personaje = crear_personaje(&tipo, &fila, &columna, &juego);
				posicionar_personaje(&juego, personaje);
				cargar=false;
				juego.pc_coloco_este_turno=true;
			}
		}
		mostrar_informacion_juego(&juego);
		if((juego.cantidad_jugadores==2)||(juego.bando_pc==ROHAN)){
			preguntar_isengard(&tipo, &fila, &columna, &juego, &cargar);
			if(cargar==true){
				personaje = crear_personaje(&tipo, &fila, &columna, &juego);
				posicionar_personaje(&juego, personaje);
				cargar=false;
			}
		}
		else if((juego.bando_pc==ISENGARD)&&(juego.pc_coloco_este_turno==false)){
			preguntar_pc(&juego, &tipo, &fila, &columna, &cargar);
			if(cargar==true){
				personaje = crear_personaje(&tipo, &fila, &columna, &juego);
				posicionar_personaje(&juego, personaje);
				cargar=false;
				juego.pc_coloco_este_turno=true;
			}
		}
		mostrar_informacion_juego(&juego);
		bando=ROHAN;
		for(int i=0;i<(juego.cantidad_rohan);i++){
			posicion_personaje=i;
			jugar(&juego, bando, posicion_personaje);
			mostrar_informacion_juego(&juego);
		}
		bando=ISENGARD;
		posicion_personaje=0;
		for(int j=0;j<(juego.cantidad_isengard);j++){
			posicion_personaje=j;
			jugar(&juego, bando, posicion_personaje);
			mostrar_informacion_juego(&juego);
		}
	}
	detectar_ganador(&juego);

	return 0;
}