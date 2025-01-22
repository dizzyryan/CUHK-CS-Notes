
import java.util.*;             // for using Scanner
import java.io.*;		// for opening File

class Lab06Ex02 {

  private static String numFileName = "numbers.txt";

  // Start coding here
  public static void printLine(int x, int y) throws FileNotFoundException {
    File inputFile = new File("numbers.txt");
    Scanner fileScanner = new Scanner(inputFile);
    int counter, dummy, counter2;
    int repeat, value;
    for (counter = 1; counter <= y; counter++) {
      while (counter < x) {
        dummy = fileScanner.nextInt();
        dummy = fileScanner.nextInt();
        counter++;
      }
      repeat = fileScanner.nextInt();
      value = fileScanner.nextInt();
      for (counter2 = 0; counter2 < repeat; counter2++) {
        System.out.print(value + " ");
      }
      System.out.println();
    }
  }

  public static void main(String[] args) throws FileNotFoundException {
    int x, y;
    Scanner keyboard = new Scanner(System.in);
    System.out.print("Start? ");
    x = keyboard.nextInt();
    System.out.print("End? ");
    y = keyboard.nextInt();
    printLine(x, y);
  }
}
