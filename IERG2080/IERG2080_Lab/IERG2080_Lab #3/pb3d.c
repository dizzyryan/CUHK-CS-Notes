#include <stdio.h>

int main(void){
	int x = 2080;

	printf("x = %i\n", x);
	if (x > 0) {
		x = 1110;
		int y = x / 10;
		printf("x = %i\n", x);;
	}

	printf("x = %i\n", x);
	return 0;
}
