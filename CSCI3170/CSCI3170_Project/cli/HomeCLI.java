package cli;

import java.util.*;

import db.*;

public class HomeCLI implements CLIInterface {
    private Database database;
    private Scanner scanner;

    public HomeCLI(Database database) {
        this.database = database;
        this.scanner = new Scanner(System.in);
    }

    public void startCLI() {
        while (true) {
            printMainMenu();
            int choice;
            try {
                choice = scanner.nextInt();
                scanner.nextLine();
            } catch (InputMismatchException e) {
                System.out.println("[Selection Error] Please choose a valid option.\n");
                continue;
            }
            System.out.println();
            CLIInterface c = null;
            switch (choice) {
                case 1:
                    c = new AdminCLI(database, scanner);
                    break;
                case 2:
                    c = new SalespersonCLI(database, scanner);
                    break;
                // case 3:
                // c = new ManagerCLI(database, scanner);
                // break;
                case 4:
                    return;
                default:
                    System.out.println("[Selection Error] Please choose a valid option.\n");
            }
            if (c != null)
                c.startCLI();
        }
    }

    private void printMainMenu() {
        System.out.println("-----Main menu-----");
        System.out.println("What kinds of operation would you like to perform?");
        System.out.println("1. Operations for administrator");
        System.out.println("2. Operations for salesperson");
        System.out.println("3. Operations for manager");
        System.out.println("4. Exit this program");
        System.out.printf("Enter your choice: ");
    }
}