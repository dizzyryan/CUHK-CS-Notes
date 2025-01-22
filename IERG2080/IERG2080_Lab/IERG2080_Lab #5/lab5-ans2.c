#include <stdio.h>

int main(void){
	int input, i, j, k, l;
	scanf("%d", &input);
	while (input%2 == 0)
		scanf("%d", &input);
	
	for (i = 0; i < (input + 1)*2 + 1; i++){
		for (j = 0; j < (input + 1)*2-i; j++)
			printf(".");
		printf("*");
		if (i == input+1)
			for (l = 0; l < (input+1)*2; l++){
				printf("*");
			}
		else{
			for (k = 0; k < i*2-1; k++)
				printf(".");
		}
		if (i != 0 && i != input+1)
			printf("*");
		printf("\n");
	}

	return 0;
}
