/**
 * Description of approaches used - Board checking for checkSolutionDetail( )
 * In this function, for-loop is used to check the collision
 *
 * Two for-loop are used, with one checks the rows, while the other checks the columns
 *
 * To check for the collision in the same row, it first locate the row to 'x'
 * it then checks all the numbers within the same row
 * if the position of input number is the same as the position of the number being checked
 * it will skip that one using 'continue' and move on to the next until all the number is checked
 * if a collision is found, it will ask player to recheck the number
 *
 * The method used for checking collision in the same column
 * follows a similar approach as described above.
 *
 * To check collision for the 3×3 subgrid for the selected cell
 * Original method (way of thinking):
 * Use if statement check if row or col is in 0-2 or 3-5 or 6-8
 * Use for loop to check all elements from [1][1] to [3][3] except user input
 * Improved method (used below):
 * Divided row number or column number by 3
 * 0~2 will give 0, 3~5 will give 1, 6~8 will give 2 (shows which subgrid it belongs to)
 * Use 3 to multiply the value to find the starting position of each subgrid (0, 3 and 6)
 * Use for loop to check all elements ([1][1] to [3][3], etc.) except user input
*/

/**
 * Description of approaches used - Implementation of the save/load function
 *
 * In savePuzzle( )
 * it first opens a file named 'saveGame.txt'
 * it reads the numbers from gameBoard starting from [0][0] to [8][8]
 * if it encounters a '0', it prints the digit '0' in the file
 * after printing each digit, it places a whitespace
 * after reading the entire gameBoard, it prints two newlines
 * then it starts reading the numbers from sol from [0][0] to [8][8]
 * the approach used is similar as described above
 * the file will be saved and closed after all the digit from gameBoard and sol is read
 * it will then inform the user the game has been saved and terminates the program
 *
 * In loadPuzzle( )
 * it first opens the file named 'saveGame.txt'
 * it there is no such file, tell the user that no game has beem saved before
 * then goes back to loadGame selection
 * if the file can be read
 * read the first 9 X 9 digits from the file and put the digits into the gameBoard
 * then read the next 9 X 9 digits from the file and put the digits into sol
 *
 * The load function is added before the gameMode selection
 * If the game has been saved before
 * the function reads the digits and put them into the gameBoard
 * then proceeds to the gameMode selection
 * If no game has been saved before, inform the user and terminate the program
 *
 * loadPuzzle cannot be used to read other text files.
 * The pointer is assigned to read the file named 'saveGame.txt'
 * If the file format is different or the name is different
 * the function will not be able to read the file
 * If another file need to be read
 * then the name of the file in the function should be changed accordingly
*/

/**
 * Description of approaches used - Locked Block Checker
 *
 * The function checkFillable( ) finds the set of possible numbers for any empty cell
 * First, it locates the position of the cell that needs to be checked using the given parameters 'x' and 'y'
 * There are three parts that check row, column and subgrid
 * The function uses a variable called 'possibleans'
 * which stores all the possible numbers for the empty cell, i.e. from 1 to 9
 * The approach used to check for row and column is similar
 * it will check all the digits in the same row/column
 * and skip the position of the cell being selected
 * if there is a number in the row/column that is not 0
 * set the digit in possibleans to 0, and 1 is added to boardcheck
 *
 * The method used to check numbers in subgrid combines the approach mentioned above
 * and the one used in checkSolutionDetail( )
 *
 * if the 'boardcheck' is equal to 9, it means there is no possible answer that can be filled
 * if the 'boardcheck' is less than 9, it means there is a possible answer that can be filled
 *
 * To use this functoin, isLockBoard( ) is used.
 * In this function, it goes through all the empty cells in the gameBoard
 * it then calls the function checkFillable( )
 * and provides it with the location of the selected cell
 * if checkFillable( ) indicates that there is no possilbe digit that can be filled (i.e. returning 0)
 * the board informs the user, locks the board and terminates the game
 * if checkFillable( ) indicates that there is possible digit that can be filled (i.e. returning 1)
 * the function will moves on to check the possible answer set in the next 0 position
 * if no cell is locked, the game continues.
*/


