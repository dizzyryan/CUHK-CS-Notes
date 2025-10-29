package db.db_op;

import java.sql.*;

public class PartTable {
    private int p_id;
    private String p_name;
    private int p_price;
    private int m_id;
    private int c_id;
    private int p_warranty;
    private int p_quantity;

    public PartTable(int p_id, String p_name, int p_price, int m_id, int c_id, int p_warranty, int p_quantity) {
        this.p_id = p_id;
        this.p_name = p_name;
        this.p_price = p_price;
        this.m_id = m_id;
        this.c_id = c_id;
        this.p_warranty = p_warranty;
        this.p_quantity = p_quantity;
    }

    public void databaseInsert(Connection connection) throws SQLException {
            PreparedStatement pstmt = connection.prepareStatement(
                    "INSERT INTO part (p_id, p_name, p_price, m_id, c_id, p_warranty, p_quantity) VALUES (?, ?, ?, ?, ?, ?, ?)");
            pstmt.setInt(1, p_id);
            pstmt.setString(2, p_name);
            pstmt.setInt(3, p_price);
            pstmt.setInt(4, m_id);
            pstmt.setInt(5, c_id);
            pstmt.setInt(6, p_warranty);
            pstmt.setInt(7, p_quantity);
            pstmt.execute();
    }
}
