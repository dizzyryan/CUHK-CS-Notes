package db.db_op;

import java.sql.*;
import java.util.List;

public class PartTable {
    private int pId;
    private String pName;
    private int pPrice;
    private int mId;
    private int cId;
    private int pWarranty;
    private int pAvailableQuantity;

    public PartTable(int pId, String pName, int pPrice, int mId, int cId, int pWarranty, int pAvailableQuantity) {
        this.pId = pId;
        this.pName = pName;
        this.pPrice = pPrice;
        this.mId = mId;
        this.cId = cId;
        this.pWarranty = pWarranty;
        this.pAvailableQuantity = pAvailableQuantity;
    }

    public static void databaseInsertBatch(Connection connection, List<PartTable> items) throws SQLException {
        PreparedStatement pstmt = connection.prepareStatement(
                "INSERT INTO part (pId, pName, pPrice, mId, cId, pWarranty, pAvailableQuantity) VALUES (?, ?, ?, ?, ?, ?, ?)");
        for (PartTable item : items) {
            pstmt.setInt(1, item.pId);
            pstmt.setString(2, item.pName);
            pstmt.setInt(3, item.pPrice);
            pstmt.setInt(4, item.mId);
            pstmt.setInt(5, item.cId);
            pstmt.setInt(6, item.pWarranty);
            pstmt.setInt(7, item.pAvailableQuantity);
            pstmt.addBatch();
        }
        pstmt.executeBatch();
        pstmt.close();
    }
}