#include <stdio.h>

// Initialize the specified game board.
void initGameBoard(int gameBoard[][9], int puzzle[][9]) {
    int i, j;
    // use for loop to initialize the gameBoard
    for (i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            gameBoard[i][j] = puzzle[i][j];
        }
    }
}

// set the format of gameboard
void printGameBoard(int gameBoard[][9]) {
    int i, j, c = 0;
    for (i = 0; i < 9; i++){
        // setup for the x axis and the line before the first three subgrid
        if (c == 0){
            printf("  012 345 678 \n");
            printf(" +---+---+---+\n");
        }
        // setup for the line after each subgrid is shown
        else if (c == 3 || c == 6 || c == 11)
            printf(" +---+---+---+\n");
        // show the y axis
        printf("%d", i);
        int k = 0;
        for (j = 0; j < 9; j++){
            k++;
            if (k == 1 || k == 4 || k == 7)
                printf("|");
            if (gameBoard[i][j] == 0)
                printf(" ");
            else if (gameBoard[i][j] == 10)
                printf("X");
            else
                printf("%d", gameBoard[i][j]);
        }
        printf("|");
        c++;
        printf("\n");
    }
    // setup for the last line
    printf(" +---+---+---+\n");
}

int inputBoard(int gameBoard[][9], int x, int y, int sol[][9], int gameMode){
    char inputbyuser;
    int rtrnvlu;
    printf("Input a number [or H: hint, S: save]: ");
    scanf(" %c", &inputbyuser);
    // if the game is in Easy Mode
    if (gameMode == 0){
        // check the validity of the input
        if ((inputbyuser > '9' || inputbyuser <= '0') && inputbyuser != 'H'){
            printf("Invalid Input.\n");
            rtrnvlu = -1;
        }
        // check if user need a hint
        else if (inputbyuser == 'H')
            rtrnvlu = 1;
        // assign user input to gameBoard
        else{
            gameBoard[x][y] = (int) inputbyuser - '0';
            rtrnvlu = 0;
        }
    }
    // if the game is in Hard Mode
    else if (gameMode == 1){
        // check the validity of the input
        if ((inputbyuser > '9' || inputbyuser <= '0') && inputbyuser != 'H' && inputbyuser != 'S'){
            printf("Invalid Input.\n");
            rtrnvlu = -1;
        }
        // check if user need a hint
        else if (inputbyuser == 'H'){
            printf("No hint in Hard mode.\n");
            rtrnvlu = -1;
        }
        // check if user need to save the puzzle and solve later
        else if (inputbyuser == 'S'){
            rtrnvlu = 3;
        }
        // assign user input to gameBoard
        else{
            gameBoard[x][y] = (int) inputbyuser - '0';
            rtrnvlu = 0;
        }
    }
    return rtrnvlu;

}

int checkFinish(int gameBoard[][9], int sol[][9]){
    int i, j, ckfsh;
    // use for loop to check numbers in all position to see if the gameBoard is finished
    for (i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if (gameBoard[i][j] == sol[i][j])
                ckfsh = 1;
            else{
                ckfsh = 0;
                break;
            }
        }
    }
    return ckfsh;
}


/* ** Hard Mode ** */

