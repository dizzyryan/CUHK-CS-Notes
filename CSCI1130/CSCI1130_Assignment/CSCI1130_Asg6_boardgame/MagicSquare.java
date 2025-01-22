package boardgame;

import java.awt.Color;
import javax.swing.JButton;
import javax.swing.JOptionPane;

/**
 * MagicSquare is a SinglePlayerGame, that is a BoardGame.
 * @author Michael FUNG
 * @since Nov 2024
 */
public class MagicSquare extends SinglePlayerGame {
    protected int n;
    protected int maxStep;
    protected int lineSum;
    protected int maxScore;
    protected int[][] numbers;
    
    /**
     * MagicSquare default constructor of a trivial game.
     */
    public MagicSquare()
    {
        this(1);
    }
    
    /**
     * MagicSquare constructor.
     * @param n is game side length (width = height = n)
     */
    public MagicSquare(int n)
    {
        // super class constructor will call initGame()
        super(n, n);
        
        this.n = n;
        maxStep = n * n;
        lineSum = (maxStep + 1) * n / 2;
        maxScore = 2 * n + 2;  // n rows, n cols, two diagonals
        numbers = new int[n][n];  // initially all zeroes
        
        String title = "MagicSquare " + xCount + "x" + yCount + ": fill [1, " + maxStep + "]";
        this.setTitle(title);
        addLineToOutput(title);
        addLineToOutput("Each row, col and diagonal should sum up to " + lineSum);        
        addLineToOutput("There are " + maxScore + " line sums and each worth one point");
        addLineToOutput("To win: get the max score " + maxScore);
    }

    /**
     * Demonstrate the same initGame() behaviour as NOT overriding a method.
     * Further initializations may be done in constructor later.
     */
    @Override
    protected void initGame()
    {
        super.initGame();
    }
    
    /**
     * This method implements game actions.
     * This method can be overridden and defined in sub-classes for different games.
     * This method is invoked when button at (x, y) is clicked/triggered.
     */
    @Override
    protected void gameAction(JButton triggeredButton, int x, int y)
    {
        // disable the triggered button
        triggeredButton.setEnabled(false);
        
        // store current step number
        numbers[x][y] = step;
        
        // set triggered button text as "[step]"
        String newPieceText = "[" + step + "]";
        triggeredButton.setText(newPieceText);
        
        // set button Color to YELLOW
        triggeredButton.setBackground(Color.YELLOW);

        // show an output line
        addLineToOutput(newPieceText + " move at (" + x + ", " + y + ")");

        // after placing a new piece, check end game
        // score will be updated and printed during the check
        checkEndGame(x, y);
        
        // method checkEndGame sets the field gameEnded, proceed accordingly
        if (gameEnded)
        {
            addLineToOutput("Game ended!");
            JOptionPane.showMessageDialog(null, "Game ended!");
        }
        else
            nextStep();
    }

    /**
     * checkEndGame considers the latest move at (moveX, moveY)
     * and determines if gameEnded is true or false.
     * This method also updates and prints score.
     * @param moveX is the x-coordinate of the latest move
     * @param moveY is the y-coordinate of the latest move
     * @return end game status: true or false
     */
    @Override
    protected boolean checkEndGame(int moveX, int moveY)
    {
        gameEnded = true;
        score = 0;
        
        if (verbose)
            System.out.print(n + "x" + n + " checkEndGame():");

        int sum = 0;
        
        // check row sums
        for (int y = 0; y < yCount; y++)
        {
            sum = 0;
            for (int x = 0; x < xCount; x++)
                sum += numbers[x][y];
            if (verbose)
                System.out.print(" " + sum);
            if (sum == lineSum)
                score++;
        }
        
        // check col sums
        for (int x = 0; x < xCount; x++)
        {
            sum = 0;
            for (int y = 0; y < yCount; y++)
                sum += numbers[x][y];
            if (verbose)
                System.out.print(" " + sum);
            if (sum == lineSum)
                score++;
        }
                
        // check diagonal \ sum
        sum = 0;
        for (int xy = 0; xy < n; xy++)
            sum += numbers[xy][xy];
        if (verbose)
            System.out.print(" " + sum);
        if (sum == lineSum)
            score++;
                        
        // check diagonal / sum
        sum = 0;
        for (int xy = 0; xy < n; xy++)
            sum += numbers[xy][n-1 - xy];
        if (verbose)
            System.out.println(" " + sum);
        if (sum == lineSum)
            score++;

        addLineToOutput("Score: " + score);
        
        if (step != maxStep)
        {
            gameEnded = false;
            return gameEnded;
        }

        addLineToOutput("All pieces filled!");
        gameEnded = true;
        
        if (score == maxScore)
            addLineToOutput("Well done!");
        else
            addLineToOutput("You failed!");
        
        return gameEnded;
    }
            
    
    /**
     * MagicSquare main() DEMO
     * @param args 
     */
    public static void main(String[] args)
    {
        // create a default size game
        MagicSquare msq;
        msq = new MagicSquare();
        msq.setSize(400, 550);
        msq.verbose = false;

        // create a 3x3 game
        msq = new MagicSquare(3);
        msq.setSize(400, 550);
        msq.setLocation(500, 50);
        msq.verbose = true;
        // the game has started and GUI thread will take over here
    }    
}
