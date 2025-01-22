package boardgame;

import javax.swing.JButton;
import javax.swing.JOptionPane;

/**
 * TurnBasedGame is a subclass of BoardGame.
 *
 * Try running this main class:
 * - Click on ALL buttons
 * - Observe Output TextArea, turn number, player names and verbose on/off
 * 
 * Available fields and methods:
 * - player1, player2, currentPlayer, turn, gameEnded
 * - getOpponent() returns a String representing the non-currentPlayer
 * - changeTurn() increments turn AND updates currentPlayer
 * - checkEndGame() analyses game state AND updates gameEnded (true or false)
 * 
 * Subclasses shall override these methods to do something accordingly:
 * - initGame(): setup a new game
 * - gameAction(): do something when a player makes a new move
 * - checkEndGame(): analyse game state
 * 
 * Subclasses may add other fields, methods as well as new main().
 * 
 * @since Nov 2024
 * @author Michael FUNG
 */
public class TurnBasedGame extends BoardGame {
    
    // there are some inherited fields from super class already
    
    // these are new fields
    protected String player1;
    protected String player2;
    protected String currentPlayer;
    protected int turn;
    
    /**
     * TurnBasedGame default constructor of a 4x4 game.
     */
    public TurnBasedGame()
    {
        this(4, 4, "Player 1", "Player 2");
    }
    
    /**
     * TurnBasedGame constructor.
     * @param xCount is number of columns (width)
     * @param yCount is number of rows (height)
     * @param player1 is name of player 1
     * @param player2 is name of player 2
     */
    public TurnBasedGame(int xCount, int yCount, String player1, String player2)
    {
        // superclass BoardGame constructor invokes initGame(), via initializeBoardGame()
        // therefore, fields player1 and player2 are UNINITIALIZED during initGame()
        super(xCount, yCount);
        this.player1 = player1;
        this.player2 = player2;
        this.setTitle("TurnBasedGame " + xCount + "x" + yCount + ": " + player1 + " vs " + player2);
        turn = 0;
        changeTurn();
    }

    // this method cannot be overridden, decided by Michael
    protected final String getOpponent()
    {
        if (currentPlayer.equals(player1))
            return player2;
        else
            return player1;
    }

    // this method cannot be overridden, decided by Michael
    protected final int changeTurn()
    {
        turn++;
        if (turn % 2 == 1)
            currentPlayer = player1;
        else
            currentPlayer = player2;
        addLineToOutput("Turn " + turn + " Current Player: " + currentPlayer);
        return turn;
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
        for (int y = 0; y < yCount; y++)
            for (int x = 0; x < xCount; x++)
                pieces[x][y].setText("?");
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

        // example: set triggered button text as currentPlayer
        triggeredButton.setText(currentPlayer);
        
        // show an output line
        addLineToOutput(currentPlayer + " move at (" + x + ", " + y + ")");

        // after placing a new piece, check end game
        checkEndGame(x, y);
        
        // method checkEndGame sets the field gameEnded, proceed accordingly
        if (gameEnded)
        {
            addLineToOutput("Game ended!");
            JOptionPane.showMessageDialog(null, "Game ended!");
        }
        else
            changeTurn();
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
     * TurnBasedGame main() DEMO
     * @param args 
     */
    public static void main(String[] args)
    {
        // create a default size game of default player names
        TurnBasedGame tbg;
        tbg = new TurnBasedGame();
        tbg.verbose = true;

        // create a 4x3 game for Player A and Player B
        tbg = new TurnBasedGame(4, 3, "Player A", "Player B");
        tbg.setLocation(400, 200);
        tbg.verbose = false;
        // the game has started and GUI thread will take over here
    }
}