int checkSolutionDetail(int gameBoard[][9], int x, int y){
    int i, j, k, m, rtnval = 0;
    // This part use for loop to check
    // if there is collision in the same row
    // Method: change the column while keep the row unchanged
    for (i = 0; i < 9; i++){
        // not checking the element that user inputted
        if (y == i)
            continue;
        // x is the row number, which will not changed
        if (gameBoard[x][y] == gameBoard[x][i]){
            printf("Check again the numbers in row %d.\n", x);
            // return a value if there is collision
            rtnval = 1;
            break;
        }
    }
    // This part use for loop to check
    // if there is collision in the same column
    // Method: change the row while keep the column unchanged
    for (j = 0; j < 9; j++){
        // not checking the element that user inputted
        if (x == j)
            continue;
        // y is the column number, which will not changed
        if (gameBoard[x][y] == gameBoard[j][y]){
            printf("Check again the numbers in column %d.\n", y);
            // return a value if there is collision
            rtnval = 1;
            break;
        }
    }
        
    int rowcheck = (int)3 * (x / 3);
    int colcheck = (int)3 * (y / 3);
    // use for loop to check 3 elements vertically and horizontally
    for (k = rowcheck; k < rowcheck + 3; k++){
        for (m = colcheck; m < colcheck + 3; m++){
            // skip user input
            if (x == k && y == m)
                continue;
            else if (gameBoard[x][y] == gameBoard[k][m]){
                printf("Check again the numbers in the subgrid where (%d, %d) is at.\n", x, y);
                // return a value if there is collision
                rtnval = 1;
                // can exit the loop if collision found.
                break;
            }
        }
    }
    // if there is no collision happened, rtnval = 0
    // if there is collision happened, which happened for once or more
    // rtnval = 1, with its value be used in main()
    return rtnval;
}


/* ** Part 2 ** */

// check for lock board
int checkFillable(int gameBoard[][9], int x, int y){
    int i, j, k;
    int boardcheck = 0, checkrtn;
    // possible answer set
    int possibleans[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    // This part check the same row (x)
    for (i = 0; i < 9; i++){
        // if the position is the same as the cell selected
        if (i == y)
            continue;
        for (j = 0; j < 9; j++){
            // find if there are possible answers
            if(gameBoard[x][i] == possibleans[j] && possibleans[j] != 0){
                possibleans[j] = 0;
                boardcheck++;
                break;
            }
        }
    }
    
    // This part check the same column (y)
    for (j = 0; j < 9; j++){
        // if the position is the same as the cell selected
        if (j == x)
            continue;
        for (i = 0; i < 9; i++){
            // find if there are possible answers
            if(gameBoard[j][y] == possibleans[i] && possibleans[i] != 0){
                possibleans[i] = 0;
                boardcheck++;
                break;
            }
        }
    }
    
    // This part check the subgrid
    int rowlocation = (int)3 * (x / 3);
    int collocation = (int)3 * (y / 3);
    for (k = rowlocation; k < rowlocation + 3; k++){
        for (i = collocation; i < collocation + 3; i++){
            if (k == x && i == y && gameBoard[k][i] != 0)
                continue;
            for (j = 0; j < 9; j++){
                if(gameBoard[k][i] == possibleans[j]  && gameBoard[k][i] != 0){
                    possibleans[j] = 0;
                    boardcheck++;
                    break;
                }
            }
        }
    }
    if (boardcheck >= 9)
        checkrtn = 0;
    else
        checkrtn = 1;
    return checkrtn;
}

// check for lock board in all cell
int isLockBoard(int gameBoard[][9]){
    int i, j, checklock, rtnlock;
    for (i = 0; i < 9; i++){
        for (j = 0; j < 9; j++){
            // skip non-zero cell
            if (gameBoard[i][j] != 0)
                continue;
            // check if the cell is locked
            else if (gameBoard[i][j] == 0){
                checklock = checkFillable(gameBoard, i, j);
                if (checklock == 0){
                    printf("Cell (%d, %d) is locked.\nBoard is locked.\nYou lose.", i, j);
                    break;
                }
                else if (checklock == 1)
                    continue;
            }
        }
        if (checklock == 0)
            break;
    }
    if (checklock == 0)
        rtnlock = 1;
    else if(checklock == 1){
        rtnlock = 0;
    }
    return rtnlock;
}

// to save the puzzle
int savePuzzle(int gameBoard[][9], int sol[][9]){
    FILE *fps;
    fps = fopen("saveGame.txt", "w");
    // write gameBoard into the file
    for(int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            if (gameBoard[i][j] == 10)
                fprintf(fps, "0 ");
            else{
                fprintf(fps, "%d", gameBoard[i][j]);
                fprintf(fps, " ");
            }
        }
        fprintf(fps, "\n");
    }
    fprintf(fps, "\n");
    // write solution into the file
    for(int i=0; i<9; i++){
        for (int j=0; j<9; j++){
            if (gameBoard[i][j] == 10)
                fprintf(fps, "0 ");
            else{
                fprintf(fps, "%d", sol[i][j]);
                fprintf(fps, " ");
            }
        }
        fprintf(fps, "\n");
    }
    fclose(fps);
    printf("Game Saved.");
    return 1;
}

