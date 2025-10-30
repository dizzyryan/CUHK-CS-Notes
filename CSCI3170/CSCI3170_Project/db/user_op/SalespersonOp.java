package db.user_op;

import java.sql.*;

public class SalespersonOp {
    private Connection connection;

    private void printTableHeader() {
        System.out.println("| ID | Name | Manufacturer | Category | Quantity | Warranty | Price |");
    }

    public SalespersonOp(Connection connection) {
        this.connection = connection;
    }

    public void searchForParts(String searchCriterion, String keyword, String ordering) throws SQLException {
        if (searchCriterion.equals("p_name")) {
            try {
                String sql = "SELECT p.p_id, p.p_name, m.m_name, c.c_name, p.p_quantity, p.p_warranty, p.p_price FROM part p JOIN manufacturer m ON p.m_id = m.m_id JOIN category c ON p.c_id = c.c_id WHERE LOWER(p.p_name) LIKE LOWER(?) ORDER BY p.p_price "
                        + ordering;
                PreparedStatement pstmt = connection.prepareStatement(sql);
                pstmt.setString(1, "%" + keyword + "%");
                ResultSet rs = pstmt.executeQuery();
                if (!rs.isBeforeFirst()) {
                    System.out.println("No results found.");
                    return;
                }
                printTableHeader();
                while (rs.next()) {
                    System.out
                            .println("| " + rs.getString(1) + " | " + rs.getString(2) + " | " + rs.getString(3) + " | "
                                    + rs.getString(4) + " | " + rs.getString(5) + " | " + rs.getString(6) + " | "
                                    + rs.getString(7) + " | ");
                }
            } catch (SQLException e) {
                System.out.println("[Error] " + e.getMessage() + "\n");
            }

        } else if (searchCriterion.equals("m_name")) {
            try {
                String sql = "SELECT p.p_id, p.p_name, m.m_name, c.c_name, p.p_quantity, p.p_warranty, p.p_price FROM part p JOIN manufacturer m ON p.m_id = m.m_id JOIN category c ON p.c_id = c.c_id WHERE LOWER(m.m_name) LIKE LOWER(?) ORDER BY p.p_price "
                        + ordering;
                PreparedStatement pstmt = connection.prepareStatement(sql);
                pstmt.setString(1, "%" + keyword + "%");
                ResultSet rs = pstmt.executeQuery();
                if (!rs.isBeforeFirst()) {
                    System.out.println("No results found.");
                    return;
                }
                printTableHeader();
                while (rs.next()) {
                    System.out
                            .println("| " + rs.getString(1) + " | " + rs.getString(2) + " | " + rs.getString(3) + " | "
                                    + rs.getString(4) + " | " + rs.getString(5) + " | " + rs.getString(6) + " | "
                                    + rs.getString(7) + " | ");
                }
            } catch (SQLException e) {
                System.out.println("[Error] " + e.getMessage() + "\n");
            }
        }
    }

    public void sellAPart(int partID, int salespersonID) throws SQLException {
        try {
            PreparedStatement pstmtQC = connection.prepareStatement("SELECT p_quantity FROM part WHERE p_id = ?");
            pstmtQC.setInt(1, partID);
            ResultSet rs = pstmtQC.executeQuery();
            if (!rs.isBeforeFirst()) {
                System.out.println("No results found.\n");
                return;
            }
            rs.next();
            int quantity = rs.getInt(1);
            if (quantity <= 0) {
                System.out.println("Out of stock.\n");
                return;
            } else {
                int t_id = 1;
                String sql = "SELECT NVL(MAX(t_id), 0) AS max_tid FROM transactionrecords";
                PreparedStatement pstmt = connection.prepareStatement(sql);
                ResultSet maxTID = pstmt.executeQuery();
                if (!maxTID.next()) {
                    t_id = 1;
                } else {
                    t_id = maxTID.getInt(1) + 1;
                }
                PreparedStatement[] pstmts = {
                        connection.prepareStatement(
                                "INSERT INTO transactionrecords (t_id, p_id, s_id, t_date) VALUES (?, ?, ?, TRUNC(CURRENT_DATE))"),
                        connection.prepareStatement(
                                "UPDATE part SET p_quantity = p_quantity - 1 WHERE p_id = ?"),
                };
                pstmts[0].setInt(1, t_id);
                pstmts[0].setInt(2, partID);
                pstmts[0].setInt(3, salespersonID);
                pstmts[1].setInt(1, partID);

                for (int i = 0; i < pstmts.length; i++) {
                    pstmts[i].executeUpdate();
                }

                PreparedStatement[] results = {
                        connection.prepareStatement(
                                "SELECT p_name FROM part WHERE p_id = " + partID),
                        connection.prepareStatement(
                                "SELECT p_quantity FROM part WHERE p_id = " + partID)
                };
                ResultSet rsName = results[0].executeQuery();
                rsName.next();
                String p_name = rsName.getString(1);
                ResultSet rsQty = results[1].executeQuery();
                rsQty.next();
                int p_quantity = rsQty.getInt(1);
                System.out
                        .println("Product: " + p_name + "(id: " + partID + ") " + "Remaining Quantity: " + p_quantity);
                System.out.println();
            }
        } catch (SQLException e) {
            System.out.println("[Error] " + e.getMessage() + "\n");
        }
    }
}