import java.util.*;

class Lab03Ex01 {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        long factorial = 1L;
        int n;
        System.out.println("Input:");
        n = keyboard.nextInt();

        // code here ...
        int counter;
        for (counter = 1; counter <= n; counter++){
            factorial *= counter;
        }
        System.out.println("The factorial is " + factorial);
    }
}