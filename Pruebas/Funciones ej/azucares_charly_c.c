#include <stdio.h>

/*
 * Pre: valores enteros positivos.
 * Post: si el entero es positivo, es vuelto y si es negativo, es deuda.
 */
int calcular_vuelto(int plata, int valor){
	int resultado;
	resultado = plata - valor;
	return resultado;
}

void pedir_valor_positivo(int* valor){
	printf("Ingresa un valor positivo\n");
	scanf("%i", valor);

	while((*valor) < 0){
		printf("El valor tiene que ser mayor que 0!.\n");
		scanf("%i", valor);
	}
}

void mostrar_mensaje(int vuelto){
	if (vuelto < 0) {
		printf("Te falta plata amiguero! %i pesos.\n", vuelto);
	} else {
		printf("Te sobran %i pesos.\n", vuelto);
	}
}

int platos_a_comprar(int plata, int precio, int* vuelto){
	int platos = 0;
	while(plata >= precio/(platos+1)){
		platos++;
		plata -= precio/platos;
	}
	(*vuelto) = plata;
	return platos;
}

int main(){
	int plata_charly;
	int vuelto_charly;
	int valor_comida;

	printf("PLATA:\n");
	pedir_valor_positivo(&plata_charly);

	printf("VALOR DE LA COMIDA:\n");
	pedir_valor_positivo(&valor_comida);

	int cantidad_platos = platos_a_comprar(plata_charly, valor_comida, &vuelto_charly);

	mostrar_mensaje(vuelto_charly);

	return 0;
}

//YBARRA ESTA MAL EL MAIL. LE FALTA EL .AR.. NO ESTA EN SLACK