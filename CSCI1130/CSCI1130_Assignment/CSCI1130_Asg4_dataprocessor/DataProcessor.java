package dataprocessor;

import java.io.*;
import java.util.*;

/**
 *
 * @author ryanc
 */
public class DataProcessor {
  
  public int y, r, c, i, t, dummy;
  
  // print file to text file
  public static void printFile() throws Exception{
    // redirection
    PrintStream printFile = new PrintStream("summary.txt");
    EnergyUseRecord.printSummary(printFile);
  }
  
  // process data in the given file
  public DataProcessor() throws Exception{
    // read from "table07.csv"
    File fileObj = new File("table07.csv");
    Scanner reader = new Scanner(fileObj);
    // read comma-separated values
    reader.useDelimiter(",");
    // read and print the whole header line
    String header = reader.nextLine();   
    // print out header
    System.out.println("Header: " + header);
    // create new object under EnergyUseRecord
    EnergyUseRecord newObj = null;
    // use while loop to read all lines in the file
    while (reader.hasNextLine()) {
      y = reader.nextInt(); // read year
      r = reader.nextInt(); // read residential
      dummy = reader.nextInt(); // discard value
      c = reader.nextInt(); // read commercial
      dummy = reader.nextInt();
      i = reader.nextInt(); // read industrial
      dummy = reader.nextInt();
      t = reader.nextInt(); // read transport
      reader.nextLine(); // discard the rest of the line
      // read and store data into new EnergyUseRecord objects
      newObj = new EnergyUseRecord(y, r, c, i, t);
      // print the record object
      System.out.println(newObj.toString());
      // print the year and annual energy use
      System.out.println("Year " + newObj.getYear() + " used " + newObj.getAnnualEnergyUse() + " TJ");
    }
  }
  
  /**
   * @param args the command line arguments
   */
  public static void main(String[] args) // NO throws clause
  {
    // try-catch ALL kinds of Exception, with the remedial action
    try{
      // new DataProcessor object
      DataProcessor record = new DataProcessor();
    }
    catch(Exception Exception){
      // printing "Error processing data!" to System.err
      System.err.print("Error processing data!");
    }
    // printSummary to console
    EnergyUseRecord.printSummary(System.out);
    // printSummary to file "output.txt"
    try{
      printFile();
    }
    catch(Exception Exception){
      // printing "Error processing data!" to System.err
      System.err.print("Error processing data!");
    }
    // terminate the app on all cases at the end
    System.exit(0);
  }
}