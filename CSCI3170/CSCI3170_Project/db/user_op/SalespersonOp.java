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
                String sql = "SELECT p.pId, p.pName, m.mName, c.cName, p.pAvailableQuantity, p.pWarranty, p.pPrice FROM part p JOIN manufacturer m ON p.mId = m.mId JOIN category c ON p.cId = c.cId WHERE LOWER(p.pName) LIKE LOWER(?) ORDER BY p.pPrice "
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
                pstmt.close();
                rs.close();
            } catch (SQLException e) {
                System.out.println("[Error] " + e.getMessage() + "\n");
            }
        } else if (searchCriterion.equals("m_name")) {
            try {
                String sql = "SELECT p.pId, p.pName, m.mName, c.cName, p.pAvailableQuantity, p.pWarranty, p.pPrice FROM part p JOIN manufacturer m ON p.mId = m.mId JOIN category c ON p.cId = c.cId WHERE LOWER(m.mName) LIKE LOWER(?) ORDER BY p.pPrice "
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
                pstmt.close();
                rs.close();
            } catch (SQLException e) {
                System.out.println("[Error] " + e.getMessage() + "\n");
            }
        }
    }

    public void sellAPart(int partID, int salespersonID) throws SQLException {
        try {
            PreparedStatement pstmtQC = connection
                    .prepareStatement("SELECT pAvailableQuantity FROM part WHERE pId = ?");
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
                int tId = 1;
                String sql = "SELECT NVL(MAX(tId), 0) AS max_tid FROM transaction";
                PreparedStatement pstmt = connection.prepareStatement(sql);
                ResultSet maxTID = pstmt.executeQuery();
                if (!maxTID.next()) {
                    tId = 1;
                } else {
                    tId = maxTID.getInt(1) + 1;
                }
                PreparedStatement[] pstmts = {
                        connection.prepareStatement(
                                "INSERT INTO transaction (tId, pId, sId, tDate) VALUES (?, ?, ?, TRUNC(CURRENT_DATE))"),
                        connection.prepareStatement(
                                "UPDATE part SET pAvailableQuantity = pAvailableQuantity - 1 WHERE pId = ?"),
                };
                pstmts[0].setInt(1, tId);
                pstmts[0].setInt(2, partID);
                pstmts[0].setInt(3, salespersonID);
                pstmts[1].setInt(1, partID);

                for (int i = 0; i < pstmts.length; i++) {
                    pstmts[i].executeUpdate();
                    pstmts[i].close();
                }
                pstmt.close();
                maxTID.close();

                PreparedStatement[] results = {
                        connection.prepareStatement(
                                "SELECT pName FROM part WHERE pId = " + partID),
                        connection.prepareStatement(
                                "SELECT pAvailableQuantity FROM part WHERE pId = " + partID)
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
                results[0].close();
                results[1].close();
                rsName.close();
                rsQty.close();
            }
            pstmtQC.close();
            rs.close();
        } catch (SQLException e) {
            System.out.println("[Error] " + e.getMessage() + "\n");
        }
    }
}