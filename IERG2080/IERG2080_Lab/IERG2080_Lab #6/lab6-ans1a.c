#include <stdio.h>
#include <time.h>

int main(){
    clock_t begin = clock();
    long i, N;
    scanf("%ld", &N);
    for(i = 1; i < N; i++){
        if (N%i == 0){
            printf("%ld\n", i);
        }
        else
            continue;
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time spent = %fs\n", time_spent);
}
