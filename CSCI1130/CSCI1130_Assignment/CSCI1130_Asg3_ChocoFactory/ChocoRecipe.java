package chocofactory;

import java.util.Random;

public class ChocoRecipe {

  // Do not MODIFY the two given private fields
  private String name = "";
  private int cocoaPercent;
  
  // Define more date fields as needed
  
  // Do not MODIFY the default constructor which is for the example run
  ChocoRecipe() {
      this.name = "100% Noir";
      this.cocoaPercent = 100;
  }
  
  // STUDENT WORK HERE to modify and add related methods
  
  // Second constructor for classic recipe
  ChocoRecipe(String name, int cocoaPercent){
      this.name = cocoaPercent + "% " + name;
      this.cocoaPercent = cocoaPercent;
  }
  
  // Third constructor for non-classic recipe
  ChocoRecipe(String name_suffix){
    // if candied, get random cocoa percent from 40%~54%
    if (name_suffix == "Candied"){
      this.cocoaPercent = genRansdomCocoaPercent(40, 54);
    }
    // if delish, get random cocoa percent from 59%~69%
    else if (name_suffix == "Delish"){
      this.cocoaPercent = genRansdomCocoaPercent(55, 69);
    }
    // combine cocoa percent and the name 
    this.name = cocoaPercent + "% " + name_suffix;
  }
  
  // create random coco percentage
  private int genRansdomCocoaPercent(int a, int b){
    cocoaPercent = (int) (Math.random() * (b-a) + a);
    return cocoaPercent;
  }
  
  // Do not MODIFY the method signature which is for CoffeeMaker to call
  public String getName() {
    return name;  // TODO: update the method body as the value returned is Hardcoded now
  }
  
  // Do not MODIFY the method signature which is for CoffeeMaker to call
  public int getCocoaPercent() {
    return cocoaPercent;  // TODO: update the method body as the value returned is Hardcoded now
  }

  // Do not MODIFY the method signature which is for CoffeeMaker to call
  public void printToConsole() {
    String type = "";
    if (cocoaPercent == 100 || cocoaPercent == 70){
      type = "classic";
    }
    else if (cocoaPercent <= 54 && cocoaPercent >= 40)
      type = "candied";
    else if (cocoaPercent <= 69 && cocoaPercent >= 55)
      type = "delish";
    
    System.out.println("This " + type + " recipe has " + cocoaPercent + "% cocoa.");   // TODO: update the method body as needed
  }

  // STUDENT may define extra helper methods here
}
