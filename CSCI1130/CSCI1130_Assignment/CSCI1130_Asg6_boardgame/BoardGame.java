package boardgame;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;
import java.util.concurrent.TimeUnit;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

/**
 * BoardGame base class.
 * This is a sub-class of JFrame (basically a window.)
 * 
 * BoardGame GUI hierarchy
 * +--------------------------------------------+
 * |                                            |
 * | board JPanel                               |
 * |                                            |
 * | contains pieces[][]                        |
 * |                                            |
 * |   (0, 0)         width xCount              |
 * |                                            |
 * |   height                                   |
 * |   yCount                                   |
 * |                                            |
 * | each element is a clickable JButton        |
 * | each stores and shows a String text        |
 * |                                            |
 * +--------------------------------------------+
 * |                                            |
 * | output JTextArea embedded in a JScrollPane |
 * |                                            |
 * +--------------------------------------------+
 * 
 * Try running this main class:
 * - Click on DEMO button many times
 * - Click on Exit! button
 * 
 * Subclasses shall override these two methods to do something accordingly:
 * - initGame(): setup a new game
 * - gameAction(): do something when a player makes a new move
 * 
 * Subclasses may add other fields, methods as well as new main().
 * 
 * DO NOT modify other parts of the program that deals with GUI!!
 * 
 * @since Nov 2024
 * @author Michael FUNG
 */
public class BoardGame extends JFrame implements ActionListener {

    // protected fields can be inherited and accessed in subclasses
    protected int xCount;
    protected int yCount;
    protected JButton[][] pieces;
    protected boolean gameEnded;

    // private GUI related instance fields
    private JPanel      board;
    private JTextArea   output;
    
    // a flag controlling more or less output
    public boolean verbose = true;
    
    // BoardGame default constructor, a demo game of 3x3
    public BoardGame()
    {
        initializeBoardGame(3, 3);
    }
    
    /**
     * BoardGame constructor creates a base game of xCount x yCount pieces
     * @param xCount is number of columns (width)
     * @param yCount is number of rows (height)
     */
    public BoardGame(int xCount, int yCount)
    {
        initializeBoardGame(xCount, yCount);
    }
    
    /*
     * This methods prepares a window title for the BoardGame.
     * This method CANNOT be modified/ overridden by subclasses, decided by Michael
     */
    @Override
    public final void setTitle(String title)
    {
        super.setTitle(title);
    }
            
    /*
     * This methods prepares a GUI for the BoardGame.
     * This method CANNOT be modified/ overridden by subclasses, decided by Michael
     */
    protected final void initializeBoardGame(int xCount, int yCount)
    {
        // copy parameters to instance fields and create pieces buttons
        this.xCount = xCount;
        this.yCount = yCount;
        // do NOT care array row-major order, just let X-dimension come first
        // this is more intuitive while it may not sacrifice performance generally
        pieces = new JButton[xCount][yCount];
        gameEnded = false;

        // adjust this JFrame object layout
        this.setTitle("BoardGame " + xCount + "x" + yCount);
        this.setLayout(new GridBagLayout());
        GridBagConstraints layoutConstraints = new GridBagConstraints();
        
        // prepare board panel
        board = new JPanel();
        board.setLayout(new GridLayout(yCount, xCount));
        board.setPreferredSize(new Dimension(xCount * 80, yCount * 80));

        // create pieces buttons on board
        for (int y = 0; y < yCount; y++)
            for (int x = 0; x < xCount; x++)
            {
                pieces[x][y] = new JButton("(X" + x + ", Y" + y + ")");
                pieces[x][y].setActionCommand(x + "," + y);
                pieces[x][y].setFocusable(false);
                
                // register this BoardGame object as ActionListener "on button click"
                pieces[x][y].addActionListener(this);

                // add this piece to GridLayout top-to-bottom, left-to-right
                board.add(pieces[x][y]);
            }

        // add board panel to this JFrame object
        layoutConstraints.gridx = 0;
        layoutConstraints.gridy = 0;
        layoutConstraints.weightx = 1;
        layoutConstraints.weighty = 1;
        layoutConstraints.anchor = GridBagConstraints.CENTER;
        layoutConstraints.fill   = GridBagConstraints.BOTH;
        this.add(board, layoutConstraints);
        
        // prepare output textarea
        output = new JTextArea();
        output.setEditable(false);
        output.setText("Output TextArea:");
        JScrollPane scrollTextPane = new JScrollPane(output);
        scrollTextPane.setPreferredSize(new Dimension(100, 120));

        // add output textarea to this JFrame object
        layoutConstraints.gridx = 0;
        layoutConstraints.gridy = 1;
        layoutConstraints.weightx = 1;
        layoutConstraints.weighty = 0;
        layoutConstraints.anchor = GridBagConstraints.SOUTH;
        layoutConstraints.fill   = GridBagConstraints.HORIZONTAL;
        this.add(scrollTextPane, layoutConstraints);        
        
        // adjust this JFrame object properties
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setVisible(true);
        this.pack();
        
        // invoke a standalone overridable method for different boardgame
        initGame();
        
        // initially, no animation is on-going, allow placing new piece
        allowPlacingNewPiece = true;
    }

