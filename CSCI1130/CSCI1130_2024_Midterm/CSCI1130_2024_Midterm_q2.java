package csci1130_2024_midterm;

/**
 * Question 2 (22%)
 * 
 * Define a class Employee that has the following members:
 * - Two private instance data fields id and monthlySalary, both of type int. (3%)
 * - A constructor that takes two int-type parameters idGiven and annualSalary for
 *   initializing the corresponding fields. Take monthly salary = round(annual salary / 12). (7%)
 * - A public instance method getID() returns the id. (3%)
 * - A public instance method getMpfBoss() that calculates and returns a double type
 *   value of the Boss's mandatory contribution based on monthlySalary. (4%)
 * - A public instance method getMpfEmployee() that calculates and returns a double
 *   type value of the Employee's mandatory contribution based on monthlySalary. (5%)
 */

// Answer:

class Employee {
  private int id, monthlySalary;
  
  public Employee (int idGiven, int annualSalary) {
    id = idGiven;
    monthlySalary = (int) Math.round(annualSalary / 12.0);
  }
  
  public int getID() {
    return id;
  }
  
  public double getMpfBoss() {
    if (monthlySalary > 30000) return 1500;
    return monthlySalary * 0.05;
  }
  
  public double getMpfEmployee() {
    if (monthlySalary < 7100) return 0;
    if (monthlySalary > 30000) return 1500;
    return monthlySalary * 0.05;
  }
} // end of class
