package oldpiformula;

import java.util.Scanner;

// class declaration
public class OldPiFormula {
    
    /** Compute arctangent based on Taylor series expansion and print steps
    *
    * @param z the input arguments in double
    * @param m the number of terms to be summed in int
    * @return result of arctan(z) in double
    */
    
    // method to find the value of arctan
    public double arctan(double z, int m) {
        // ... compute and print ...
        int counter;
        int power;
        double arctanAns = 0;
        double temp = 1 / z;
        
        System.out.printf("arctan(1/" + (int) temp + "):\n");
        
        // compute and print values of acrtan
        for (counter = 1; counter <= m; counter++){
            // calculate the power of z
            power = 2 * counter - 1;
            arctanAns += Math.pow(-1, counter + 1) * ((double) Math.pow(z, power) / power);
            if (counter <= 2 || (m - counter + 1) <= 2)
                System.out.printf("%.13f\n", arctanAns);
            else if (counter == 3)
                System.out.println("...");
        }
        return arctanAns;
    }
    
    // method to scan values and validate
    public int scanValue(){
        Scanner keyboard = new Scanner(System.in);
        int temp = keyboard.nextInt();
        
        // validation of user input
        if (temp <= 0){
            System.out.println("Invalid input!");
            System.exit(1);
        }
        
        // return the value to the variable
        return temp;
    }
    
    public static void main(String[] args) {
        // create a new Scanner object, named keyboard
        
        // scan for four inputs
        OldPiFormula myTest = new OldPiFormula();
        System.out.print("a? ");
        int a = myTest.scanValue();
        System.out.print("b? ");
        int b = myTest.scanValue();
        System.out.print("c? ");
        int c = myTest.scanValue();
        System.out.print("m? ");
        int m = myTest.scanValue();
        // use if-statement to validate value of m
        if (m > 20){
            System.out.println("Invalid input!");
            System.exit(1);
        }
        
        // ... get inputs, call arctan() and find out pi ...
        
        double arctanB = myTest.arctan((1.0 / (double) b), m);
        
        double arctanC = myTest.arctan((1.0 / (double) c), m);
        
        // use formula to find PI
        double answer = 4.0 * (a * arctanB - arctanC);
        
        System.out.printf("pi: %.13f\n", answer); // send printf() message
    }

// end
}