#include <stdio.h>
#include <stdlib.h>

int main() {
    // question (a)
    size_t buffersize = 1024;
    char *buffer;
    while (1){
        buffer = (char*) malloc(buffersize);
        if(buffer != NULL){
            buffersize *= 2;
            free(buffer);
        }
        else{
            printf("Buffersize reaches maximum. Buffersize = %ld bytes.\n", buffersize);
            break;
        }
    }
    
    // question (b)
    size_t arraysize = 1024;
    while (1){
        char vlabuffer[arraysize];
        printf("%ld\n", arraysize);
        if(vlabuffer !=  NULL){
            arraysize *= 2;
        }
        else{
            printf("The maximum array size = %ld bytes.", arraysize);
            break;
        }
    }
    return 0;
}
/* question (c)
 * 1. size limitation
 * 2. buffer overflows
 */
