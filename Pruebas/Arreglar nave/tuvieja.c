# include <stdio.h>
int main () {
	int costo_de_reparacion , ahorros;
	scanf("%d" , & costo_de_reparacion);
	scanf("%d" , & ahorros );
	if (ahorros >= costo_de_reparacion){
		printf ("Tranki que podemos arreglarla \n");
	}
	else {
	printf ("Siamo fuori, no podemos volver \n");
	}
	return 0;
}