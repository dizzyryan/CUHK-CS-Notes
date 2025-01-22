
import java.util.*;
import java.io.*;

class Lab08Ex01 {

  public static void main(String[] args) {
    Scanner keyIn = new Scanner(System.in);
    int n;
    System.out.println("Input n:");
    n = keyIn.nextInt();
    int[] dupIn = new int[n];
    System.out.printf("Input %d integers:\n", n);
    for (int counter = 0; counter < n; counter++) {
      dupIn[counter] = keyIn.nextInt();
      System.out.print(dupIn[counter] + " ");
    }
    System.out.println();
    for (int counter = 0; counter < n; counter++) {
      for (int counter2 = counter + 1; counter2 < n; counter2++){
        if (dupIn[counter2] == dupIn[counter]){
          dupIn[counter2] = -1;
        }
      }
      if (dupIn[counter] != -1)
        System.out.print(dupIn[counter] + " ");
    }
  }
}
