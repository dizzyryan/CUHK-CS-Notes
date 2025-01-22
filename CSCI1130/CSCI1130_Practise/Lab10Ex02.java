
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

// Please implement all TODOs in the provided code skeleton
class Lab10Ex02 {

  public static void main(String[] args) {
    Scanner keyInput = new Scanner(System.in);
    String filename = keyInput.nextLine();

    Scanner fileInput = null;
    String lineData = "";

    // open file
    try {
      fileInput = new Scanner(new File(filename));
    } catch (FileNotFoundException ex) {
      System.out.println("File not found!");
      System.exit(1);
    }

    while (/* TODO implement proper loop condition*/fileInput.hasNextLine() == true) {
      // TODO read a line of log
      lineData = null;
      lineData = fileInput.nextLine();
      String[] log = lineData.split(" ");
      boolean valid = (log[0].length() == 10);
      if (/* TODO judge validity of a line */valid == true) {
        // valid line

        // TODO get name entry. Assume no space in name.
        String name = log[log.length - 1];
        // TODO 1. filter out special case (1)
        if (name.charAt(0) == '.') {
          continue;
        }
        // TODO 2. separately considers file and directory
        // TODO 3. for directory, deal with case (2)
        if (name.charAt(name.length() - 1) == '/') {
          System.out.println("dir: " + name.substring(0, name.length() - 1));
        }
        else {
          System.out.println("file: " + name);
        }

        // TODO 4. print out processed name
      }
    }
  }

}
