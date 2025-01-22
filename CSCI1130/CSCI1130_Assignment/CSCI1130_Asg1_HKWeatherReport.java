package hkweatherreport;

import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.net.URI;
import javax.imageio.ImageIO;
import javax.swing.*;

/**
 * HKWeatherReport Java with Ant - Java application.
 * @author Michael FUNG
 * @version 1.0
 */

public class HKWeatherReport implements ActionListener {
    
    private static final int SID = 1155123456; // Student ID
    
    private static final String HKO_BASE = "https://www.hko.gov.hk/";
    private static final String HK_MAP_URL = HKO_BASE + "images/hko_map_terrain_v2.png";
    private static final String WREPORT_URL = HKO_BASE + "textonly/v2/forecast/englishwx2.htm";
    
    private final JTextPane reportPane;
    private final JButton button;
    
    /**
     * Constructor sets up a JFrame window with its components and properties.
     * @throws Exception
     */
    
    public HKWeatherReport() throws Exception {
        Image hkMap = ImageIO.read(new URI(HK_MAP_URL).toURL());
        ImageIcon hkMapIcon = new ImageIcon(hkMap);
        
        JFrame window;
        window = new JFrame("HK Weather (source: HK Observatory)");
        window.setLayout(new GridLayout(1, 2));
        
        button = new JButton();
        button.setIcon(hkMapIcon);
        button.setToolTipText("Click to update!");
        JLabel infoBox = new JLabel("My SID is " + SID);
        JPanel leftPanel = new JPanel();
        leftPanel.add(button);
        leftPanel.add(infoBox);
        window.add(leftPanel, 0, 0);
        
        reportPane = new JTextPane();
        reportPane.setPage(WREPORT_URL);
        JScrollPane scrollPane = new JScrollPane(reportPane);
        window.add(scrollPane, 0, 1);
        
        window.setSize(1000, 600);
        window.setVisible(true);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    
    /** 
     * actionPerformed() is the only method defined in the ActionListener interface.
     * The GUI thread will invoke method actionPerformed() on button click events.
     * @param eventObject
     */
    
    @Override
    public void actionPerformed(ActionEvent eventObject){
        System.out.println("Updating...");
        try {
            double probability = Math.random();
            double threshold = 0.4;
            // depends on the drawn random value, perform either operation:
            if (probability < threshold)
            {
                System.out.println("P(load error) = " + threshold + " > " + probability);
                reportPane.setPage("blah blah blah"); // this will trigger an exceotion
            }
            else
            {
                System.out.println("P(load error) = " + threshold + " < " + probability);
                reportPane.setPage(WREPORT_URL);
            }
        } catch (IOException ex){
            String errorMessage = "<html><font color=\"RED\">UNLUCKILY, ";
            errorMessage += "unable to update weather report from:" + "<p></font></html>";
            JOptionPane.showMessageDialog(null, errorMessage + WREPORT_URL);
        }
    }
    
    /**
     * Activate the Update button.
     * "this" object serves as the ActionListener of the button.
     * HKWeatherReport implements ActionListener.
     */
    
    private void activateUpdateButton() {
        button.addActionListener(this);
    }
    
    /**
     * main() method is the starting point of a standalone Java application
     * @param args the command line arguments
     * @throws java.lang.Exception
     */
    
    public static void main(String[] args) throws Exception {
        HKWeatherReport obj = new HKWeatherReport();
        System.out.println("Running: " + obj.getClass().getSimpleName());
        // the GUI Application will continue in another thread
        obj.activateUpdateButton();
        System.out.println("Enjoy!");
        // main() method thread will stop here
    }
} // end of class