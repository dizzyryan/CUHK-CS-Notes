package csci1130_2024_midterm;

/**
 * Question 3 (12%)
 */

// Answer:

class Game {
  
  /*
  Finish the following method in a class Game that calculates combinations C(n, r) and returns a
  long-type result where C(n, r) = n! / (n-r)!r! for integers n >= r >= 0. Return 0 if the parameters are
  invalid. You may define some other helper method(s). Assume no overflow occurs. (12%)
  */
  public long C(int n, int r) {
    // answer:
    if (n < r || r < 0) return 0;
    long ans = 1;
    for (int i = 1; i <= r; i++)
      ans = ans * (n - i + 1) / i;
    return ans;
  } // end of method
  
  /*
  The class name of the above work is Game. Write a standard main() method that generates and
  prints the following table if numbers using the method C(n, r), for n from 0 to 9 and all valid r
  values. Display numbers usiong printf with a field width of 4. Do NOT hard-code the printing. (8%)
  
  n=0:   1
  n=1:   1   1
  n=2:   1   2   1
  n=3:   1   3   3   1
  n=4:   1   4   6   4   1
  n=5:   1   5  10  10   5   1
  n=6:   1   6  15  20  15   6   1
  n=7:   1   7  21  35  35  21   7   1
  n=8:   1   8  28  56  70  56  28   8   1
  n=9:   1   9  36  84 126 126  84  36   9   1
  ---NEED NOT PRINT THIS LINE----------------- <- Ruler for your reference
  */
  
  public static void main( String[] args ) {
    Game obj = new Game();
    int n, r;
    
    for (n = 0; n <= 9; n++) {
      System.out.print("n=" + n + ":");
      
      for (r = 0; r <=n; r++)
        System.out.printf("%4d", obj.C(n, r));
      
      System.out.println();
    }
  }
}

