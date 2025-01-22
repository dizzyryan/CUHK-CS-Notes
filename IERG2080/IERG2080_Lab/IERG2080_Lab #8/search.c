#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 256

void searchword(const char *word, FILE *file) {
    char buffer[MAX_LENGTH];
    int lineno = 0, wordno = 0, matchno = 0;

    while (fgets(buffer, MAX_LENGTH, file) != NULL) {
        if (strstr(buffer, word) != NULL) {
            printf("[%04d]    %s", lineno, buffer);
            wordno = 1;
            matchno++;
        }
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

/*
 * Question (b)
 * it may lead to the situation that only the 
 * first 256 characters will be checked.
 */