// to load the saved puzzle
int loadPuzzle(int gameBoard[][9], int sol[][9]){
    int ifload;
    FILE *fpload;
    fpload = fopen("saveGame.txt", "r");
    // if the game has not been saved before
    if (fpload == NULL){
        printf("You did not save any game before.");
        ifload = 0;
    }
    // if the game has been saved before
    else{
        // write the saved game to gameBoard
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                if (fscanf(fpload, "%d", &gameBoard[i][j]) == 1)
                    continue;
            }
        }
        // write the solution to sol
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                if (fscanf(fpload, "%d", &sol[i][j]) == 1)
                    continue;
            }
        }
        ifload = 1;
    }
    fclose(fpload);
    return ifload;
}

void printSolution(int puzzle[][9],int solution[][9]){
    FILE *fp;
    fp = fopen("textInput.txt", "w");
    if (fp == NULL) {printf("Error in writing file."); return;}

    fprintf(fp,"0\n"); // Change to 1 if runns in Hard mode
    for(int i=0; i<9; i++)
    for (int j=0; j<9; j++){
        if (puzzle[i][j]==0){
            fprintf(fp, "%d %d\n", i, j);
            fprintf(fp, "%d\n", solution[i][j]); // You may print a character to test Hint/Save-load function.
        }
    }
    fclose(fp);
}

