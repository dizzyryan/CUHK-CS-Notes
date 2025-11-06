package db.user_op;

import java.sql.*;

public class ManagerOp {
    private Connection connection;

    private void printManagerHeader() {
        System.out.println("| ID | Name | Mobile Phone | Years of Experience |");
    }

    private void printSalesRecordHeader() {
        System.out.println("| ID | Name | Years of Experience | Number of Transaction |");
    }

    private void printTotalSalesValueHeader() {
        System.out.println("| Manufacturer ID | Manufacturer Name | Total Sales Value |");
    }

    public ManagerOp(Connection connection) {
        this.connection = connection;
    }

    public void listAllSalespersons(String ordering) throws SQLException {
        try {
            String sql = "SELECT sId, sName, sPhoneNumber, sExperience FROM salesperson ORDER BY sExperience "
                    + ordering;
            PreparedStatement pstmt = connection.prepareStatement(sql);
            ResultSet rs = pstmt.executeQuery();
            if (!rs.isBeforeFirst()) {
                System.out.println("No results found.");
                return;
            }
            printManagerHeader();
            while (rs.next()) {
                System.out.println("| " + rs.getString(1) + " | " + rs.getString(2) + " | " + rs.getString(3) + " | "
                        + rs.getString(4) + " | ");
            }
            System.out.println();
            pstmt.close();
            rs.close();
        } catch (SQLException e) {
            System.out.println("[Error] " + e.getMessage() + "\n");
        }
    }

    public void countSalesRecord(int lowerBound, int upperBound) throws SQLException {
        try {
            PreparedStatement pstmt = connection.prepareStatement(
                    "SELECT s.sId, s.sName, s.sExperience, COUNT(t.tId) AS no_transactions FROM salesperson s JOIN transaction t ON s.sId = t.sId  WHERE s.sExperience BETWEEN ? AND ? GROUP BY s.sId, s.sName, s.sExperience ORDER BY s.sId DESC");
            pstmt.setInt(1, lowerBound);
            pstmt.setInt(2, upperBound);
            ResultSet rs = pstmt.executeQuery();
            if (!rs.isBeforeFirst()) {
                System.out.println("No results found.");
                return;
            }
            System.out.println("Transaction Record:");
            printSalesRecordHeader();
            while (rs.next()) {
                System.out.println("| " + rs.getString(1) + " | " + rs.getString(2) + " | " + rs.getString(3) + " | "
                        + rs.getString(4) + " | ");
            }
            pstmt.close();
            rs.close();
        } catch (SQLException e) {
            System.out.println("[Error] " + e.getMessage() + "\n");
        }
    }

    public void showTotalSalesValue() throws SQLException {
        try {
            PreparedStatement pstmt = connection.prepareStatement(
                    "WITH PartSales AS ( SELECT p.pId, p.pPrice, p.mId, m.mName, COUNT(p.pId) AS no_sold FROM part p JOIN transaction t ON p.pId = t.pId JOIN manufacturer m ON m.mId = p.mId GROUP BY p.pId, p.pPrice, p.mId, m.mName ) SELECT s.mId, s.mName, SUM(s.pPrice * s.no_sold) AS price FROM PartSales s GROUP BY s.mId, s.mName ORDER BY price DESC");
            ResultSet rs = pstmt.executeQuery();
            if (!rs.isBeforeFirst()) {
                System.out.println("No results found.");
                return;
            }
            printTotalSalesValueHeader();
            while (rs.next()) {
                System.out.println("| " + rs.getString(1) + " | " + rs.getString(2) + " | " + rs.getString(3) + " | ");
            }
            pstmt.close();
            rs.close();
        } catch (SQLException e) {
            System.out.println("[Error] " + e.getMessage() + "\n");
        }
    }
}
