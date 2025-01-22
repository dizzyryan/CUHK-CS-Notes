package dataprocessor;

import java.io.*;

/**
 *
 * @author ryanc
 */
public class EnergyUseRecord {
  
  // private instance fields
  private int year;
  private int residential;
  private int commercial;
  private int industrial;
  private int transport;

  // private class fields (cumulative)
  private static int yearCount = 0;
  private static int residentialCumulative = 0;
  private static int commercialCumulative = 0;
  private static int industrialCumulative = 0;
  private static int transportCumulative = 0;
  
  // constructor to update class fields and instance fields
  public EnergyUseRecord(int y, int r, int c, int i, int t){
    year = y;
    // update year count
    yearCount += 1;
    
    residential = r;
    residentialCumulative += r;
    
    commercial = c;
    commercialCumulative += c;
    
    industrial = i;
    industrialCumulative += i;
    
    transport = t;
    transportCumulative += t;
  }
  
  // get current year
  public int getYear(){
    return this.year;
  }
  
  // get toatal annual energy use
  public int getAnnualEnergyUse(){
    int annualEnergyUse = this.residential + this.commercial + this.industrial + this.transport;
    return annualEnergyUse;
  }
  
  // making strings

  @Override
  public String toString(){
    return String.format("Year %d - Res: %7d TJ  Com: %7d TJ  Ind: %7d TJ  Trp: %7d TJ", year, residential, commercial, industrial, transport);
  }
  
  // reset all cumulative values to zero
  public static void resetCumulation(){
    yearCount = 0;
    residentialCumulative = 0;
    commercialCumulative = 0;
    industrialCumulative = 0;
    transportCumulative = 0;
  }
  
  // print the summary for all data
  public static void printSummary(PrintStream ps){
    ps.printf("There are %d records:\n", yearCount);
    // if yearCount is zero
    if (yearCount == 0){
      ps.println("Summary not available");
    }
    // print average vaklues
    else {
      ps.printf("average(residential) = %7d TJ\n", residentialCumulative/yearCount);
      ps.printf("average(commercial)  = %7d TJ\n", commercialCumulative/yearCount);
      ps.printf("average(industrial)  = %7d TJ\n", industrialCumulative/yearCount);
      ps.printf("average(transport)   = %7d TJ\n", transportCumulative/yearCount);
    }
  }
  
  /**
   * @param args the command line arguments
   */
  public static void main(String[] args) {
    EnergyUseRecord record1997 = new EnergyUseRecord(1997, 1000, 2000, 3000, 4000);
    System.out.println(record1997.toString()); // invoke toString() method
    
    EnergyUseRecord record2000 = new EnergyUseRecord(2000, 5000, 6000, 7000, 8000);
    System.out.println(record2000); // invoke toString() method implicitly
    
    System.out.println("Year " + record2000.getYear() + " used " + record2000.getAnnualEnergyUse() + " TJ");
    EnergyUseRecord.printSummary(System.out);
    EnergyUseRecord.resetCumulation();
    
    EnergyUseRecord.printSummary(System.out);
    System.out.println( new EnergyUseRecord(2024, 5999, 6999, 7999, 8999) );
    EnergyUseRecord.printSummary(System.out);
    EnergyUseRecord.resetCumulation();
  }
}