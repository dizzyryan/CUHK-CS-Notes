
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.logging.Level;
import java.util.logging.Logger;

// let's complete the class SquareMatrix here
class SquareMatrix extends Matrix {
  // define your fields, constructor and more instance methods here
  // YOUR CODE HERE

  int dimension;
  
  public SquareMatrix(int dms, String fileName) {
    super(dms, dms);
    this.dimension = dms;
    data = new double[dms][dms];
    File i = new File(fileName);
    try {
      Scanner f = new Scanner(i);
      for (int c1 = 0; c1 < dms; c1++) {
        for (int c2 = 0; c2 < dms; c2++) {
          data[c1][c2] = f.nextDouble();
        }
      }
    } catch (FileNotFoundException ex) {
      Logger.getLogger(SquareMatrix.class.getName()).log(Level.SEVERE, null, ex);
    }
  }

  public boolean isDiagonal() {
    for (int c1 = 0; c1 < dimension; c1++) {
      for (int c2 = 0; c2 < dimension; c2++) {
        if (c1 != c2 && data[c1][c2] != 0) {
          return false;
        }
      }
    }
    return true;
  }
}

// Given the class Matrix here
class Matrix {
  // fields, constructor and more instance methods

  protected int rowM, colN;
  protected double[][] data;

  public Matrix(int m, int n) {
    this.rowM = m;
    this.colN = n;
    this.data = new double[m][n];
  }

  // instance method toString() 
  public String toString() {
    StringBuilder str = new StringBuilder();

    for (int i = 0; i < rowM; i++) {
      for (int j = 0; j < colN; j++) {
        str.append(String.format("%10.2f ", data[i][j]));
      }
      str.append("\n");
    }
    return str.toString();
  }
}

class Lab09Ex01 {

  public static void main(String[] args) {

    // Do not touch the following lines
    // 
    Scanner keyin = new Scanner(System.in);
    int m;

    System.out.println("m?");
    m = keyin.nextInt();

    SquareMatrix mat;
    mat = new SquareMatrix(m, "matrix" + m + ".txt");
    System.out.print(mat);
    System.out.println(mat.isDiagonal());

    // The End 
  }
}
