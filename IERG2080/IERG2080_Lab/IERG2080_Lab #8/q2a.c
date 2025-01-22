// Input : hFile - handle to opened file stream.
// Output: Returns length of file in bytes, -1 on error (w/ errno set).

#include <stdio.h>

long fileLength(FILE *hFile) {
   long currentpos = ftell(hFile);
   if (fseek(hFile, 0, SEEK_END) != 0) {
       return -1;
   }
   long length = ftell(hFile);
   if (length == -1L) {
       return -1;
   }
   return length;
}


int main() {
   FILE *file = fopen("test.txt", "r");
   if (file == NULL) {
       perror("Error opening file");
       return 1;
   }
   long length = fileLength(file);
   if (length == -1) {
       perror("Error getting file length");
       fclose(file);
       return 1;
   }
   printf("File length: %ld bytes\n", length);
   fclose(file);
   return 0;
}