/* The main function */
int main()
{
    /* Local variables */
    int myPuzzle[9][9];
    // The solution
    int mySolution[9][9];
    // Game Board
    int gameBoard[9][9];

    // gameMode: {0: Easy  1: Hard}
    // chances is the no. of chances in hard mode
    // hintCount stores the no. of hint used.
    int gameMode, chances = 3, hintCount = 0;

    // store x, y coordinate of a cell
    int x, y;

    // number will store the puzzle ID (player's puzzle selection)
    int number;

    // Create YOUR local variables
    /* Initialize the local variables */
    int win = 0, validIn = 0, inputValid = 0;
    int check = 0;
    char loadgame;
    int i, j, checkload;
    char gamemodein;

    while (1) {
        // Load the previous game
        printf("Load the saved game (y/n)?");
        scanf(" %c", &loadgame);
        if (loadgame != 'y' && loadgame != 'n')
            continue;
        // if user want to load the saved game
        if (loadgame == 'y'){
            checkload = loadPuzzle(myPuzzle, mySolution);
            // if user did not save the game before
            if (checkload == 0)
                return 0;
            // if user saved the game before
            if (checkload == 1){
                // select gameMode
                while (1) {
                    // Read the game mode
                    printf("Enter the game mode [0: Easy. 1: Hard]: ");
                    scanf(" %c", &gamemodein);
                    // input is invalid, ask to enter the level again
                    if (gamemodein != '1' && gamemodein != '0'){
                        printf("Invalid input.\n");
                        continue;
                    }
                    // easy mode selected, leave the loop
                    if (gamemodein == '0') {
                        gameMode = 0;
                        printf("You have selected Easy mode.\n");
                        break;
                    }
                    // hard mode selected, leave the loop
                    else if (gamemodein == '1') {
                        gameMode = 1;
                        printf("You have selected Hard mode.\n");
                        break;
                    }
                }
                break;
            }
        }
        // if user do not want to load the saved game
        else if (loadgame == 'n'){
            while (1) {
                // Read the game mode
                printf("Enter the game mode [0: Easy. 1: Hard]: ");
                scanf(" %c", &gamemodein);
                // input is invalid, ask to enter the level again
                if (gamemodein != '1' && gamemodein != '0'){
                    printf("Invalid input.\n");
                    continue;
                }
                // easy mode selected, leave the loop
                if (gamemodein == '0') {
                    gameMode = 0;
                    printf("You have selected Easy mode.\n");
                    break;
                }
                // hard mode selected, leave the loop
                else if (gamemodein == '1') {
                    gameMode = 1;
                    printf("You have selected Hard mode.\n");
                    break;
                }
            }
            // load file from new puzzle
            FILE *fptr;
            fptr = fopen("puzzle.txt", "r");
            for (i = 0; i < 9; i++){
                for (j = 0; j < 9; j++){
                    if (fscanf(fptr, "%d", &myPuzzle[i][j]) == 1){
                        continue;
                    }
                }
            }
            for (i = 0; i < 9; i++){
                for (j = 0; j < 9; j++){
                    if (fscanf(fptr, "%d", &mySolution[i][j]) == 1){
                        continue;
                    }
                }
            }
            fclose(fptr);
            break;
        }
    }
    
    // initiate the game and print the gameBoard
    initGameBoard(gameBoard, myPuzzle);
    printGameBoard(gameBoard);
    
    // While the game is not finished:
    while (1){
        // Let the player select a cell
        // Repeat the cell selection process if it is invalid
        printf("Select a row and column: ");
        scanf("%d %d", &x, &y);
        if (x > 8 || y > 8){
            printf("Out of bound. Input Again.\n");
            continue;
        }
        else if (gameBoard[x][y] > 0){
            printf("Occupied.\n");
            continue;
        }
        // Print Game Board After player chose a valid cell (displayed as 'X')
        else {
            gameBoard[x][y] = 10;
            printGameBoard(gameBoard);
            gameBoard[x][y] = 0;
        }
        
        // Receive input from the player by calling inputBoard().
        // Use the return value from inputBoard() for program control flow.
        validIn = inputBoard(gameBoard, x, y, mySolution, gameMode);
        
        // If inputBoard indicates invalid input, go back to cell selection
        if (validIn == -1){
            printGameBoard(gameBoard);
            continue;
        }
        // If user want to save the game
        else if (validIn == 3){
            savePuzzle(gameBoard, mySolution);
            break;
        }
        // If user needs a hint
        else if (gameMode == 0 && validIn == 1){
            gameBoard[x][y] = mySolution[x][y];
            printGameBoard(gameBoard);
            hintCount++;
        }
        // if user input a valid number
        else if (gameMode == 0 && validIn == 0){
            // if user input a correct number
            if (gameBoard[x][y] == mySolution[x][y]){
                printGameBoard(gameBoard);
            }
            // if user input a wrong number
            else if (gameBoard[x][y] != mySolution[x][y]){
                printf("Sorry, %d should not be placed at (%d, %d).\n", gameBoard[x][y], x, y);
                gameBoard[x][y] = 0;
                printGameBoard(gameBoard);
                continue;
            }
        }
        
        // check the answer for different game mode
        // e.g., call checkSolutionDetail() for Hard mode
        if (gameMode == 1 && validIn == 0){
            inputValid = checkSolutionDetail(gameBoard, x, y);
            chances -= inputValid;
            if (inputValid == 0){
                printGameBoard(gameBoard);
                if (isLockBoard(gameBoard) == 1)
                    break;
            }
            else if (inputValid == 1){
                gameBoard[x][y] = 0;
                if (chances != 0){
                    printf("You have %d chances left.\n", chances);
                    printGameBoard(gameBoard);
                }
                if (chances == 0){
                    printf("You lose.");
                    break;
                }
            }
        }
        
        // Output the winning or losing message
        check = checkFinish(gameBoard, mySolution);
        if (gameMode == 0 && check == 1){
            printf("Congratulations! You have finished a puzzle in easy mode and used %d hints.\n", hintCount);
            break;
        }
        if (gameMode == 1 && check == 1){
            printf("Congratulations! You have finished a puzzle in hard mode with %d chances left.\n", chances);
            break;
        }
        else if (check == 0)
            continue;
    }
    return 0;
}
