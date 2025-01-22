#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void searchword(const char *word, FILE *file) {
    size_t LENGTH = 2;
    char *buffer = malloc(LENGTH);
    int lineno = 0, wordno = 0, matchno = 0, resize = 0;

    while (fgets(buffer, LENGTH, file) != NULL) {
        if (strlen(buffer) == LENGTH - 1 && buffer[LENGTH - 2] != '\n'){
            LENGTH *= 2;
            buffer = realloc(buffer, LENGTH);
            printf("Buffer resized from %zu to %zu bytes.\n", LENGTH/2, LENGTH);
            resize = 1;
        }
        else resize = 0;
        if (strstr(buffer, word) != NULL) {
            printf("[%04d]    %s", lineno, buffer);
            wordno = 1;
            matchno++;
        }
        if (!resize)
            lineno++;
    }
    if (wordno != 0)
        printf("\nNumber of matches for %s = %d\n", word, matchno);
    else
        printf("\nNumber of matches for %s = %d\n", word, wordno);
}

int main(int argc, char *argv[]) {
    // Incorrect number of arguments
    if (argc < 2) {
        printf("Usage: search word [filename]\n");
        return 1;
    }

    const char *word = argv[1];
    FILE *file = NULL;

    if (argc == 3) {
        file = fopen(argv[2], "r");
        // File cannot be opened
        if (file == NULL) {
            printf("Cannot open file %s\n", argv[2]);
            return 1;
        }
    }
    else {
        file = stdin;
    }

    searchword(word, file);

    if (file != stdin) {
        fclose(file);
    }

    return 0;
}
