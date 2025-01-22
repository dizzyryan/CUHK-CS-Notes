
import java.util.Scanner;
import java.io.File;

// let's extend the class Matrix here
// Given the partially completed class Matrix here
class Matrix {
  // fields, constructor and more instance methods

  private int rowM, colN;
  private double[][] data;

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

  public void setData(double[][] data) {
    for (int i = 0; i < rowM; i++) {
      for (int j = 0; j < colN; j++) {
        this.data[i][j] = data[i][j];
      }
    }
  }

  // define more instance methods here
  // YOUR CODE HERE
  public double subMatrixSum(int rowS, int colS, int nRow, int nCol) {
    int c1, c2;
    double sum = 0;
    for (c1 = rowS; c1 <= nRow; c1++) {
      for (c2 = colS; c2 <= nCol; c2++) {
        sum += data[c1][c2];
      }
    }
    return sum;
  }
  
  public void printTranspose() {
    
    Matrix obj = new Matrix(colN, rowM);
    int x, y;
    if (colN == rowM) {
      for (x = 0; x < rowM; x++) {
        for (y = 0; y < colN; y++) {
          if (x == y) {
            obj.data[x][y] = data[x][y];
          }
          if (x != y) {
            obj.data[x][y] = data[y][x];
          }
        }
      }
    }
    if (colN != rowM) {
      for (x = 0; x < colN; x++) {
        for (y = 0; y < rowM; y++) {
          if (x == 0 && y == 0)
            obj.data[x][y] = data[x][y];
          obj.data[x][y] = data[y][x];
        }
      }
    }
    System.out.print(obj.toString());
  }

}

class Lab10Ex01 {

  public static void main(String[] args) {

    // Do not touch the following lines
    // 
    Scanner keyin = new Scanner(System.in);
    int m, n;
    System.out.println("m? n?");
    m = keyin.nextInt();
    n = keyin.nextInt();
    double[][] data = new double[m][n];
    System.out.println("Enter " + m * n + " elements");
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        data[i][j] = keyin.nextDouble();
      }
    }
    Matrix mat;
    mat = new Matrix(m, n);
    mat.setData(data);
    
    System.out.println(mat.subMatrixSum(0, 0, m - 2, n - 2));
    mat.printTranspose();

    // The End 
  }
}

/*
class Matrix {
    // fields, constructor and more instance methods
    private     int rowM, colN;
    private double[][] data;

    public Matrix(int m, int n) {
        this.rowM = m;
        this.colN = n;
        this.data = new double[m][n];
    }

    // instance method toString() 
    public String toString() {
        StringBuilder str = new StringBuilder();

        for(int i=0; i<rowM; i++) {
            for(int j=0; j<colN; j++) 
                str.append(String.format("%10.2f ", data[i][j]));
            str.append("\n");
        }
        return str.toString();
    }

    public void setData(double[][] data) {
        for(int i=0; i<rowM; i++) 
            for(int j=0; j<colN; j++) 
	        this.data[i][j] = data[i][j];
    }

    // define more instance methods here
    // YOUR CODE HERE


}

class Lab10Ex01 {
  public static void main(String[] args) {
      
    // Do not touch the following lines
    // 
    Scanner keyin = new Scanner(System.in);
    int m, n;
    double data = new double[m][n];

    System.out.println("m? n?");
    m = keyin.nextInt();
    n = keyin.nextInt();
    System.out.println("Enter "+m*n+" elements");
    for(int i=0; i<m; i++) 
        for(int j=0; j<n; j++) 
	    data[m][n] = keyin.nextDouble();

    Matrix mat;
    mat = new Matrix(m, n);
    mat.setData(data);
    System.out.print(mat.subMatrix(0,0,m-2,n-2));
    mat.printTranspose();

    // The End 
  }
}

*/