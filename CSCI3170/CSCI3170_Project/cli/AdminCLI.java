package cli;

import java.sql.*;
import java.util.*;

import db.Database;
import db.user_op.AdminOp;

public class AdminCLI implements CLIInterface {
    private Database database;
    private Scanner scanner;

    public AdminCLI(Database database, Scanner scanner) {
        this.database = database;
        this.scanner = scanner;
    }

    private AdminOp adminOp;

    public void startCLI() {
        adminOp = new AdminOp(database.connection);
        while (true) {
            printAdminMenu();
            int choice;
            try {
                choice = scanner.nextInt();
                scanner.nextLine();
            } catch (InputMismatchException e) {
                scanner.nextLine();
                System.out.println("[Selection Error] Please choose a valid option.\n");
                continue;
            }
            System.out.println();
            switch (choice) {
                case 1:
                    createAllTables();
                    break;
                case 2:
                    deleteAllTables();
                    break;
                case 3:
                    loadFromDatafile();
                    break;
                case 4:
                    showTableContent();
                    break;
                case 5:
                    return;
                default:
                    System.out.println("[Selection Error] Please choose a valid option.\n");
            }
        }
    }

    private void printAdminMenu() {
        System.out.println("-----Operations for administrator menu-----");
        System.out.println("What kinds of operation would you like to perform?");
        System.out.println("1. Create all tables");
        System.out.println("2. Delete all tables");
        System.out.println("3. Load from datafile");
        System.out.println("4. Show content of a table");
        System.out.println("5. Return to the main menu");
        System.out.printf("Enter your choice: ");
    }

    private void createAllTables() {
        try {
            System.out.printf("Processing...");
            adminOp.createAllTables();
            System.out.println("Done! Database is initialized!\n");
        } catch (SQLException e) {
            System.out.println();
            System.out.println("[Creation Error] " + e.getMessage());
        }
    }

    private void deleteAllTables() {
        try {
            System.out.printf("Processing...");
            adminOp.deleteAllTables();
            System.out.println("Done! Database is removed!\n");
        } catch (SQLException e) {
            System.out.println();
            System.out.println("[Deletion Error] " + e.getMessage());
        }
    }

    private void loadFromDatafile() {
        System.out.printf("Type in the Source Data Folder Path: ");
        String folderPath = scanner.nextLine().trim().toLowerCase();
        try {
            System.out.printf("Processing...");
            adminOp.loadFromDatafile(folderPath);
            System.out.println("Done! Data is inputted to the databse!\n");
        } catch (Exception e) {
            if (e instanceof SQLException) {
                System.out.println();
                System.out.println("[SQL Error] " + e.getMessage());
            } else {
                System.out.println();
                System.out.println("[Loading Error] " + e.getMessage() + "\n");
            }
        }
    }

    private void showTableContent() {
        System.out.printf("Which table would you like to show: ");
        String tableName = scanner.nextLine().replaceAll("\\s+", "").toLowerCase();
        try {
            adminOp.showTableContent(tableName);
        } catch (SQLException e) {
            System.out.println();
            System.out.println("[Show Error] " + e.getMessage());
        }
    }
}
