#include <stdio.h>
#include <string.h>

void archivefile(const char* filename, FILE* archive) {
   FILE* file = fopen(filename, "rb");
   if (file == NULL) {
       printf("Failed to open file: %s\n", filename);
       return;
   }

   fseek(file, 0, SEEK_END);
   long filesize = ftell(file);
   fseek(file, 0, SEEK_SET);

   fprintf(archive, "%s\n%ld\n", filename, filesize);

   char buffer[1024];
   size_t bytesRead;
   while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
       fwrite(buffer, 1, bytesRead, archive);
   }

   fclose(file);
}

int main(int argc, char* argv[]) {
   if (argc < 3) {
       printf("Usage: ./mytar outputfile infile1 [infile2] ...\n");
       return 1;
   }

   const char* arcfile = argv[1];
   FILE* arcexist = fopen(arcfile, "r");
   if (arcexist != NULL) {
       printf("Output file myfiles.mt already exists, overwrite? (y/N): ");
       char overwrite;
       scanf("%c", &overwrite);
       if (overwrite == 'N' || overwrite == 'n') {
           printf("Aborted!\n");
           fclose(arcexist);
           return 1;
       }
       else if (overwrite != 'Y' && overwrite != 'y') {
           printf("Invalid input!\n");
           fclose(arcexist);
           return 1;
       }
   }
  
   FILE* archive = fopen(arcfile, "wb");
   if (archive == NULL) {
       printf("Failed to create archive: %s\n", arcfile);
       fclose(archive);
       return 1;
   }

   fprintf(archive, "mytar\n");

   printf("Creating archive file ...\n");
   int i;
   for (i = 2; i < argc; i++) {
       archivefile(argv[i], archive);
       printf("Adding file %s to archive ...\n", argv[i]);
   }
   fseek(archive, 0, SEEK_END);
   long totalsize = ftell(archive);
   fclose(archive);
   printf("Total %d files and %ld bytes archived successfully.\n", i-2, totalsize);
   return 0;
}