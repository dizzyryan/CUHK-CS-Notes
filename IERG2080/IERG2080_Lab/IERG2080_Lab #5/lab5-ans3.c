#include <stdio.h>

int main(void){
    int input, i, j, k, start, count = 0, follow = 0;
    scanf("%d", &input);
    while (input > 100)
        scanf("%d", &input);
    for (i = 1; i <= input; i++){
        start = i;
        count = 0;
        follow = 0;
        for (j = 0; j < input; j++){
            if (start % 2 == 1)
                printf("@");
            if (start % 2 == 0)
                printf("#");
                count += 1;
                follow += 1;
                for (k = 0; k < follow; k++){
                    if (count < input){
                        if (start % 2 == 1)
                            printf("#");
                        if (start % 2 == 0)
                            printf(".");
                        count += 1;
                    }
                    if (count == input)
                        break;
                }
                if (count == input)
                        break;
        }
        printf("\n");
    }
    return 0;
}
