package boardgame;

import javax.swing.JButton;
import javax.swing.JOptionPane;

/**
 * @since Nov 2024
 * @author Michael FUNG
 */
public class SinglePlayerGame extends BoardGame {
    
    // there are some inherited fields from super class already
    
    // these are new fields
    protected int step;
    protected int score;
    
    /**
     * SinglePlayerGame default constructor of a 4x4 game.
     */
    public SinglePlayerGame()
    {
        this(4, 4);
    }
    
    /**
     * SinglePlayerGame constructor.
     * @param xCount is number of columns (width)
     * @param yCount is number of rows (height)
     */
    public SinglePlayerGame(int xCount, int yCount)
    {
        // superclass BoardGame constructor invokes initGame(), via initializeBoardGame()
        super(xCount, yCount);
        this.setTitle("SinglePlayerGame " + xCount + "x" + yCount);
        addLineToOutput("Score: " + score);
        nextStep();
    }

    // this method cannot be overridden, decided by Michael
    protected final int nextStep()
    {
        step++;
        addLineToOutput("Step " + step + ":");
        return step;
    }

    /***************************************************************************
     * Subclasses are expected to inherit and may override the following methods
     ***************************************************************************/

    /**
     * Initialize all buttons in a game.
     */
    @Override
    protected void initGame()
    {
        // by defualt, set all pieces to "?"
        for (int y = 0; y < yCount; y++)
            for (int x = 0; x < xCount; x++)
            {
                pieces[x][y].setText("?");
                // set opacity to reveal color background
                pieces[x][y].setOpaque(true);
            }

        score = 0;
        step = 0;
    }

    /**
     * Set score
     * @param newScore can be +/-.
     * @return updated score
     */
    protected int setScore(int newScore)
    {
        return score = newScore;
    }
    
    /**
     * This method implements game actions.
     * This method can be overridden and defined in sub-classes for different games.
     * This method is invoked when button at (x, y) is clicked/triggered.
     */
    @Override
    protected void gameAction(JButton triggeredButton, int x, int y)
    {
        // by default, the triggered button is disabled
        // subclasses may override (change) this behaviour
        triggeredButton.setEnabled(false);
        
        // example: set triggered button text as "[step]"
        String newPieceText = "[" + step + "]";
        triggeredButton.setText(newPieceText);
        
        // show an output line
        addLineToOutput(newPieceText + " move at (" + x + ", " + y + ")");

        // example: reduce score by ten on each step/move
        setScore(score - 10);
        addLineToOutput("Score: " + score);

        // after placing a new piece, check end game
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
     * @param moveX is the x-coordinate of the latest move
     * @param moveY is the y-coordinate of the latest move
     * @return end game status: true or false
     */
    protected boolean checkEndGame(int moveX, int moveY)
    {
        // sample check gameEnded
        // by default, all "?" are replaced/clicked
        gameEnded = true;
        for (int y = 0; y < yCount; y++)
            for (int x = 0; x < xCount; x++)
                if (pieces[x][y].getText().equals("?"))
                {
                    gameEnded = false;
                    return gameEnded;
                }
        addLineToOutput("All pieces filled!");
        return gameEnded;
    }
            
    
    /**
     * SinglePlayerGame main() DEMO
     * @param args 
     */
    public static void main(String[] args)
    {
        // create a default size game
        SinglePlayerGame spg;
        spg = new SinglePlayerGame();
        spg.verbose = true;

        // create a 5x5 game
        spg = new SinglePlayerGame(5, 3);
        spg.setLocation(400, 200);
        spg.verbose = false;
        // the game has started and GUI thread will take over here
    }
}
