
import java.util.*;

class Lab07Ex01 {

  public static void main(String[] args) {
    Scanner key = new Scanner(System.in);
    String str = key.next();
    boolean isP = true;
    int len = str.length();
    int temp = len;
    for (int counter = 0; counter < (len / 2); counter++) {
      if (str.charAt(counter) == str.charAt(temp - 1)) {
        temp--;
      } 
      else {
        isP = false;
        break;
      }
    }

    if (isP == true) {
      System.out.println("Yes");
    } else {
      System.out.println(
              "No");
    }
  }
}
