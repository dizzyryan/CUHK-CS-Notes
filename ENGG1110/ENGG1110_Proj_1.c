/**
 * Description of approaches used - Board checking for checkSolutionDetail( )
 * In this function, for-loop is used to check the collision
 *
 * This part is used to check collision in row and column
 * There are two for-loop used, with one checking row and another checking column
 *
 * To check for the collision in the same row, it first locate the row to x
 * it will then check all the numbers within the same row
 * if the position of input number is the same as the position of the number that is being checked
 * it will skip this one using 'continue' and check for the next until all the number is checked
 * if collision is found, it will ask player to check again the number
 *
 * The method used for checking collision in the same column is the same as above.
 *
 * This part is used to check collision for the 3×3 subgrid for the selected cell
 * Original method (way of thinking):
 * Use if statement check if row or col is in 0-2 or 3-5 or 6-8
 * Use for loop to check all elements from [1][1] to [3][3] except user input
 * Improved method (used below):
 * Divided row number or column number by 3
 * 0~2 will give 0, 3~5 will give 1, 6~8 will give 2 (shows which subgrid it belongs to)
 * Use 3 to multiply the value to find the starting position of each subgrid (0, 3 and 6)
 * Use for loop to check all elements ([1][1] to [3][3], etc.) except user input
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
    printf("Input a number [or H: hint]: ");
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
        if ((inputbyuser > '9' || inputbyuser <= '0') && inputbyuser != 'H'){
            printf("Invalid Input.\n");
            rtrnvlu = -1;
        }
        // check if user need a hint
        else if (inputbyuser == 'H'){
            printf("No hint in Hard mode.\n");
            rtrnvlu = -1;
        }
        // assign user input to gameBoard
        else{
            gameBoard[x][y] = (int) inputbyuser - '0';
            rtrnvlu = 0;
        }
    }
    return rtrnvlu;
}

// check if the game is finished
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

// check for collision
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
int checkFillable(int gameBoard[][9], int x, int y){
    
}

int isLockBoard(int gameBoard[][9]){
    
}

int savePuzzle(int gameBoard[][9], int sol[][9]){
    
}

int loadPuzzle(int gameBoard[][9], int sol[][9]){
    
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
    int myPuzzle[9][9]={
        {5,0,0,0,6,3,4,0,0},
        {0,0,0,7,0,0,0,0,0},
        {1,0,0,0,5,0,8,3,0},
        {0,0,0,0,1,8,0,0,7},
        {0,0,6,9,0,0,0,0,0},
        {0,4,3,0,0,0,9,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,7,0,0,2,0},
        {3,2,0,6,4,0,5,0,0}
    };
    // The solution
    int mySolution[9][9] = {
        {5,9,8,1,6,3,4,7,2},
        {6,3,2,7,8,4,1,5,9},
        {1,7,4,2,5,9,8,3,6},
        {2,5,9,4,1,8,3,6,7},
        {8,1,6,9,3,7,2,4,5},
        {7,4,3,5,2,6,9,8,1},
        {4,6,5,8,9,2,7,1,3},
        {9,8,1,3,7,5,6,2,4},
        {3,2,7,6,4,1,5,9,8}
    };
    
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
    char gamemodein;

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
    
    // to initialize and display the gameBoard
    initGameBoard(gameBoard, myPuzzle);
    printGameBoard(gameBoard);
    
    while (1){
        // Let the player select a cell
        // Repeat the cell selection process if it is invalid
        printf("Select a row and column: ");
        scanf("%d %d", &x, &y);
        if (x > 8 || y > 8){
            printf("Out of bound. Input Again.\n");
            continue;
        }
        // Repeat the cell selection process if it is occupied
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
        // If inputBoard indicates valid input and user need hint, give user a hint
        if (gameMode == 0 && validIn == 1){
            gameBoard[x][y] = mySolution[x][y];
            printGameBoard(gameBoard);
            hintCount++;
        }
        // If inputBoard indicates valid input
        if (gameMode == 0 && validIn == 0){
            // If user input a correct number, display the board
            if (gameBoard[x][y] == mySolution[x][y]){
                printGameBoard(gameBoard);
            }
            // If user input a wrong number, show wrong message and go back to cell selection
            else if (gameBoard[x][y] != mySolution[x][y]){
                printf("Sorry, %d should not be placed at (%d, %d).\n", gameBoard[x][y], x, y);
                gameBoard[x][y] = 0;
                printGameBoard(gameBoard);
                continue;
            }
        }
        
        // check the answer for Hard mode
        if (gameMode == 1 && validIn == 0){
            // check if user input a correct number
            inputValid = checkSolutionDetail(gameBoard, x, y);
            chances -= inputValid;
            // if user input a number that has no collision, display the board
            if (inputValid == 0){
                printGameBoard(gameBoard);
            }
            // if user input a number that has collision(s), tell users the chances they have left
            else if (inputValid == 1){
                gameBoard[x][y] = 0;
                if (chances != 0){
                    printf("You have %d chances left.\n", chances);
                    printGameBoard(gameBoard);
                }
                // if the user has no more chance, stop the program
                if (chances == 0){
                    printf("You lose.");
                    break;
                }
            }
        }
        
        // Output the winning or losing message if the game is finished
        check = checkFinish(gameBoard, mySolution);
        if (gameMode == 0 && check == 1){
            printf("Congratulations! You have finished a puzzle in easy mode and used %d hints.\n", hintCount);
            break;
        }
        if (gameMode == 1 && check == 1){
            printf("Congratulations! You have finished a puzzle in hard mode with %d chances left.\n", chances);
            break;
        }
        // if the game is not finish, go back to cell selection
        else if (check == 0)
            continue;
    }
    return 0;
}
