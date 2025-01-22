package stego;

import java.awt.image.BufferedImage;
import java.io.File;
import java.util.Scanner;
import javax.swing.ImageIcon;
import javax.swing.JOptionPane;

public class PGM {
  // instance fields
  private final String imageName;
  private int width, height;
  private int maxValue;
  private int[][] image;

  /** Default constructor for creating a simple checker PGM image of 2 x 3 */
  public PGM() {
    imageName = "Simple";
    width = 2;
    height = 3;
    maxValue = 255;                   // value for white in default/given file
    image = new int[height][width];   // note: height as row, width as column
    image[0][0] = image[1][1] = 255;  // white dots
    image[0][1] = image[2][0] = 127;  // gray dots
    image[1][0] = image[2][1] = 0;    // black dots
  }

  /** Constructor for creating an "mid-gray" PGM image of w x h 
   * @param name image name in String
   * @param w width in int
   * @param h height in int
  * // All pixels shall carry value of 127 */
  public PGM(String name, int w, int h) {
    imageName = name;
    width = w;
    height = h;
    maxValue = 255;
    image = new int[height][width];

    for (int row = 0; row < height; row++) 
      for (int col = 0; col < width; col++) 
        image[row][col] = 127;    
  }
  
  /** Constructor for creating an "gray stipe" PGM image of w x h
  * // pixels carry values of full range of 0 to 255 
  */
  public PGM(String name, int x) {
    imageName = name;
    width = 16;
    height = x;
    maxValue = 255;
    image = new int[height][width];

    for (int row = 0; row < height; row++) 
      for (int col = 0; col < width; col++) 
        image[row][col] = row;    
  }  

  /** Constructor for reading a PGM image file */
  public PGM(String filename) {
    this.imageName = filename;
    read(filename);
  }

  /**
   * Get the width of the image
   * @return image width in int
   */
  public int getWidth() { return width; }

  /** Get the height of the image
   * @return image height in int
   */
  public int getHeight() { return height; }

  /** Get the image 2D array
   * @return image 2D array in int[][]
   */
  public int[][] getImage() { 
      int[][] image = new int[height][width];
      for(int i = 0; i<height; i++) {
          System.arraycopy(this.image[i], 0, image[i], 0, width);
      }      
      return image; 
  }
  
  /** Show image on screen
   */
  public void showImage() {
    if (getHeight() <= 0 || getWidth() <= 0 || image == null) {
      JOptionPane.showConfirmDialog(null, "Width x Height = " + getWidth() + "x" + getHeight(), imageName + " corrupted!", JOptionPane.CLOSED_OPTION, JOptionPane.ERROR_MESSAGE, null);
      return;
    }

    BufferedImage img = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_BYTE_GRAY);

    int grayLevel, gray; 
            
    for (int row = 0; row < getHeight(); row++) {
      for (int col = 0; col < getWidth(); col++) {        
        grayLevel = image[row][col];
        gray = (grayLevel << 16) + (grayLevel << 8) + grayLevel; 
        img.setRGB(col, row, gray);
      }
    }

    JOptionPane.showConfirmDialog(null, "Width x Height = " + getWidth() + "x" + getHeight(), imageName, JOptionPane.CLOSED_OPTION, JOptionPane.INFORMATION_MESSAGE, new ImageIcon(img));
  }
  
  /** read a PGM file
   * @param filename is the PGM filename in String
   * @return true after finishing the action
   */
  public boolean read(String filename) {
  
    try {
      File f = new File(filename);
      Scanner reader = new Scanner(f);
      String header = reader.nextLine();
      if (header == null || header.length() < 2 || header.charAt(0) != 'P' || header.charAt(1) != '2') {
        throw new Exception("Wrong PGM header!");
      }

      do { // skip lines (if any) start with '#'
        header = reader.nextLine();
      } while (header.charAt(0) == '#');

      Scanner readStr = new Scanner(header);  // get w, h from last line scanned instead of file
      width = readStr.nextInt();
      height = readStr.nextInt();
      maxValue = reader.nextInt();  // get the rest from file

      System.out.println("Reading PGM image of size " + width + "x" + height);

      image = new int[height][width];

      for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
          int p = reader.nextInt();
          if (p > maxValue) {
            throw new Exception("Pixel value " + p + " on row " + row + ", col " + col + " out of range!");
          }

          image[row][col] = p;
        }
      }
    } catch (Exception e) {
      System.err.println(e);
      image = null;
      width = -1;
      height = -1;
      return false;
      // End of your code
    }

    return true;
  }
  
}
