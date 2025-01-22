import java.util.*;

class Lab04Ex01 {
    
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        System.out.println("Please enter the height of the tree:");
        int height = keyboard.nextInt();
        
        System.out.println("Look!");
        int i, counter;
        
        for (counter = 1; counter <= height; counter++){
            for (i = 0; i < (height - counter); i++){
                System.out.print(" ");
            }
            for (i = 0; i < 2*counter-1; i++){
                System.out.print("^");
            }
            System.out.print("\n");
        }
        
        for (counter = 0; counter < (height - 1); counter++){
            System.out.print(" ");
        }
        System.out.println("H");
    }
}