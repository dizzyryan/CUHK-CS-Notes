package csci1130_2024_midterm;

import java.util.Scanner;

/**
 * Question 4 (22%)
 * Answer the following questions in Java for estimating π.
 * π/4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 - ...  Equation (1)
 */

class Employee {
  /*
  a) Declare an 8-bit integer variable named m. (1%)
  byte m;
  
  b) Declare a double-type variable named pi. (1%)
  double pi;
  
  c) Declare and initialize a varibale key with a new Scanner object over System.in. (2%)
  Scanner key = new Scanner( System.in );
  
  d) Display a prompt "Input m:" and then use method nextInt() of the Scanner object
     varibale key to read an input into m form the user, with proper type casting. (2%)
  System.out.println("Input m:");
  m = (byte) key.nextInt();
  
  e) Validate that 1 <= m < 30 and print "OK; otherwise print "XX". Just let the program
     move on, independent of the result. (4%)
  if (m >= 1 && m < 30) System.out.println("OK");
  else System.out.println("XX");
  */
  
  /*
  f) Complete the following method, which prints and calculates the k-th term if Equation(1)
    as +1/X format where X indicates denominator packed with sign either + or -, e.g.
    if k is 2, it prints -1/3 (4 character);
    if k is 9, it prints +1/17 (5 character); etc.
    The method returns the calcukated term as a double-type value.
    Assume some valid value of k where 2 <= k <= m, thus you need NOT check. (4%)
  */
  public static double getKthTerm(int k) {
    int sign = (k%2==0) ? -1 : 1;
    
    System.out.println( (sign==-1 ? "-" : "+") + "1/" + (2*k - 1) );
    return (double) sign / (2 * k - 1);
  }
  
  /*
  g) Print the series by calling getKthTerm(int k) with the cumulated sum of terms up to m.
    Store an estimated value of π into variable pi using LHS of Equation 1. (5%)
  */
  public static void main( String[] args) {
    byte m;
    double pi;
  
    Scanner key = new Scanner( System.in );
    System.out.println("Input m:");
    m = (byte) key.nextInt();
    if (m >= 1 && m < 30) System.out.println("OK");
    else System.out.println("XX");
    // The lines above are not included in this question, just for compilation purposes.
    
    System.out.println("LHS = RHS Series = 1"); // Given k = 1 term
    double ans = 0;
    for (int counter = 2; counter <= m; counter++)
      ans += getKthTerm(counter);
    pi = 4 * ans;
  }
  /*
  h) Write down a Java double-type literal with value 2468 in normalzied exponential notation. (1%)
    double value = 2.468e3;
  
  i) What is the type and value of (byte) Math.floor(-8.49e0)? (2%)
    Type: byte
    Value: -9
  */
}

