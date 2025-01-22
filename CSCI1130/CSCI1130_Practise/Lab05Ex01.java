import java.util.Scanner;
// let's complete the class Fraction here
class Fraction {
    // define your fields, constructor and more instance methods here
    
    // YOUR CODE HERE
    private int a;
    private int b;
    
    Fraction(int a, int b){
      this.a = a;
      this.b = b;
    }
    
    public void printString(){
      System.out.print(a + "/" + b);
    }
    
    public void printAsDouble(int precision){
      double ans;
      ans = (double) a / (double) b;
      System.out.printf("%." + precision + "f\n", ans);
    }
  
}

class Lab05Ex01 {
  public static void main(String[] args) {
      
    // Do not touch the following lines
    // 
    Scanner keyin = new Scanner(System.in);
    int a, b, precision;

    System.out.println("a? b? precision?");
    a = keyin.nextInt();
    b = keyin.nextInt();
    precision = keyin.nextInt();

    Fraction r;
    r = new Fraction(a, b);
    r.printString();
    System.out.print(" = ");
    r.printAsDouble(precision);
    // The End 
  }
}