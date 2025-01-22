#include <stdio.h>
#include <string.h>

int main() {
    char input[10];
    int logged_in = 0; // False
    scanf("%s", input);
    int check = strcmp("ierg2080", input);
    if (check == 0){
        logged_in++;
        printf("Login successful!\n");
    }
    else
    printf("Incorrect password!\n");
}
