#include <stdio.h>

const int SIGNO_MAX =12;
const int SIGNO_MIN =1;
const int MALDADES_MAX =99;
const int MALDADES_MIN =0;
const int MASCOTAS_MIN =0;
const int MASCOTAS_MAX =5;
const int OFENSIVO = 1;
const int DEFENSIVO = 2;
const int NO_CLASIFICADO =0;
const int LIMITE_CLASIFICATIVO_MALDADES =50;
const int ARIES =1;
const int TAURO =2;
const int GEMINIS =3;
const int CANCER =4;
const int LEO =5;
const int VIRGO =6;
const int LIBRA =7;
const int ESCORPIO =8;
const int SAGITARIO =9;
const int CAPRICORNIO =10;
const int ACUARIO =11;
const int PISCIS =12;
const int UN_PUNTO =1;
const int DOS_PUNTOS =2;
const int TRES_PUNTOS =3;
const int CUATRO_PUNTOS =4;
const int CINCO_PUNTOS =5;
const int UN_PUNTO_INTENSIDAD_DEFENSIVO_MIN =0;
const int UN_PUNTO_INTENSIDAD_DEFENSIVO_MAX =9;
const int DOS_PUNTOS_INTENSIDAD_DEFENSIVO_MIN =10;
const int DOS_PUNTOS_INTENSIDAD_DEFENSIVO_MAX =19;
const int TRES_PUNTOS_INTENSIDAD_DEFENSIVO_MIN =20;
const int TRES_PUNTOS_INTENSIDAD_DEFENSIVO_MAX =29;
const int CUATRO_PUNTOS_INTENSIDAD_DEFENSIVO_MIN =30;
const int CUATRO_PUNTOS_INTENSIDAD_DEFENSIVO_MAX =39;
const int CINCO_PUNTOS_INTENSIDAD_DEFENSIVO_MIN =40;
const int CINCO_PUNTOS_INTENSIDAD_DEFENSIVO_MAX =49;
const int UN_PUNTO_INTENSIDAD_OFENSIVO_MIN =50;
const int UN_PUNTO_INTENSIDAD_OFENSIVO_MAX =59;
const int DOS_PUNTOS_INTENSIDAD_OFENSIVO_MIN =60;
const int DOS_PUNTOS_INTENSIDAD_OFENSIVO_MAX =69;
const int TRES_PUNTOS_INTENSIDAD_OFENSIVO_MIN =70;
const int TRES_PUNTOS_INTENSIDAD_OFENSIVO_MAX =79;
const int CUATRO_PUNTOS_INTENSIDAD_OFENSIVO_MIN =80;
const int CUATRO_PUNTOS_INTENSIDAD_OFENSIVO_MAX =89;
const int CINCO_PUNTOS_INTENSIDAD_OFENSIVO_MIN =90;
const int CINCO_PUNTOS_INTENSIDAD_OFENSIVO_MAX =99;
const char ACCION ='A';
const char COMEDIA ='C';
const char DRAMA ='D';
const char TERROR ='T';

void mostrar_mensaje_bienvenida(){
	printf("Bienvenido amigo mio, asique ¿quieres unirte a la batalla?\nPorfavor completa las siguientes preguntas asi determinaremos a que bando perteneces\nBuena suerte camarada, la necesitaras.\n");
}

/*
 * Pre: Valores enteros positivos entre 0 y 12.
 * Post: Devuelte un entero positivo que sera el valor del signo.
 */
void pedir_signo_valido(int* valor_signo){
 	printf("¿Cual es tu signo del zodiaco?\n1:Aries, 2:Tauro, 3:Géminis, 4:Cáncer, 5:Leo, 6:Virgo,7:Libra, 8:Escorpio, 9:Sagitario, 10:Capricornio, 11:Acuario, 12:Piscis\n");
 	scanf("%i", valor_signo);

 	while((*valor_signo)<SIGNO_MIN||(*valor_signo)>SIGNO_MAX){
 		printf("Porfavor ingrese un signo valido!\n");
		scanf("%i", valor_signo);
	}
}

/*
 * Pre: Valores caracteres A, C, D y T.
 * Post: Devuelve un caracter que sera el que determine el genero preferido.
 */
