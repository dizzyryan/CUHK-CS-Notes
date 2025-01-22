#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

// use to check if such directory exists
int isDir(const char* path) {
    struct stat path_stat;
    if (stat(path, &path_stat) == 0)
        return S_ISDIR(path_stat.st_mode);
    return 0;
}

// archive files
void archiveFile(FILE* file, const char* filename, FILE* archive) {
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

// archive files in directory
long arcdir(const char* directory, FILE* archive, const char* dul) {
    int countfiles = 0;
    DIR* dir = opendir(directory);
    if (dir == NULL) {
        fprintf(stderr, "Failed to open directory %s, reason: %s\n", directory, strerror(errno));
        return 1;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char filepath[256];
            snprintf(filepath, sizeof(filepath), "%s/%s", directory, entry->d_name);

            FILE* file = fopen(filepath, "rb");
            if (!strcmp(entry->d_name, dul)) {
                printf("Input file same as output file, skipped.\n");
                continue;
            }
            if (file != NULL) {
                archiveFile(file, entry->d_name, archive);
                printf("Adding file %s to archive ...\n", entry->d_name);
                countfiles++;
            } else {
                fprintf(stderr, "Failed to open file %s, reason: %s\n", filepath, strerror(errno));
            }
        } else if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char subdir[256];
            snprintf(subdir, sizeof(subdir), "%s/%s", directory, entry->d_name);
            arcdir(subdir, archive, dul);
        }
    }
    closedir(dir);
    return countfiles;
}

int main(int argc, char* argv[]) {
    long dirfile = 0, nomfile = 0;
    if (argc < 3) {
        printf("Usage: ./mytar outputfile infile1 [infile2] ...\n");
        return 1;
    }

    const char* arcfile = argv[1];
    FILE* arcexist = fopen(arcfile, "r");
    if (arcexist != NULL) {
        printf("Output file %s already exists, overwrite? (y/N): ", arcfile);
        char overwrite;
        scanf(" %c", &overwrite);
        if (overwrite == 'N' || overwrite == 'n') {
            printf("Aborted!\n");
            fclose(arcexist);
            return 1;
        } else if (overwrite != 'Y' && overwrite != 'y') {
            printf("Invalid input!\n");
            fclose(arcexist);
            return 1;
        }
    }

    // Create the output archive file
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
        if (isDir(argv[i])) {
            dirfile = arcdir(argv[i], archive, argv[1]);
            printf("Input file %s is a directory, skipped..\n", argv[i]);
        } else {
            FILE* file = fopen(argv[i], "rb");
            if (!strcmp(argv[i], argv[1])) {
                printf("Input file same as output file, skipped.\n");
                continue;
            }
            if (file != NULL) {
                archiveFile(file, argv[i], archive);
                nomfile++;
                printf("Adding file %s to archive ...\n", argv[i]);
            } else {
                fprintf(stderr, "Failed to open file %s, reason: %s\n", argv[i], strerror(errno));
            }
        }
    }

    fseek(archive, 0, SEEK_END);
    long totalsize = ftell(archive);
    fclose(archive);
    printf("Total %d files and %ld bytes archived successfully.\n", (int) nomfile + (int) dirfile, totalsize);

    return 0;
}