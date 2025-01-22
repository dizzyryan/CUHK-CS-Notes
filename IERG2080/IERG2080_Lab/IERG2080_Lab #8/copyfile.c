#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>

// print the usage instructions if no argument given
void prtErUsage() {
    printf("Usage: ./copyfile source destination [buffersize]\n");
}

// print the usage instructions given source, destination and buffer size
void prtUsage(char source[], char destination[], long buffer, long filesize, float time) {
    printf("Copying from %s to %s with buffer size %ld bytes "
           "... %ld bytes copied successfully in %fs.\n", source,
           destination, buffer, filesize, time);
}

// function for reading filesize
int Filesize(FILE *filename) {
    // pointer move to the end
    fseek(filename, 0, SEEK_END);
    // read the pointer position
    int filesize = ftell(filename);
    // move pointer to the initial position
    rewind(filename);
    return filesize;
}

int main(int argc, char *argv[]) {
    // Validate program arguments
    if (argc < 3 || argc > 4) {
        // print usage instruction
        prtErUsage();
        return 1;
    }

    // program arguments structure
    char *source = argv[1];
    char *destin = argv[2];
    long buffersize = 8192;
    char checkstdout[] = "stdout";
    char checkstdin[] = "stdin";

    // determine buffer size
    if (argc == 4) {
        // Convert buffer size argument to integer
        buffersize = atoi(argv[3]);
        // user supply 0, find buffer size (file size)
        if (buffersize == 0) {
            // open source file
            FILE *sfile = fopen(source, "r");
            // report if error found
            if (sfile == NULL) {
                perror("Error opening source file");
                return 1;
            }
            // assign filesize to buffer size
            buffersize = Filesize(sfile);
            // close file
            fclose(sfile);
        }
    }

    // Allocate memory for buffer
    char *buffer = (char *)malloc(buffersize);

    // Open source file
    FILE *sfile = fopen(source, "ab+");
    // report if error
    if (sfile == NULL) {
        perror("Error opening source file");
        free(buffer);
        return 1;
    }
    // Open destination file
    FILE *dfile = fopen(destin, "ab+");
    // report if error
    if (dfile == NULL) {
        perror("Error opening destination file");
        return 1;
    }

    // if user input stdin
    char storestdin[100000];
    if (!strcmp(argv[1], checkstdin)) {
        fgets(storestdin, 100000, stdin);
        fputs(storestdin, sfile);
    }

    // if user input stdout
    char printstdout;
    if (!strcmp(argv[2], checkstdout)) {
        if(!strcmp(argv[1], checkstdin)){
            fclose(sfile);
            printstdout = fgetc(stdin);
            while (printstdout != EOF) {
                printf("%c", printstdout);
                printstdout = fgetc(stdin);
            }
        }
        FILE *stdoutptr = fopen(source, "r");
        printstdout = fgetc(stdoutptr);
        while (printstdout != EOF) {
            printf("%c", printstdout);
            printstdout = fgetc(stdoutptr);
        }
        fclose(stdoutptr);
    }

    // Determine source file size
    int sfilesize = Filesize(sfile);

    if (strcmp(argv[2], checkstdout)) {
        // start timing
        clock_t begin = clock();
        // Copy file
        int bytes, BytesRead = 0;
        while ((bytes = fread(buffer, 1, buffersize, sfile)) > 0) {
            BytesRead += bytes;
            // check if same content
            if (fwrite(buffer, 1, bytes, dfile) != bytes) {
                perror("Error writing to destination file");
                fclose(sfile);
                fclose(sfile);
                free(buffer);
                return 1;
            }
        }
        // end timing
        clock_t end = clock();
        // calculate the time used
        double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
        // Verify file copy
        if (BytesRead != sfilesize) {
            printf("Error: Destination file size doesn't match source file size.\n");
        } else {
            prtUsage(source, destin, buffersize, sfilesize, time_spent);
        }
    }

    // read and change file permission
    struct stat fileStatS, fileStatD;
    // Get the file status
    if (stat(source, &fileStatS) == -1 || stat(destin, &fileStatD) == -1) {
        perror("stat");
        return 1;
    }
    // Check permission
    if ((fileStatS.st_mode & S_IRUSR) != (fileStatD.st_mode & S_IRUSR)) {
        fileStatD.st_mode |= fileStatS.st_mode;
    }
    if ((fileStatS.st_mode & S_IWUSR) != (fileStatD.st_mode & S_IWUSR)) {
        fileStatD.st_mode |= fileStatS.st_mode;
    }
    if ((fileStatS.st_mode & S_IXUSR) != (fileStatD.st_mode & S_IXUSR)) {
        fileStatD.st_mode |= fileStatS.st_mode;
    }
    if (chmod(destin, fileStatD.st_mode) == -1) {
        perror("chmod");
        return 1;
    }
    if (strcmp(argv[2], checkstdout) == 0 || strcmp(argv[1], checkstdin) == 0){
        remove("stdin");
        remove("stdout");
    }
    // Clean up
    fclose(sfile);
    fclose(dfile);
    free(buffer);

    return 0;
}

/* Question 2 (c)
 * reducing the buffer will increase the time for copy the file
*/

