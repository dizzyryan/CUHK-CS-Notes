package stego;

import java.util.*;
import java.io.*;

public class Stego {

  /**
   * convert an array of bits to a String DO NOT MODIFY the method signature
   *
   * @param the bit stream in a byte array
   * @return secret message in String
   */
  private String bitArrayToString(byte[] bitArr) {
    // Your code here

    // use StringBuilder to build a string to store the hidden message
    StringBuilder hiddenMsg = new StringBuilder("");
    // declare counters to be used in nested loop
    int inCounter, outCounter;
    int decimalValue = 0, power = 0;

    // there are total (bitArr.length / 8) characters
    for (outCounter = 0; outCounter < bitArr.length / 8; outCounter++) {
      // start from 0, 8, 16... and end at 7, 15, ...
      for (inCounter = outCounter * 8; inCounter <= (outCounter + 1) * 8 - 1; inCounter++) {
        // convert from binary value to decimal value
        decimalValue += bitArr[inCounter] * Math.pow(2, 7 - power);
        // use power for reduction
        power++;
      } // end of inner loop
      // once detected ASCII character, terminate the process
      if (decimalValue == 0) {
        break;
      }
      // appen the hidden message
      hiddenMsg.append((char) decimalValue);
      // clear power and decimal value
      power = 0;
      decimalValue = 0;
    } // end of outer loop

    // convert hidden message from StringBuilder to String
    String msgString = hiddenMsg.toString();
    // return the string
    return msgString;
    // End of your code 
  }

  /**
   * decode the stego image back a String, and prints to console DO NOT MODIFY
   * the method signature
   *
   * @param pgmImage the PGM image to be decoded
   */
  public void decode(PGM pgmImage) {
    // Your code here
    // get the height and width of the pgm image
    int height, width;
    height = pgmImage.getHeight();
    width = pgmImage.getWidth();
    // setup an array
    int arrLength = height * width;
    byte bitArr[] = new byte[arrLength];
    // copy the array of pgm file to originalImage (object reference)
    int originalImage[][] = pgmImage.getImage();
    // declare counters to be used in nested loop
    int counter1, counter2, counter3 = 0;
    
    System.out.println("Decoding a PGM image of size " + width + "x" + height);
    for (counter1 = 0; counter1 < height; counter1++) {
      for (counter2 = 0; counter2 < width; counter2++) {
        // find the LSB
        if (originalImage[counter1][counter2] % 2 == 0)
          bitArr[counter3] = 0;
        else
          bitArr[counter3] = 1;
        counter3++;
      } // end of inner loop
    } // end of outer loop

    // convert array to words and print to the console
    System.out.println(bitArrayToString(bitArr));
    // End of your code  
  }

  /**
   * main() method, starting point of the Java application.
   *
   * @param args the command line arguments
   */
  public static void main(String[] args) {
    String filename;

    // Create and display the first PGM image
    PGM pgmSimple;
    pgmSimple = new PGM();
    pgmSimple.showImage();

    // Create and display the second PGM image       
    PGM pgmDefault;
    pgmDefault = new PGM("MidGray", 40, 30);
    pgmDefault.showImage();

    // See how it shows when the filename goes wrong        
    filename = "WRONG_FILENAME.ppm";
    PGM pmgCorrupted;
    pmgCorrupted = new PGM(filename);
    pmgCorrupted.showImage();

    // Uncomment the following lines after the bitArrayToString method is implemented (for testing only)
    //Stego testStego = new Stego();
    //byte [] simpleBitArray = {0, 1, 0, 0, 0, 0, 0, 1}; // a value of 65 in binary format
    //System.out.println(testStego.bitArrayToString(simpleBitArray)); // prints "A" after correct implementation
    
    // Decode java's slogan from java_stego.pgm
    Stego javaStego = new Stego();
    
    PGM pgmJava;
    pgmJava = new PGM("java_stego.pgm");
    pgmJava.showImage();
    javaStego.decode(pgmJava);
    
    // you may decode the other provided stego PGM files for testing too
    // PGM pgmCamMan, pgmNoCamMan, pgmPeppers;
    // pgmCamMan = new PGM("cameraman_stego_with_message.pgm");
    // pgmCamMan.showImage();
    // javaStego.decode(pgmCamMan);
    // pgmNoCamMan = new PGM("cameraman_stego_without_message.pgm");
    // pgmNoCamMan.showImage();
    // javaStego.decode(pgmNoCamMan);
    // pgmPeppers = new PGM("peppers_stego.pgm");
    // pgmPeppers.showImage();
    // javaStego.decode(pgmPeppers);
    
    // terminate the process
    System.exit(0);
  }

}
