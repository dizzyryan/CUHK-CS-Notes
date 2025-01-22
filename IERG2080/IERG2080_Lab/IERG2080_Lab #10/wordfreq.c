#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define INITIAL 20
#define BUFFER_SIZE 256

int find_word_pos(char **words, int count, char *word) {
   for (int i = 0; i < count; i++) {
       if (strcasecmp(words[i], word) == 0) {
           return i;
       }
   }
   return -1;
}

void expand_arrays(char ***words, int **counts, int *size) {
   *size *= 2;
   *words = realloc(*words, sizeof(char *) * (*size));
   *counts = realloc(*counts, sizeof(int) * (*size));
   printf("Realloc() to %d words\n", *size);
}

void word_frequency(const char *filename) {
   FILE *file = fopen(filename, "r");
   if (!file) {
       perror("Failed to open source file, reason: ");
       return;
   }

   fseek(file, 0, SEEK_END);
   long file_size = ftell(file);
   rewind(file);

   char **words = malloc(sizeof(char *) * INITIAL);
   int *counts = malloc(sizeof(int) * INITIAL);
   int size = INITIAL;
   int count = 0;

   if (file_size > size){
       expand_arrays(&words, &counts, &size);
   }

   char buffer[BUFFER_SIZE];
   while (fscanf(file, "%s", buffer) == 1) {
       char *word = strdup(buffer);
       if (word == NULL) {
           printf("Memory allocation failed.\n");
           break;
       }

       int wordpos = find_word_pos(words, count, word);
       if (wordpos == -1) {
           words[count] = word;
           counts[count] = 1;
           count++;
       } else {
           free(word);
           counts[wordpos]++;
       }
   }

   fclose(file);

   printf("%ld bytes and %d unique words processed successfully.\n", file_size, count);

   printf("[Counts]   Word\n"
          "--------  -------\n");
   for (int i = 0; i < count; i++) {
       printf("[     %d]:  \"%s\"\n", counts[i], words[i]);
   }

   for (int i = 0; i < count; i++) {
       free(words[i]);
   }
   free(words);
   free(counts);
}

int main(int argc, char *argv[]) {
   if (argc != 2) {
       printf("Usage: ./wordfreq filename\n");
       return 1;
   }
   const char *filename = argv[1];
   word_frequency(filename);
   return 0;
}
