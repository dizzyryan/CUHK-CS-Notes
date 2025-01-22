import java.util.*;

class Lab02Ex01 {
  public static void main(String[] args) {

    Scanner keyboard = new Scanner(System.in);
    int i, j;
    System.out.println("Input first number:");
    i = keyboard.nextInt();
    
    System.out.println("Input second number:");
    j = keyboard.nextInt();
    
    int sum = i + j;
    
    if (sum % 2 == 0){
        System.out.println("Sum is even");
    }
    else
        System.out.println("Sum is odd");
    
  }
}