    /**
     * Allow this thread to wait/ delay for an amount of time
     * while other tasks can happen concurrently, GUI repaints and updates.
     * For example, this is useful during animations.
     * @param delayInmillisecond is the minimum amount of time to be delayed
     */
    protected void delayInMSwhileRunningOtherTasks(long delayInmillisecond)
    {
        // slow down this process by sleeping this thread
        try {
            TimeUnit.MILLISECONDS.sleep(delayInmillisecond);
        } catch (InterruptedException exceptionObject) {
            Thread.currentThread().interrupt();
        }
    }
    
    /**
     * allowPlacingNewPiece is a multi-thread programming specific field indicating
     * if the previous move (e.g. animation) has finished such that
     * placing new piece is allowed
     */
    protected boolean allowPlacingNewPiece;
    
    /**
     * This is a callback method on button click (for all pieces).
     * This method is declared in ActionListener AND shall be overridden.
     * This method CANNOT be modified/ overridden by subclasses, decided by Michael.
     * @param actionObject is generated by the system
     */
    @Override
    public final void actionPerformed(ActionEvent actionObject) {
        if (gameEnded)
            return;
        
        if (actionObject.getSource() instanceof JButton)
        {
            JButton triggeredButton = (JButton) actionObject.getSource();
            
            if (verbose)
                addLineToOutput("*** Clicked " + triggeredButton.getActionCommand() + 
                                " button originally shown '" + triggeredButton.getText() + "'");

            String[] coord = triggeredButton.getActionCommand().split(",");
            int x = Integer.parseInt(coord[0]);
            int y = Integer.parseInt(coord[1]);
            
            // invoke a standalone overridable method for different boardgames
            // an asynchronous task executing in a new thread to allow animation, etc.
            // IF gameAction() TAKES LONG, admission control is REQUIRED, e.g.,
            // using a flag allowPlacingNewPiece, otherwise, gameAction sequence
            // MAY BE WRONG!!!
            // if previous action is still on-going, disallow placing new piece
            if (!allowPlacingNewPiece)
                return;
            new Thread(
                new Runnable() {
                    @Override
                    public void run() {
                        // this method runs in a separate Thread, so concurrency is allowed!!

                        // disallow placing new piece during animation of a dropping piece
                        allowPlacingNewPiece = false;
                        // AFTER setting the above to false, MUST set it back to true BEFORE RETURN!

                        gameAction(triggeredButton, x, y);

                        // allow placing new piece after animation
                        allowPlacingNewPiece = true;
                    }
                }
            ).start();
            // above can be written in lambda expression OR anonymous inner class
        }
    }
    
    /**
     * Add a line to output JTextArea, scroll to the end to show latest content.
     * This method CANNOT be modified/ overridden by subclasses, decided by Michael.
     * @param str is a line of text to append
     */
    protected final void addLineToOutput(String str)
    {
        output.append("\n");
        output.append(str);
        output.setCaretPosition(output.getDocument().getLength());
    }

    /************************************************************************************
     * Students are expected to inherit and override the following methods in subclasses
     ************************************************************************************/
    
    /**
     * This method initializes a game, e.g., setting up pieces labels, setting scores, etc.
     * This method is to be overridden and defined in sub-classes for different games.
     */
    protected void initGame()
    {
        pieces[0][0].setText("DEMO");
        pieces[0][0].setForeground(Color.RED);

        pieces[2][1].setText("Exit!");
        pieces[2][1].setForeground(Color.GREEN);

        Random rng = new Random();
            
        pieces[rng.nextInt(xCount)][yCount-1].setText("???");

    }

    /**
     * This method implements game actions.
     * This method is to be overridden and defined in sub-classes for different games.
     * This method is invoked by the general actionPerformed() callback method.
     * @param triggeredButton is the button clicked by the user
     * @param x is the x-coordinate of the clicked button
     * @param y is the y-coordinate of the clicked button
     */
    protected void gameAction(JButton triggeredButton, int x, int y)
    {
        // EXAMPLE action to introduce cute behaviour on clicking DEMO button
        if (x == 0 && y == 0)
        {
            pieces[xCount-1][yCount-1].setText("Oops!");
            
            // change text color of some random button to BLUE
            Random rng = new Random();
            pieces[rng.nextInt(xCount)][rng.nextInt(yCount)].setForeground(Color.BLUE);
        }
        else
            // EXAMPLE action to disable the clicked button
            triggeredButton.setEnabled(false);
        
        // DEMO action on clicking Exit! at pieces[2][1]
        if (x == 2 && y == 1)
        {
            addLineToOutput("Game ended!");
            JOptionPane.showMessageDialog(null, "Game ended!");
        }
    }
    
    /**
     * BoardGame main() DEMO.
     * Demonstrates how to start new boardgames.
     * @param args 
     */
    public static void main(String[] args) {
        // create a DEMO board of width x height = 7 x 5 at screen coord (300, 100)
        BoardGame baseGame;
        baseGame = new BoardGame(7, 5);
        baseGame.setLocation(300, 100);
        
        // create a default DEMO board of 3x3 at (0, 0)
        BoardGame baseGame3x3 = new BoardGame();
        baseGame3x3.setLocation(20, 0);
        // the game has started and GUI thread will take over here
    }
    
}
