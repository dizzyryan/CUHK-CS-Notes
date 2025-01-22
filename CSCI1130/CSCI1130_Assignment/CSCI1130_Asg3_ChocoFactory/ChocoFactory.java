package chocofactory;

// imports for JOptionPane, Random, etc.
import javax.swing.JOptionPane;
//import java.util.Random;

public class ChocoFactory {

  private static String[] chocoNames;
  private static int[] cocoaPercents;
  private static ChocoMaker chocoMaker;

  /**
   * Show a menu of choices and get user's input, given method
   * @return a String of user input: "1","2",…,"4", null means Cancel/Close
   */
  public static String showChocoMenu() {
    /*** student's work to display choco menu items ***/
    String chocoMenu = """
                       Make Choco: Input your choice
                       1. 100% Noir
                       2. 70% Dark
                       3. [40%~69%] Candied or Delish
                       4. Quit""";
    return JOptionPane.showInputDialog(chocoMenu);
  }

  /**
   * @param args the command line arguments
   */
  public static void main(String[] args) {

    // Example use of ChocoMaker with a ChocoRecipe, you should replace them with your own logic
    
    chocoMaker = new ChocoMaker();
    
    // initialize choco names & milk percent

    /*** student's work here to initialize values, call getChoiceFromChocoMenu()of the ChocoTimeHelper class,            where Number-Format Exceptions are handled for you.
       Modify the following sample code fragment to start processing user requests in a loop ***/
    
    // STUDENT WORK HERE
    
    // use while loop to process user request
    while (true){
      // get choice from choco menu
      int chocoMenuChoice = ChocoMaker.getChoiceFromChocoMenu();
      int returnValue; // return value from dialog box
      ChocoRecipe choco = new ChocoRecipe();
      
      // if user closed or cancelled
      if (chocoMenuChoice == -1) {
        System.out.println("User closed or cancelled dialog box");
        JOptionPane.showMessageDialog(null,"Input again");
        continue;
      }
      
      else if (chocoMenuChoice == -2) {
        System.out.println("User input invalid number format");
        JOptionPane.showMessageDialog(null,"Input again");
        continue;
      }
      
      // if user choose classic
      else if (chocoMenuChoice == 1) {
        // System.out.println("User picked 1"); // optionally printed for debugging purposes
        choco = new ChocoRecipe();
      }
      
      else if (chocoMenuChoice == 2) {
        // System.out.println("User picked 2"); // optionally printed for debugging purposes
        choco = new ChocoRecipe("Dark", 70);
      }
      
      else if (chocoMenuChoice == 3) {
        // System.out.println("User picked 3"); // optionally printed for debugging purposes
          
        // ask if users want candied or delish
        int candiedOrDeish = JOptionPane.showConfirmDialog(null,"Candied?","Candied or Delish",JOptionPane.YES_NO_OPTION);
          
        if (candiedOrDeish == 0){ // Yes - Candied case
          choco = new ChocoRecipe("Candied");
        }
        
        else if (candiedOrDeish == 1){ // No - Delish case
          choco = new ChocoRecipe("Delish");
        }
      }
      
      // user quit the program
      else if (chocoMenuChoice == 4) {
        break;
      }
      returnValue = chocoMaker.makeChoco(choco);
      // check if choco beans are still available, if not, exit
      if (returnValue == -1){
        break;
      }
      JOptionPane.showMessageDialog(null,"A new " + choco.getName() + " is made!");
      
    }
    
    JOptionPane.showMessageDialog(null, "Bye!");
    System.exit(0);
    
  }
}