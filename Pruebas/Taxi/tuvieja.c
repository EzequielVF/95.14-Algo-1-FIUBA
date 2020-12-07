# include <stdio.h>
int main(){
	char destino;
	scanf("%c", &destino);

	switch(destino){
		case 'F':
		printf("Su tarifa va a ser de 50 pesos\n");
		break;
		case 'C':
		printf("Su tarifa va a ser de 80 pesos\n");
		break;
		case'B':
		printf("Su tarifa va a ser de 120 pesos\n");
		break;
		default:
		printf("No puedo llevarlo a ese planeta porque no esta en la lista\n");
		break;
	}
	return 0;
}