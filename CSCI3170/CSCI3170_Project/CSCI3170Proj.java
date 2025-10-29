import java.sql.*;
import cli.*;
import db.*;

public class CSCI3170Proj {
    public static void main(String[] args) {
        Database database = new Database();
        try {
            database.connect();
        } catch (ClassNotFoundException e) {
            System.out.println("[CONNECTION ERROR] Java MySQL DB Driver not found!");
            System.out.println("[CONNECTION ERROR] Please connect to CUHK CSE VPN.");
            System.exit(0);
        } catch (SQLException e) {
            System.out.println("[SQL ERROR] " + e.getMessage());
            System.exit(0);
        }

        System.out.println("Welcome to sales system!");
        System.out.println();

        HomeCLI cli = new HomeCLI(database);
        cli.startCLI();
    }
}