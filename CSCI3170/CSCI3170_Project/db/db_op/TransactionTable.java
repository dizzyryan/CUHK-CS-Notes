package db.db_op;

import java.sql.*;
import java.util.List;

public class TransactionTable {
    private int tId;
    private int pId;
    private int sId;
    private String tDate;

    public TransactionTable(int tId, int pId, int sId, String tDate) {
        this.tId = tId;
        this.pId = pId;
        this.sId = sId;
        this.tDate = tDate;
    }

    public static void databaseInsertBatch(Connection connection, List<TransactionTable> items) throws SQLException {
        PreparedStatement pstmt = connection
                .prepareStatement(
                        "INSERT INTO transaction (tId, pId, sId, tDate) VALUES (?, ?, ?, TO_DATE(?, 'DD/MM/YYYY'))");
        for (TransactionTable item : items) {
            pstmt.setInt(1, item.tId);
            pstmt.setInt(2, item.pId);
            pstmt.setInt(3, item.sId);
            pstmt.setString(4, item.tDate);
            pstmt.addBatch();
        }
        pstmt.executeBatch();
        pstmt.close();
    }
}
