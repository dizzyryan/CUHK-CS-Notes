import java.util.*;

class Lab02Ex02 {
    
    public static void main(String[] args) {
        System.out.println("Input Monthly Salary:");
        Scanner keyboard = new Scanner(System.in);
        int income = keyboard.nextInt();
        int contribution = 0;
        
        if (income >= 7100 && income <= 30000){
            contribution += Math.round((double) income * 0.05);
        }
        
        if (income > 30000){
            contribution += 1500;
        }
        System.out.printf("Monthly Mandatory Contribution:\n" + contribution + "\n");
    }
}