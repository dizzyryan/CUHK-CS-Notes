package cli;

import java.sql.*;
import java.util.*;

import db.Database;
import db.user_op.SalespersonOp;

public class SalespersonCLI implements CLIInterface {
    private Database database;
    private Scanner scanner;

    public SalespersonCLI(Database database, Scanner scanner) {
        this.database = database;
        this.scanner = scanner;
    }

    private SalespersonOp salespersonOp;

    public void startCLI() {
        salespersonOp = new SalespersonOp(database.connection);
        while (true) {
            printSalespersonMenu();
            int choice;
            try {
                choice = scanner.nextInt();
                scanner.nextLine();
            } catch (InputMismatchException e) {
                System.out.println("[Selection Error] Please choose a valid option.\n");
                continue;
            }
            System.out.println();
            switch (choice) {
                case 1:
                    searchForParts();
                    break;
                case 2:
                    sellAPart();
                    break;
                case 3:
                    return;
                default:
                    System.out.println("[Selection Error] Please choose a valid option.\n");
            }
        }
    }

    private void printSalespersonMenu() {
        System.out.println("-----Operations for salesperson menu-----");
        System.out.println("What kinds of operation would you like to perform?");
        System.out.println("1. Search for parts");
        System.out.println("2. Sell a part");
        System.out.println("3. Return to the main menu");
        System.out.printf("Enter your choice: ");
    }

    private void searchForParts() {
        System.out.println("Choose the Search criterion: ");
        System.out.println("1. Part name");
        System.out.println("2. Manufacturer Name");
        System.out.printf("Choose the Search criterion: ");
        int tmp = scanner.nextInt();
        String searchCriterion = tmp == 1 ? "p_name" : "m_name";
        scanner.nextLine();
        System.out.println();
        System.out.printf("Type in the Search Keyword: ");
        String keyword = scanner.nextLine();
        System.out.println();
        System.out.println("Choose ordering:");
        System.out.println("1. By price, ascending order");
        System.out.println("2. By price, descending order");
        System.out.printf("Choose ordering: ");
        tmp = scanner.nextInt();
        String ordering = tmp == 1 ? "ASC" : "DESC";
        System.out.println();
        try {
            salespersonOp.searchForParts(searchCriterion, keyword, ordering);
            System.out.println("End of Query\n");
        } catch (SQLException e) {
            System.out.println("[Error] " + e.getMessage() + "\n");
        }
    }

    private void sellAPart() {
        System.out.printf("Enter the Part ID: ");
        int partID = scanner.nextInt();
        scanner.nextLine();
        System.out.printf("Enter the Salesperson ID: ");
        int salespersonID = scanner.nextInt();
        scanner.nextLine();
        try {
            salespersonOp.sellAPart(partID, salespersonID);
        } catch (SQLException e) {
            System.out.println("[Error] " + e.getMessage() + "\n");
        }
    }
}