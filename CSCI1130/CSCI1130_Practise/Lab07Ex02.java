import java.util.*;

class Lab07Ex02 {
  
  public static String decode(StringBuilder rev){
    String hiddenStr = rev.toString();
    String decodeStr = "";
    int counter, len = hiddenStr.length();
    for (counter = 0; counter < len; counter++){
      if (Character.isLetter(hiddenStr.charAt(counter)) == true)
        decodeStr += hiddenStr.charAt(counter);
      else
        continue;
    }
    return decodeStr;
  }
  
  
  public static void main(String[] args){
    Scanner key = new Scanner( System.in );
    StringBuilder userIn = new StringBuilder(key.next());
    StringBuilder reverseStr = userIn.reverse();
    System.out.println(reverseStr);
    System.out.println(decode(reverseStr));
  }
}
