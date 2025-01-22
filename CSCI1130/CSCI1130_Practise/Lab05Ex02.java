import java.util.Scanner;

class Lab05Ex02 {
  public static void main(String[] args) {

    // define guess = 0
    int guess = 0;
    Scanner s = new Scanner(System.in);

    // while guess is not 7
    while (guess != 7){
      // print "Guess my age? " and ask user for integer and assign it to guess
      System.out.print("Guess my age? ");
      guess = s.nextInt();
    }// end of while

    // print "You got it!"
    System.out.println("You got it!");
  }
}