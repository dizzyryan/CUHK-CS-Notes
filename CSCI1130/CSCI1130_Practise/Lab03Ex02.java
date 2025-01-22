import java.util.*;

class Lab03Ex02 {
    
    // calculate the value
    public static void main(String args[]){
        // Please write down the formula for T_i on paper before
        // you start writing the program
        System.out.printf("n? ");
        Scanner keyboard = new Scanner(System.in);
        int n = keyboard.nextInt();
        double answer = 3.0;
        System.out.printf("%.6f\n", answer);
        int counter;
        for (counter = 1; counter < n; counter++){
            answer += (double) Math.pow(-1, counter + 1) * 4.0 / ((2.0*counter)*(2.0*counter + 1)*(2.0*counter + 2));
            if (counter <= 1 || (n - counter) <= 2){
                System.out.printf("%.6f\n", answer);
            }
            else if (counter == 2){
                System.out.println("...");
            }
        }
        
    }  
}



