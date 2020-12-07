#include <stdio.h>
const int CALORIAS_MAXIMAS = 2400;
const int CALORIAS_MINIMAS = 2000;

int main(){
	int calorias_totales = 0;
	int calorias_comida;

	printf("dame una caloria. Ingresa 0 para salir.");
	scanf("%i", &calorias_comida);
	while(calorias_comida > 0){
		calorias_totales += calorias_comida;
		printf("dame una caloria. Ingresa 0 para salir.");
		scanf("%i", &calorias_comida);
	}



	return 0;
}