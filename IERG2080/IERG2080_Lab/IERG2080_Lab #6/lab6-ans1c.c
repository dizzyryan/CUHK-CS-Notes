#include <stdio.h>
#include <time.h>
#include <math.h>

int main(){
    clock_t begin = clock();
    long a, b, c, d, N;
    scanf("%ld", &N);
    
    for(a = sqrt(N);;a++){
        b = sqrt((pow(a,2)-N));
        if (pow(b,2) == (pow(a,2)-N)){
            c = a+b;
            d = a-b;
            printf("%ld, %ld, %ld, %ld\n", a, b, c, d);
            break;
        }
        else
            continue;
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time spent = %fs\n", time_spent);
}
