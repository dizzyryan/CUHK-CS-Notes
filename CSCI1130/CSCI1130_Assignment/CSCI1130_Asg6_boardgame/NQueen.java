package boardgame;

import java.awt.Color;
import javax.swing.JButton;
import javax.swing.JOptionPane;

/**
 * @author Michael FUNG
 * @since Nov 2024
 */

public class NQueen extends SinglePlayerGame {

  /**
   * * STUDENTS' FIELDS HERE **
   */
  // E.g., some variables and arrays for keeping game state
  protected int n; // in total of N queens
  protected int[][] numbers;  // game board
  protected int queenCount; // no. of queens

  /**
   * NQueen default constructor of a trivial game.
   */
  public NQueen() {
    this(1);
  }

  /**
   * NQueen constructor.
   *
   * @param n is game side length (width = height = n)
   */
  public NQueen(int n) {
    // super class constructor will call initGame()
    super(n, n);

    /**
     * * STUDENTS' WORK HERE **
     */
    this.n = n; // assign n to variable n in this class
    numbers = new int[n][n];  // initialize 2D array number[][]
    queenCount = 0;
    
    // title of the game application
    String title = "NQueen " + n + "x" + n + ": place " + n + " queens peacefully";
    this.setTitle(title);
    
    // show text in the output text area
    addLineToOutput(title);
    addLineToOutput("Toggle the buttons to place/remove one queen at each step");
    addLineToOutput("One queen is allowed on each row, col and diagonal");
  }

  /**
   * * STUDENTS' WORK HERE **
   */
  // E.g., define some methods, override some methods, etc.
  // See given completed class MagicSquare to get ideas.
  @Override
  protected void initGame() {
    // initialize the gameboard by setting all button to '*'
    for (int y = 0; y < yCount; y++) {
      for (int x = 0; x < xCount; x++) {
        pieces[x][y].setText("*");
        pieces[x][y].setOpaque(true); // set opacity to reveal color background
      }
    }
  }

  @Override
  protected void gameAction(JButton triggeredButton, int x, int y) {
    // check if there are places for queens / button have being seletced
    if (queenCount < n && numbers[x][y] == 0) { // initalized or button have NOT been selected
      numbers[x][y] = 1;  // mark 1 to the button been clicked
      triggeredButton.setText("Q"); // show Q as queen is being placed
      triggeredButton.setBackground(Color.YELLOW);  // display color
      queenCount++;  // add queen
      
      // after placing a new piece, check end game, score will be updated and printed during the check
      checkEndGame(x, y);
      
      // method checkEndGame sets the field gameEnded, proceed accordingly
      if (gameEnded) {
        addLineToOutput("Game ended!");
        JOptionPane.showMessageDialog(null, "Game ended!");
      } else {
        nextStep();
      }
    }
    else if (numbers[x][y] == 0) { // all queen have been selected and user try to palce n+1 queen
      addLineToOutput("All queens on board, remove some!"); // show warning
    } 
    else if (numbers[x][y] == 1) {  // queen have been placed, user try to remove the queen
      numbers[x][y] = 0;  // mark 0 to the button being clicked
      triggeredButton.setText("*"); // show * as the queen is removed
      triggeredButton.setBackground(null);  // remove color effect
      queenCount--;  // remove queen count
      // check game
      checkEndGame(x, y);
      // method checkEndGame sets the field gameEnded, proceed accordingly
      if (gameEnded) {
        addLineToOutput("Game ended!");
        JOptionPane.showMessageDialog(null, "Game ended!");
      } else {
        nextStep();
      }
    }

    // to check if all elements alright
    System.out.println("queenCount = " + queenCount);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        System.out.print("[" + (numbers[j][i] == 1 ? "Q" : " ") + "]");
      }
      System.out.println();
    }
  }
  
  // check if game ends or not
  @Override
  protected boolean checkEndGame(int moveX, int moveY) {
    // initialize game as not ended
    gameEnded = false;
    score = 0;
    
    // initialize sum to find offending queens
    int sum = 0;

    // check row sums
    for (int y = 0; y < yCount; y++) {
      sum = 0;
      for (int x = 0; x < xCount; x++) {
        sum += numbers[x][y];
      }
      if (sum > 1) {  // more than one queen in a row
        score--;
      }
    }

    // check col sums
    for (int x = 0; x < xCount; x++) {
      sum = 0;
      for (int y = 0; y < yCount; y++) {
        sum += numbers[x][y];
      }
      if (sum > 1) {  // more than one queen in a col
        score--;
      }
    }

    // check diagonal \ sum
    // check from lower left hand corner
    for (int xy = -(n - 1); xy <= n - 1; xy++) {
      sum = 0;
      for (int xPos = 0; xPos < n; xPos++) {
        int index = xPos - xy;  // using the patterns to find yPos
        if (index >= 0 && index < n) {
          sum += numbers[xPos][index];
        }
      }
      if (sum > 1) { // more than one queen in \ diagional
        score--;
      }
    }

    // check diagonal / sum
    // check from upper right hand corner
    for (int xy = 0; xy <= 2 * (n - 1); xy++) {
      sum = 0;
      for (int xPos = 0; xPos < n; xPos++) {
        int index = xy - xPos;  // using the patterns to find yPos
        if (index >= 0 && index < n) {
          sum += numbers[xPos][index];
        }
      }
      if (sum > 1) { // more than one queen in / diagional
        score--;
      }
    }
    
    // if queen is less or equal to n, show user's move and score
    if (queenCount <= n) {
      addLineToOutput("Toggle at (" + moveX + ", " + moveY + ")");
      addLineToOutput("Queen count " + queenCount + " / " + n);
      addLineToOutput("Score: " + score);
    }
    // if queen is equal to n, remind user
    if (queenCount == n) {
      addLineToOutput("All pieces filled!");
      // if score is 0, game finished
      if (score == 0) {
        addLineToOutput("Finished in " + super.step + " steps!");
        gameEnded = true;
      }
    }
    
    return gameEnded;
  }

  /**
   * NQueen main() GIVEN
   *
   * @param args is an array of String command line arguments.
   */
  public static void main(String[] args) {
    // create a default size game
    NQueen nqg;
    nqg = new NQueen();
    nqg.setSize(400, 550);
    nqg.verbose = false;

    // create a 4x4 game
    nqg = new NQueen(4);
    nqg.setSize(400, 550);
    nqg.setLocation(500, 50);
    nqg.verbose = true;
    // the game has started and GUI thread will take over here
  }
}
