
import java.util.Scanner;
// let's complete the class Fraction here

class Fraction {
  // define your fields, constructor and more instance methods here
  // YOUR CODE HERE

  public int a;  // numerator
  public int b;  // denominator

  public Fraction(int num, int den) {
    a = num;
    b = den;
    if (b % a == 0) {
      b = b / a;
      a = 1;
    }
  }

  public String printString() {
    return a + "/" + b;
  }

  public Fraction multiplyBy(Fraction obj) {
    this.a *= obj.a;
    this.b *= obj.b;
    return simplify(new Fraction(this.a, this.b));
  }

  private Fraction simplify(Fraction obj) {
    int num, den;
    num = obj.a;  // 2
    den = obj.b;  // 6
    if (den % num == 0) {
      den = den / num;
      num = 1;
    }
    return new Fraction(num, den);
  }
}

class Lab06Ex01 {

  public static void main(String[] args) {

    // Do not touch the following lines
    // 
    Scanner keyin = new Scanner(System.in);
    System.out.println("a? b? c? d?");
    int a, b, c, d;
    a = keyin.nextInt();
    b = keyin.nextInt();
    c = keyin.nextInt();
    d = keyin.nextInt();

    Fraction r, q, result;
    r = new Fraction(a, b);
    q = new Fraction(c, d);

    System.out.print(r.printString() + " x " + q.printString() + " = ");
    result = r.multiplyBy(q);
    System.out.println(result.printString());
    // The End 
  }
}