void pedir_genero_valido(char* valor_genero){
 	printf("¿Cual es tu genero de cine preferido?\nAccion=A,Comedia=C,DramaD,Terror=T\n");
 	scanf(" %c", valor_genero);

	while(((*valor_genero)!=ACCION&&(*valor_genero)!=COMEDIA)&&((*valor_genero)!=DRAMA&&(*valor_genero)!=TERROR)){
    	printf("Porfavor ingrese un caracter valido!\n");
    	scanf(" %c", valor_genero);
  	}
}

/*
 * Pre: Valores enteros positivos entre 0 y 99.
 * Post: Devuelve un entero positivo que es la cantidad de maldades en ultimo mes.
 */
void pedir_maldades_valido(int* valor_maldades){
	printf("¿Cuantas maldades llevas en el ultimo mes?(Entre 0 y 99)\n");
  	scanf("%i", valor_maldades);

  	while((*valor_maldades)<MALDADES_MIN||(*valor_maldades)>MALDADES_MAX){
    	printf("Porfavor ingrese una cantidad de maldades valida!\n");
    	scanf("%i", valor_maldades);
  	}
}

/*
 * Pre: Valores enteros positivos entre 0 y 5.
 * Post: Devuelve un entero que representa la cantidad de mascotas que tiene el usuario.
 */
void pedir_mascotas_valido(int* valor_mascotas){
 	printf("¿Cuantas mascotas tenes?(Entre 0 y 5 (5 signfica 5 o mas))\n");
  	scanf("%i", valor_mascotas);

  	while((*valor_mascotas)<MASCOTAS_MIN||(*valor_mascotas)>MASCOTAS_MAX){
    	printf("Porfavor ingrese una cantidad de mascotas valida!\n");
    	scanf("%i", valor_mascotas);
  	}
}

/*
 * Pre: Recibe el signo en forma de entero, el genero en forma de caracter, las maldades en forma de entero y las mascotas en forma de entero.
 * Post: Devuelve el bando en el que esta el usuario.
 */
int determina_defensivo_ofensivo(int signo, char genero, int* maldades, int* mascotas){
 	int medidor_ofensivo_defensivo =0;

  	if((signo==ARIES||signo==LEO||signo==SAGITARIO||signo==GEMINIS||signo==LIBRA||signo==ACUARIO)&&(genero==COMEDIA||genero==TERROR)&&((*maldades)>=LIMITE_CLASIFICATIVO_MALDADES)&&((*mascotas)>=MASCOTAS_MIN&&(*mascotas)<=MASCOTAS_MAX)){
    	medidor_ofensivo_defensivo=OFENSIVO;
  	}
  	else if((signo==TAURO||signo==VIRGO||signo==CAPRICORNIO||signo==CANCER||signo==ESCORPIO||signo==PISCIS)&&(genero==ACCION||genero==DRAMA)&&((*maldades)<LIMITE_CLASIFICATIVO_MALDADES)&&((*mascotas)>=MASCOTAS_MIN&&(*mascotas)<=MASCOTAS_MAX)){
    	medidor_ofensivo_defensivo=DEFENSIVO;
  	}else{
    	medidor_ofensivo_defensivo=NO_CLASIFICADO;
  	}
  return medidor_ofensivo_defensivo;
 }

/*
 * Pre: Recibe el bando, si este es  OFENSIVO, DEFENSIVO, NO_CLASIFICADO.
 * Post: Si el bando recibido es NO_CLASIFICADO, repetira las preguntas hasta que este sea OFENSIVO O DEFENSIVO.
 */
 void repetir_preguntas(int signo, char genero, int* maldades, int* mascotas, int* bando){
  	
  	while((*bando)==NO_CLASIFICADO){
		
		printf("Lo siento, no se te a podido establecer en un bando, porfavor intentalo nuevamente y rapido porque la batalla se acerca.\n");

    	pedir_signo_valido(&signo);

    	pedir_genero_valido(&genero);

    	pedir_maldades_valido(maldades);

    	pedir_mascotas_valido(mascotas);

  		if((signo==ARIES||signo==LEO||signo==SAGITARIO||signo==GEMINIS||signo==LIBRA||signo==ACUARIO)&&(genero==COMEDIA||genero==TERROR)&&((*maldades)>=LIMITE_CLASIFICATIVO_MALDADES)&&((*mascotas)>=MASCOTAS_MIN&&(*mascotas)<=MASCOTAS_MAX)){
    		(*bando)=OFENSIVO;
  		}
  		else if((signo==TAURO||signo==VIRGO||signo==CAPRICORNIO||signo==CANCER||signo==ESCORPIO||signo==PISCIS)&&(genero==ACCION||genero==DRAMA)&&((*maldades)<LIMITE_CLASIFICATIVO_MALDADES)&&((*mascotas)>=MASCOTAS_MIN&&(*mascotas)<=MASCOTAS_MAX)){
    		(*bando)=DEFENSIVO;
  		}else{
    		(*bando)=NO_CLASIFICADO;
  		}
  	}
}

