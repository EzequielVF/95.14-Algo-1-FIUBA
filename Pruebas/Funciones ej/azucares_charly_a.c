#include <stdio.h>

int calcular_vuelto(int plata, int valor){
	int resultado;
	resultado = plata - valor;
	return resultado;
}

int main(){
	int plata_charly;
	int vuelto_charly;
	int valor_comida;

	printf("Cuanta $ tenes?\n");
	scanf("%i", &plata_charly);

	printf("Cuanto cuesta?\n");
	scanf("%i", &valor_comida);

	vuelto_charly = calcular_vuelto(plata_charly, valor_comida);

	return 0;
}