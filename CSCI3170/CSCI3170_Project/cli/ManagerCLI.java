package cli;

import java.sql.*;
import java.util.*;

import db.Database;
import db.user_op.ManagerOp;

public class ManagerCLI implements CLIInterface {
    private Database database;
    private Scanner scanner;

    public ManagerCLI(Database database, Scanner scanner) {
        this.database = database;
        this.scanner = scanner;
    }

    private ManagerOp managerOp;

    public void startCLI() {
        managerOp = new ManagerOp(database.connection);
        while (true) {
            printManagerMenu();
            int choice;
            try {
                choice = scanner.nextInt();
                scanner.nextLine();
            } catch (InputMismatchException e) {
                scanner.nextLine();
                System.out.println("[Error] Please choose a valid option.\n");
                continue;
            }
            System.out.println();
            switch (choice) {
                case 1:
                    listAllSalespersons();
                    break;
                case 2:
                    countSalesRecord();
                    break;
                case 3:
                    showTotalSalesValue();
                    break;
                case 4:
                    System.out.println("Not available.\n");
                    continue;
                case 5:
                    return;
                default:
                    System.out.println("[Error] Please choose a valid option.\n");
            }
        }
    }

    private void printManagerMenu() {
        System.out.println("-----Operations for manager menu-----");
        System.out.println("What kinds of operation would you like to perform?");
        System.out.println("1. List all salespersons");
        System.out.println(
                "2. Count the no. of sales record of each salesperson under a specific range on years of experience");
        System.out.println("3. Show the total sales value of each manufacturer");
        System.out.println("4. Show the N most popular part");
        System.out.println("5. Return to the main menu");
        System.out.printf("Enter your choice: ");
    }

    private void listAllSalespersons() {
        int tmp;
        System.out.println("Choose ordering:");
        System.out.println("1. By ascending order");
        System.out.println("2. By descending order");
        System.out.printf("Choose the list ordering: ");
        try {
            tmp = scanner.nextInt();
        } catch (InputMismatchException e) {
            scanner.nextLine();
            System.out.println("[Error] Please choose a valid option.\n");
            return;
        }
        scanner.nextLine();
        System.out.println();
        String ordering = tmp == 1 ? "ASC" : "DESC";
        try {
            managerOp.listAllSalespersons(ordering);
        } catch (SQLException e) {
            System.out.println("[Error] " + e.getMessage() + "\n");
        }
    }

    private void countSalesRecord() {
        int lowerBound, upperBound;
        System.out.printf("Type in the lower bound for years of experience: ");
        try {
            lowerBound = scanner.nextInt();
        } catch (InputMismatchException e) {
            scanner.nextLine();
            System.out.println("[Error] Please enter a valid lower bound.\n");
            return;
        }
        scanner.nextLine();
        System.out.printf("Type in the upper bound for years of experience: ");
        try {
            upperBound = scanner.nextInt();
        } catch (InputMismatchException e) {
            scanner.nextLine();
            System.out.println("[Error] Please enter a valid upper bound.\n");
            return;
        }
        scanner.nextLine();
        System.out.println();
        try {
            managerOp.countSalesRecord(lowerBound, upperBound);
            System.out.println("End of Query\n");
        } catch (SQLException e) {
            System.out.println("[Error] " + e.getMessage() + "\n");
        }
    }

    private void showTotalSalesValue() {
        try {
            managerOp.showTotalSalesValue();
            System.out.println("End of Query\n");
        } catch (SQLException e) {
            System.out.println("[Error] " + e.getMessage() + "\n");
        }
    }
}