/*
 * Pre: Recibe dos enteros positivos como mascotas y maldades.
 * Post: Genera el nivel de intensidad del usuario en forma de entero.
 */
int calcula_intensidad(int maldades, int mascotas){
  	int puntos =0;

  	if((maldades>=UN_PUNTO_INTENSIDAD_DEFENSIVO_MIN&&maldades<=UN_PUNTO_INTENSIDAD_DEFENSIVO_MAX)||(maldades>=UN_PUNTO_INTENSIDAD_OFENSIVO_MIN&&maldades<=UN_PUNTO_INTENSIDAD_OFENSIVO_MAX)){
    	puntos=UN_PUNTO+mascotas;
  	}
  	else if((maldades>=DOS_PUNTOS_INTENSIDAD_DEFENSIVO_MIN&&maldades<=DOS_PUNTOS_INTENSIDAD_DEFENSIVO_MAX)||(maldades>=DOS_PUNTOS_INTENSIDAD_OFENSIVO_MIN&&maldades<=DOS_PUNTOS_INTENSIDAD_OFENSIVO_MAX)){
    	puntos=DOS_PUNTOS+mascotas;
  	}
  	else if((maldades>=TRES_PUNTOS_INTENSIDAD_DEFENSIVO_MIN&&maldades<=TRES_PUNTOS_INTENSIDAD_DEFENSIVO_MAX)||(maldades>=TRES_PUNTOS_INTENSIDAD_OFENSIVO_MIN&&maldades<=TRES_PUNTOS_INTENSIDAD_OFENSIVO_MAX)){
    	puntos=TRES_PUNTOS+mascotas;
  	}
  	else if((maldades>=CUATRO_PUNTOS_INTENSIDAD_DEFENSIVO_MIN&&maldades<=CUATRO_PUNTOS_INTENSIDAD_DEFENSIVO_MAX)||(maldades>=CUATRO_PUNTOS_INTENSIDAD_OFENSIVO_MIN&&maldades<=CUATRO_PUNTOS_INTENSIDAD_OFENSIVO_MAX)){
    	puntos=CUATRO_PUNTOS+mascotas;
  	}
  	else if((maldades>=CINCO_PUNTOS_INTENSIDAD_OFENSIVO_MIN&&maldades<=CINCO_PUNTOS_INTENSIDAD_DEFENSIVO_MAX)||(maldades>=CINCO_PUNTOS_INTENSIDAD_OFENSIVO_MIN&&maldades<=CINCO_PUNTOS_INTENSIDAD_OFENSIVO_MAX)){
    	puntos=CINCO_PUNTOS+mascotas;
  	}
  	return puntos;
}

/*
 * Pre: Recibe el bando y el nivel de intensidad en forma de enteros.
 * Post: Imprime el nivel y el bando del usuario.
 */
void mostrar_bando_intensidad(int bando, int intensidad){
  	if(bando==OFENSIVO){
    	printf("Estas del bando ofensivo y tu nivel es %i amigo mio, pelea con honor y recupera la tierra media para Sauron.\n", intensidad);
  	}
  	else if(bando==DEFENSIVO){
 		printf("Estas del bando defensivo y tu nivel es %i mi querido hobbit, pelea codo a codo con Legolas, Gimli y Aragorn, defiende la tierra media.\n", intensidad);
  	}
}

int main(){
 	int signo;
 	char genero;
 	int maldades;
 	int mascotas;
	int bando=0;
	int intensidad=0;

  	mostrar_mensaje_bienvenida();

  	pedir_signo_valido(&signo);

  	pedir_genero_valido(&genero);

  	pedir_maldades_valido(&maldades);

  	pedir_mascotas_valido(&mascotas);

  	bando=determina_defensivo_ofensivo(signo, genero,&maldades,&mascotas);

  	repetir_preguntas(signo, genero,&maldades,&mascotas, &bando);

  	intensidad=calcula_intensidad(maldades, mascotas);

  	mostrar_bando_intensidad(bando, intensidad); 

  	return 0;
}
