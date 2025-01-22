import java.util.Scanner; 

public class Lab04Ex02 {
  /*
   * @param x integer input
   * @param y integer input
   * @return an integer as the GCD of x and y
   * You don't have to modify this function
   */
  public static int gcd(int x, int y) {
    // The following implements the Euclidean Algorithm for finding GCD
    // See: https://en.wikipedia.org/wiki/Euclidean_algorithm
    while (y != 0) {
      int tmp = y;
      y = x % y;
      x = tmp;
    }
    return x;
  }
  
  /*
   * @param x integer input
   * @param y integer input
   * @return an integer as the LCM of x and y
   */
  public static int lcm(int x, int y) {
    // Try applying the gcd method to get lcm
    int lcmValue = (x * y) / (gcd(x, y));
    return lcmValue;
  }
  
  // compute the gcc and lcm for four input values here
  public static void main(String[] args) {
        
    Scanner scan = new Scanner(System.in);
    int a = scan.nextInt();
    int b = scan.nextInt();
    int c = scan.nextInt();
    int d = scan.nextInt();
    
    int gcdValue, lcmValue;
    
    gcdValue = gcd( gcd( gcd(a, b), c), d);
    lcmValue = lcm( lcm( lcm(a, b), c), d);
        
    // Write your code
    System.out.println("GCD is " + gcdValue);
    System.out.println("LCM is " + lcmValue);
    
  }    
}
