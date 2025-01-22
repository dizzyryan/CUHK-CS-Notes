#include <stdio.h>

int main(void){
	int input, i, j = 0, k;
	scanf("%d", &input);
	while (input%2 == 0)
                scanf("%d", &input);

	for (i = 0; i < input; i++){
		for (j = 0; j < input; j++){
			if (i == j)	
				printf("x");
			else
				printf(".");
		}
		printf("x");
		for (j = input; j != 0; j--){
			if (i == j-1)
				printf("x");
			else
				printf(".");
		}
		printf("\n");
	}
	for (i = 0; i < input*2+1; i++)
		printf("x");
	printf("\n");
	for (i = 0; i < input; i++){
		for (j = input; j != 0; j--){
                        if (i == j-1)
                                printf("x");
                        else
                                printf(".");
                }
		printf("x");
                for (j = 0; j < input; j++){
                        if (i == j)
                                printf("x");
                        else
                                printf(".");
                }
                printf("\n");
	}
	return 0;
}
