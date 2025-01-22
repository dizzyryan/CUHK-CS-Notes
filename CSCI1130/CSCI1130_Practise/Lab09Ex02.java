
import java.util.*;

class Lab09Ex02 {

  public static void main(String[] args) {
    int n;
    Scanner i = new Scanner(System.in);
    n = i.nextInt();
    int a[][] = new int[n][n];
    int num = 1;
    int top = 0, left = 0, right = n - 1, bottom = n - 1;
    while (top <= bottom && left <= right) {
      // top
      for (int counter = left; counter <= right; counter++) {
        a[top][counter] = num;
        num++;
      } top++;
      
      for (int counter = top; counter <= bottom; counter++) {
        a[counter][right] = num;
        num++;
      } right--;
      
      for (int counter = right; counter >= left; counter--) {
        a[bottom][counter] = num;
        num++;
      } bottom--;
      
      for (int counter = bottom; counter >= top; counter--) {
        a[counter][left] = num;
        num++;
      } left++;

    }

    for (int c1 = 0; c1 < n; c1++) {
      for (int c2 = 0; c2 < n; c2++) {
        System.out.print(a[c1][c2]);
        if(c2 != n - 1)
          System.out.print(" ");
      }
      System.out.println();
    }
  }
}
