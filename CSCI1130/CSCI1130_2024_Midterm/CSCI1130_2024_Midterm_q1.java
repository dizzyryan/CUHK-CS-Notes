package csci1130_2024_midterm;

/**
 * Question 1 (18%)
 * 
 * Read the following Java program and write down the expected printouts on the standard console
 * output in the box on the right below
 */

class Exchange {
  private static int total = 0;
  private double rate;
  
  public Exchange() {
    rate = 2;
    System.out.println(rate);
  }
  
  public Exchange(double r) {
    rate = r;
    System.out.println(rate);
  }
  
  public double forward(double a) {
    System.out.println(total += a);
    return a * rate;
  }
  
  public double backward(double a) {
    Exchange obj = new Exchange(1 / rate);
    return obj.forward(a);
  }
  
  public static void main(String[] args) {
    Exchange rm2hk = new Exchange();
    System.out.println(rm2hk.forward(10));
    System.out.println(rm2hk.backward(2));
    Exchange hk2tw = new Exchange(4);
    hk2tw.backward(20);
  }
}


/**
 * Solution:
 * 
 * .o's are optional
 * 2.0
 * 10
 * 20.0
 * 0.5
 * 12
 * 1.0
 * 4.0
 * 0.25
 * 32
 */