package db.db_op;

import java.sql.*;
import java.util.List;

public class CategoryTable {
    private int cId;
    private String cName;

    public CategoryTable(int cId, String cName) {
        this.cId = cId;
        this.cName = cName;
    }

    public static void databaseInsertBatch(Connection connection, List<CategoryTable> items) throws SQLException {
        PreparedStatement pstmt = connection.prepareStatement("INSERT INTO category (cId, cName) VALUES (?, ?)");
        for (CategoryTable item : items) {
            pstmt.setInt(1, item.cId);
            pstmt.setString(2, item.cName);
            pstmt.addBatch();
        }
        pstmt.executeBatch();
        pstmt.close();
    }
}
