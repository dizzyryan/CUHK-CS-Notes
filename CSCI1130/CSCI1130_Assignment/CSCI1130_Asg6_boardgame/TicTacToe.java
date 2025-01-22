package boardgame;

import java.awt.Color;

/**
 * TicTacToe is a subclass of TurnBasedGame.
 * @author Michael FUNG
 */
public class TicTacToe extends TurnBasedGame {
    
    // try using default access modifier
    String winner;
    
    // TicTacToe default and only constructor
    public TicTacToe()
    {
        super(3, 3, "X", "O");
        this.setTitle("Tic Tac Toe");
    }

    // initialize TicTacToe board with all blanks
    @Override
    protected void initGame()
    {
        for (int y = 0; y < yCount; y++)
            for (int x = 0; x < xCount; x++)
                pieces[x][y].setText(" ");
    }
    
    
    // THIS GAME DOES NOT OVERRIDE inherited method gameAction()
    // The inherited method from superclass TurnBasedGame is adequate and good.
    // - a clicked button will be disabled (grayed and not clickable) any more.
    // - new move will show proper currentPlayer name
    // - it invokes checkEndGame() AND changeTurn()
    
    
    // check 3-connected same-player pieces to determine gameEnded by simple hard-coding
    @Override
    protected boolean checkEndGame(int moveX, int moveY)
    {
        // short-circuit OR checkings
        if (checkConnect3(0,0, 0,1, 0,2) ||
            checkConnect3(1,0, 1,1, 1,2) ||
            checkConnect3(2,0, 2,1, 2,2) ||

            checkConnect3(0,0, 1,0, 2,0) ||
            checkConnect3(0,1, 1,1, 2,1) ||
            checkConnect3(0,2, 1,2, 2,2) ||
        
            checkConnect3(0,0, 1,1, 2,2) ||
            checkConnect3(0,2, 1,1, 2,0))
        {
            gameEnded = true;
            addLineToOutput("Winner is " + winner + "!");
        }
        else
            // TicTacToe specific: turn number == 3x3 == 9 as end-game condition
            if (turn == xCount * yCount)
            {
                gameEnded = true;
                addLineToOutput("Draw game!");
            }
        return gameEnded;
    }
    
    // private helper method
    private boolean checkConnect3(int x0, int y0, int x1, int y1, int x2, int y2)
    {
        if (pieces[x0][y0].getText().equals(currentPlayer) &&
            pieces[x1][y1].getText().equals(currentPlayer) &&
            pieces[x2][y2].getText().equals(currentPlayer))
        {
            winner = currentPlayer;
            // color the connected winning pieces in YELLOW
            pieces[x0][y0].setBackground(Color.YELLOW);
            pieces[x1][y1].setBackground(Color.YELLOW);
            pieces[x2][y2].setBackground(Color.YELLOW);
            pieces[x0][y0].setOpaque(true);
            pieces[x1][y1].setOpaque(true);
            pieces[x2][y2].setOpaque(true);
            return true;
        }
        return false;
    }
    
    public static void main(String[] args)
    {
        TicTacToe ttt;
        ttt = new TicTacToe();
        ttt.setLocation(400, 200);
        ttt.verbose = false;
        // the game has started and GUI thread will take over here
    }

}
