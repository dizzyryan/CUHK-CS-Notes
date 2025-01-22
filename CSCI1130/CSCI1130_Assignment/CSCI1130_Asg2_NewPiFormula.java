package newpiformula;

import java.util.Scanner;
import org.apache.commons.math3.special.Gamma;

/**
 *
 * @author ypchui
 */
public class NewPiFormula {

    /**
     * @param args the command line arguments
     */
    
    public static void main(String[] args) {
        // Start your code here
        
        // Use the following to scan user input
        Scanner keyboard = new Scanner(System.in);
        
        // Read lambda
        System.out.print("lambda? ");
        int lambda = keyboard.nextInt();
        boolean checkLambda = lambda <= 20 && lambda >= 1;
        if (checkLambda == false){
            System.out.println("Invalid input!");
            System.exit(0);
        }
        
        // Use the following to read maximum number of terms
        System.out.print("m? ");
        int maxNumber = keyboard.nextInt();
        boolean checkMaxNumber = maxNumber <= 30 && maxNumber >= 1;
        if (checkMaxNumber == false){
            System.out.println("Invalid input!");
            System.exit(0);
        }
       
        // Use the following to count the answer
        double factorial = 1;
        double answer = 0;
        double piSum = 0;
       
        for (int counter = 1; counter <= maxNumber; counter++){
            // Use this part to calculate factorial
            factorial *= counter;
            
            // Use the following to find the answer of different part of the function
            double firstPart = 1.0 / factorial;
            double secondPart = 1.0 / ((double) counter + (double) lambda) - 4.0 / (2.0 * (double) counter + 1.0);
            double thirdPart = ((Math.pow((2 * counter + 1),2))/(4 * ((double) counter + (double) lambda))) - (double) counter;
            double gammaFunction = Gamma.gamma(thirdPart + ((double) counter - 1)) / Gamma.gamma(thirdPart);
            
            // Use the following to find the answer of the summation
            answer += firstPart * secondPart * gammaFunction;
            
            // Use the following to find the value of PI
            piSum = 4.0 + answer;
            
            // Use the following to see if the value should be printed or not
            if (counter <= 3 || (maxNumber - counter + 1) <= 3){
                System.out.print("m = " + counter + "; ");
                System.out.printf("pi = %.12f\n", piSum);
            }
            else if (counter == 4){
                System.out.println("...");
            }       
        }
        // Use the following to print Error
        System.out.printf("Error = %.12f\n", Math.PI - piSum);
       // End of your code
    } 
}
