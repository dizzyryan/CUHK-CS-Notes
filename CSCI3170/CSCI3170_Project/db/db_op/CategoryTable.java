package db.db_op;

import java.sql.*;

public class CategoryTable {
    private int c_id;
    private String c_name;

    public CategoryTable(int c_id, String c_name) {
        this.c_id = c_id;
        this.c_name = c_name;
    }

    public void databaseInsert(Connection connection) throws SQLException {
        PreparedStatement pstmt = connection.prepareStatement("INSERT INTO category (c_id, c_name) VALUES (?, ?)");
        pstmt.setInt(1, c_id);
        pstmt.setString(2, c_name);
        pstmt.execute();
    }
}
