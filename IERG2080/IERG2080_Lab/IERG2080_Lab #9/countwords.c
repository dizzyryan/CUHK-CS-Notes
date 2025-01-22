#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./countwords filename\n");
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open source file, reason: ");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(file_size + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return 1;
    }

    size_t num_read = fread(buffer, 1, file_size, file);
    if (num_read != file_size) {
        perror("Failed to read file");
        free(buffer);
        fclose(file);
        return 1;
    }

    printf("Processing %s ...%ld bytes processed successfully\n", argv[1], file_size);

    fclose(file);

    int word_count = 0;
    int chara = 0;

    for (int i = 0; i < file_size; i++) {
        if (isalpha(buffer[i])) {
            if (!chara) {
                word_count++;
                chara = 1;
            }
        } else {
            chara = 0;
        }
    }

    free(buffer);

    printf("Number of word counts: %d\n", word_count);

    return 0;
}
