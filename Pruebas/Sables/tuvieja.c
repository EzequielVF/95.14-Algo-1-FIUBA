# include <stdio.h>

const char VERDE = 'V';
const char ROJO = 'R';

int main () {
	char color_sable_1 , color_sable_2 , color_sable_3 ;
	int sables_cambiados = 0;
	scanf ( "%c" , & color_sable_1 ) ;
	scanf ( "%c" , & color_sable_2 ) ;
	scanf ( "%c" , & color_sable_3 ) ;
	
	if ( color_sable_1 == VERDE )
	sables_cambiados ++;
	if ( color_sable_2 == VERDE )
	sables_cambiados ++;
	if ( color_sable_3 == VERDE )
	sables_cambiados ++;
	if (sables_cambiados!= 0)
	printf ("Se han cambiado %d sables del color VERDE a ROJO\n", sables_cambiados);
	else
	printf ("Todos los sables son de color ROJO\n");
return 0;
}