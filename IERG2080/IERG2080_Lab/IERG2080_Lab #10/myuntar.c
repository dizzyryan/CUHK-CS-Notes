#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>

// to check if the directory exists
int DirectoryCheck(const char *path)
{
   struct stat stats;
   stat(path, &stats);
   if (S_ISDIR(stats.st_mode))
       return 1;
   return 0;
}

// function to extract files
void extractfile(FILE* archive, const char* outputpath, size_t* readbytes){
   // get the filename and filesize
   char filename[256];
   long filesize;
   fscanf(archive, "%s\n%ld\n", filename, &filesize);

   char outfilename[256];
   if (outputpath != NULL) {
       // check if directory exists
       if (DirectoryCheck(outputpath)) {
           // if so, store the output file name and path
           snprintf(outfilename, sizeof(outfilename), "%s/%s", outputpath, filename);
       } else {
           // if directory does not exist, print failed
           fprintf(stderr, "Failed to open destination file %s/%s, reason: %s\n", outputpath, filename, strerror(errno));
           exit(0);
       }
   }   // if no directory, store output file name
   else {
       snprintf(outfilename, sizeof(outfilename), "%s", filename);
   }
   // open output file
   FILE* outputfile = fopen(outfilename, "wb");
   if (outputfile == NULL) {
       printf("Failed to create file: %s\n", outfilename);
       return;
   }

   // write file data to output file
   char buffer[filesize];
   size_t bytes;
   size_t totalbytes = 0;
   while (totalbytes < filesize) {
       bytes = fread(buffer, 1, sizeof(buffer), archive);
       if (bytes == 0) {
           break;
       }
       size_t bytesToWrite;
       if (totalbytes + bytes <= filesize) {
           bytesToWrite = bytes;
       } else {
           bytesToWrite = filesize - totalbytes;
       }
       fwrite(buffer, 1, bytesToWrite, outputfile);
       totalbytes += bytesToWrite;
   }

   int nextchar = fgetc(archive);
   if (nextchar != EOF) {
       ungetc(nextchar, archive);
   }

   printf("Extracting file %s/%s ...\n", outputpath, filename);
   fclose(outputfile);
   *readbytes += filesize;
}

int main(int argc, char* argv[]) {
   // usage check
   if (argc < 2) {
       printf("Usage: ./myuntar inputfile [output_path]\n");
       return 1;
   }

   // open the input file, print error if failed to do so
   const char* inputfile = argv[1];
   FILE* archive = fopen(inputfile, "rb");
   if (archive == NULL) {
       printf("Failed to open archive file: %s\n", inputfile);
       return 1;
   }

   // check if a directory is provided
   char* outputpath = NULL;
   if (argc == 3) {
       outputpath = argv[2];
   }

   // check is the archive is in the correct format
   char id[6];
   fscanf(archive, "%s\n", id);
   if (strcmp(id, "mytar") != 0) {
       printf("Invalid archive file: %s\n", inputfile);
       fclose(archive);
       return 1;
   }

   // Process extract file start
   printf("Reading archive file ...\n");
   int fileCount = 0;
   size_t readbytes = 0;

   // check if it is the end of file, extract if not
   while (!feof(archive)) {
       extractfile(archive, outputpath, &readbytes);
       fileCount++;
   }

   fclose(archive);
   printf("Total %d files and %ld bytes extracted successfully.\n", fileCount, readbytes);
   return 0;
}
