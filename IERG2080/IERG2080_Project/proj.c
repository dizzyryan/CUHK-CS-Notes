/** <curses.h> automatically includes the headers <stdio.h> and <unctrl.h> */
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PBM 3821

// fill the whole screen with spaces to show a full reverse background.
void bg_reverse()
{
    attron(A_REVERSE);
    // loop to fill space
    for (int i = 0; i < 24; i++)
        for (int j = 0; j < 80; j++)
            mvaddstr(i,j, " ");
    attroff(A_REVERSE);
};

// read the input PBM file if supplied
void readPBM(const char *infile, int bitmap[][80], int width, int height)
{
    FILE *file;
    char line[MAX_PBM];
    int row = 0;

    file = fopen(infile, "r");

    // show error if file cannot be opened
    if (file == NULL) {
        endwin();
        perror("Error opening file");
        exit(1);
    }

    // read the first line
    fgets(line, MAX_PBM, file);
    // remove newline
    line[strcspn(line, "\n")] = '\0';

    // check for file format P1
    if (strcmp(line, "P1") != 0) {
        endwin();
        printf("Invalid file format.\n");
        exit(1);
    }

    // read the following file
    while (fgets(line, MAX_PBM, file) != NULL) {
        // remove newline
        line[strcspn(line, "\n")] = '\0';

        // skip lines begin with '#'
        if (line[0] == '#') {
            continue;
        }

        // check for width and height
        if (sscanf(line, "%d %d", &width, &height) == 2) {
            if (width == 80 && height == 24)
                break;
            else {
                endwin();
                printf("The size of the PBM should be 80*24.\r\n");
                exit(1);
            }
        }
    }

    // read the bitmap data
    while (fgets(line, MAX_PBM, file) != NULL) {
        // remove newline
        line[strcspn(line, "\n")] = '\0';

        int k = 0;

        for (int j = 0; j < strlen(line); j++) {
            if (line[j] == ' ')
                continue;
            bitmap[row][k++] = line[j] - '0';
            if (k == 80){
                k = 0;
                row++;
            }
        }

        // break if all rows have been read
        if (row >= height) {
            break;
        }
    }
    fclose(file);
}

// print PBM file
void printPBM(int bitmap[][80]){
    int k = 0;
    // loop through all rows
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 80; j++) {
            // print space if 0
            if (bitmap[i][j] == 0) {
                attron(A_REVERSE);
                mvaddstr(i, j, " ");
                attroff(A_REVERSE);
                k++;
                continue;
            }
            // print # if 1
            if (bitmap[i][j] == 1) {
                attrset(A_NORMAL);
                mvaddstr(i, j, "#");
                k++;
            }
        }
    }
}

// move the cursor and do modification if user press space
void movecursor(int ch, int* x_pos, int* y_pos, int inbitmap[][80]){
    int check = mvinch(*x_pos, *y_pos) & A_CHARTEXT;
    int x = *x_pos, y = *y_pos;
    // check for key input
    switch (ch) {
        // press arrow up
        case KEY_UP:
            if (--x >= 0) {
                move(--(*x_pos), *y_pos);
            }
            break;
            // press arrow down
        case KEY_DOWN:
            if (++x <= 23) {
                move(++(*x_pos), *y_pos);
            }
            break;
            // press arrow left
        case KEY_LEFT:
            if (--y >= 0) {
                move(*x_pos, --(*y_pos));
            }
            break;
            // press arrow right
        case KEY_RIGHT:
            if (++y <= 79) {
                move(*x_pos, ++(*y_pos));
            }
            break;
            // press space
        case 32:
            // to erase #
            if (check == 35) {
                attron(A_REVERSE);
                mvaddstr(*x_pos, *y_pos, " ");
                attroff(A_REVERSE);
                inbitmap[*x_pos][*y_pos] = 0;
                move(*x_pos,*y_pos);
            }
                // to draw a #
            else if (check == 32) {
                mvaddstr(*x_pos, *y_pos, "#");
                inbitmap[*x_pos][*y_pos] = 1;
                move(*x_pos,*y_pos);
            }
            break;
            // press ESC
        case 27:
            return;
    }
}

// save output bitmap to a file
void savebitmapfile(const char *outfile, int bitmap[][80]){
    FILE *outbitmapfile = fopen(outfile, "w");

    if (outfile == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fprintf(outbitmapfile, "P1\r\n"); // file format
    fprintf(outbitmapfile, "# This is a bitmap\r\n"); // comment
    fprintf(outbitmapfile, "80 24\r\n"); // PBM size

    // print PBM to the file
    for (int i = 0; i < 24; i++){
        for (int j = 0; j < 80; j++){
            fprintf(outbitmapfile, "%d", bitmap[i][j]);
        }
        fprintf(outbitmapfile, "\r\n");
    }

    fclose(outbitmapfile); // Close the file
}

int main(int argc, char *argv[])
{
    /* this is a pointer, to be used to store some curses window info */
    WINDOW *win;
    int ch; // for key reading
    int bitmap[24][80];
    int x_pos = 0, y_pos = 0; // store the position of cursor

    /* curses initialization */
    win = initscr();
    if (win == NULL)
    {
        printf("initscr() failed\n");
        exit(1);
    }
    cbreak();
    noecho();
    intrflush(win, FALSE);
    keypad(win, TRUE);
    refresh();

    // resize the terminal
    resize_term(24, 80);

    bg_reverse();
    move(0,0);
    // assign 0 to bitmap
    memset(bitmap, 0, sizeof(bitmap));
    refresh();

    char *infile = NULL, *outfile = NULL;
    int inexist = 0, outexist = 0;

    // use this part to read the input/output file name from command line, null if not supplied
    if(argc > 1){
        for (int i = 1; i < argc; i++) {
            if (strncmp(argv[i], "in=", 3) == 0) {
                infile = strchr(argv[i], '=') + 1;
                inexist = 1;
                continue;
            }
            if (strncmp(argv[i], "out=", 4) == 0) {
                outfile = strchr(argv[i], '=') + 1;
                outexist = 1;
                continue;
            }
            if (strncmp(argv[i], "in=", 3) != 0 || strncmp(argv[i], "out=", 4) != 0){
                endwin();
                printf("Usage: ./proj [in=in_file] [out=out_file]\n");
                printf("Usage: ./proj [out=out_file] [in=in_file]\n");
                return 0;
            }
        }
    }

    // read the PBM file if supplied
    if (inexist == 1) {
        readPBM(infile, bitmap, 80,24);
        printPBM(bitmap);
        move(0,0);
        refresh();
    }

    // use this part to move the cursor
    do{
        ch = getch();
        movecursor(ch, &x_pos, &y_pos, bitmap);
        refresh();
    }while (ch != 27);

    // end the curses program
    endwin();

    // if no outfile supplied, print PBM to the terminal
    if (outexist == 0) {
        printf("P1\r\n# Below is the Bitmap\r\n80 24\r\n");
        for (int i = 0; i < 24; i++){
            for (int j = 0; j < 80; j++){
                printf("%d", bitmap[i][j]);
            }
            printf("\r\n");
        }
    }

    // if outfile is given, print PBM to the file
    if (outexist == 1) {
        savebitmapfile(outfile, bitmap);
    }

    // new line before termination
    printf("\n");

    return 0;
}