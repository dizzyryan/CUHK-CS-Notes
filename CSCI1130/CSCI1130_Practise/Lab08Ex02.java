
import java.util.Scanner;
// let's complete the class Matrix here

class Matrix {

  // define your fields, constructor and more instance methods here
  private int rowM, colN;
  double data[][];

  // YOUR CODE HERE
  Matrix(int m, int n) {
    this.rowM = m;
    this.colN = n;
    this.data = new double[m][n];
  }

  // method toString() shall return a String representation of the Matrix
  //   but the method itself prints nothing.
  //   Use format specifier "%10.2f" for each element without extra space.
  public String toString() {
    StringBuilder returnStr = new StringBuilder();
    for (int counterM = 0; counterM < rowM; counterM++) {
      for (int counterN = 0; counterN < colN; counterN++) {
        returnStr.append(String.format("%10.2f ", data[counterM][counterN]));
      }
      returnStr.append("\n");
    }
    return returnStr.toString();
  }

  public void add(double scalar) {
    for (int counterM = 0; counterM < rowM; counterM++) {
      for (int counterN = 0; counterN < colN; counterN++) {
        data[counterM][counterN] = scalar;
      }
    }
  }

}

class Lab08Ex02 {

  public static void main(String[] args) {

    // Do not touch the following lines
    // 
    Scanner keyin = new Scanner(System.in);
    int m, n;
    double a;

    System.out.println("m? n? a?");
    m = keyin.nextInt();
    n = keyin.nextInt();
    a = keyin.nextDouble();

    Matrix mat1;
    mat1 = new Matrix(m, n);
    mat1.add(a);
    System.out.println(mat1.toString());

    // The End 
  }
}
