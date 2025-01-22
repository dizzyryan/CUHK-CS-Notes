package chocofactory;

import javax.swing.JFrame;
import javax.swing.JLabel;

import java.awt.Color;
import java.awt.Graphics;
import javax.swing.JComponent;
import javax.swing.JOptionPane;

/** Given utility ChocoDrawing class for drawing a piece of choco
 *  
 * DO NOT MODIFY this class
 * 
 * @author YPChui
 */
class ChocoDrawing extends JComponent {
    
    // ALL static and instance fields/methods are given, DO NOT MODIFY

    private final int cocoa_radius = 25;
    private final int start_x, start_y;
    private int cocoa_percentage = 100;

    /** Draw the choco in the tray
     * 
     * @param cocoa_percentage percentage of cocoa in the recipe
     * @param start_x starting x-coord to be drawn
     * @param start_y starting y-coord to be drawn
     */
    ChocoDrawing(int cocoa_percentage, int start_x, int start_y) {
        this.cocoa_percentage = cocoa_percentage;
        this.start_x = start_x;
        this.start_y = start_y;
    }    
    
    @Override
    public void paint(Graphics g) {
        int x = start_x;
        
        // draw base cocoa color
        g.setColor(new Color(50+2*(100-cocoa_percentage), 0+2*(100-cocoa_percentage), 0)); // choco brown in color
        g.fillOval(x, start_y, cocoa_radius*2, cocoa_radius*2);
        
        // draw midtone and highlight
        g.setColor(new Color(100+(int)(1.5*(100-cocoa_percentage)), 50+(int)(1.5*(100-cocoa_percentage)), 0)); // lighter brown in color
        g.fillOval(x+5, start_y+6, cocoa_radius, cocoa_radius);
        g.setColor(Color.white);
        g.fillOval(x+10, start_y+11, cocoa_radius/3, cocoa_radius/3);
    }    
}

/** Given ChocoMaker class for receiving choco recipe and draw it on the panel display.
 * 
 * @author YPChui
 */
public class ChocoMaker {
    
    final private JFrame window;
    private ChocoDrawing chocoFigure;
    private final static int MARGIN_LEFT = 20, MARGIN_TOP = 20;
    private static int numOfChoco = 0;
    private static final int SLOT_WIDTH = 90;
    private static final int MAX_NUM_PIECE = 4;

    /** Default constructor
     * 
     */
    public ChocoMaker() {
        window = new JFrame("Choco Maker");
        window.setSize(SLOT_WIDTH*MAX_NUM_PIECE+30, 140);
        window.setLocation(20, 20);
        window.setVisible(true);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    
    /** Make choco by drawing and printing console message
     * 
     * @param chocoRecipe a reference to a choco recipe object
     * @return 1 for successful making, -1 means failing due to out of Java beans
     */
    public int makeChoco(ChocoRecipe chocoRecipe) {
        if(numOfChoco>=MAX_NUM_PIECE) {
            JOptionPane.showMessageDialog(null, "Out of Cocoa Beans!!");
            return -1;
        } else {
            chocoRecipe.printToConsole();
            return makeChoco(chocoRecipe.getName(), chocoRecipe.getCocoaPercent());
        }
    }
    
    /** Make choco by drawing 
     * 
     * @param name name of the choco recipe
     * @param cocoaPercent cocoa percent of the choco recipe
     * @return 1 for successful making
     */
    private int makeChoco(String name, int cocoaPercent) {
        
        // Draw the choco name on top
        JLabel chocoName = new JLabel(name);
        chocoName.setBounds(MARGIN_LEFT+numOfChoco*SLOT_WIDTH, -40, 150, 100);
        window.getContentPane().add(chocoName);
        
        // Draw a piece of choco
        chocoFigure = new ChocoDrawing(cocoaPercent, MARGIN_LEFT+SLOT_WIDTH*numOfChoco, MARGIN_TOP+10);
        window.getContentPane().add(chocoFigure); 
        
        numOfChoco++;
        window.revalidate();
        window.repaint();    
        return 1;
    }
    
  /** Get the user input String from Choco Menu<br>
   *  A helper method for easy processing in flow control<br>
   *    - parsing the user input String,<br>
   *    - handling Non-Number-Format exception, and<br>
   *    - generalizing the user input as an integer of task, or error code
   *
   * @return an integer of user choice: 1, 2, 3 or 4; or an error code:<br>
   *    -1 means Cancel/Close,<br>
   *    -2 means out-of-range user input i.e. <1 or >4
   */
  public static int getChoiceFromChocoMenu() {
    String choice;
    choice = ChocoFactory.showChocoMenu();
    if (choice == null) {
      return -1; // "Cancel" is clicked
    }
    
    int task;
    try { // exception handling for Invalid Number Format
      task = Integer.parseInt(choice);
      if(task < 1 || task > 4) {
          task = -2;
      }
    } catch (NumberFormatException e) {
      task = -1;
    }
    return task;
  }

}