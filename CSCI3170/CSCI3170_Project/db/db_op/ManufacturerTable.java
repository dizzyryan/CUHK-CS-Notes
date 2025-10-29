package db.db_op;

import java.sql.*;

public class ManufacturerTable {
    private int m_id;
    private String m_name;
    private String m_address;
    private int m_phone;

    public ManufacturerTable(int m_id, String m_name, String m_address, int m_phone) {
        this.m_id = m_id;
        this.m_name = m_name;
        this.m_address = m_address;
        this.m_phone = m_phone;
    }

    public void databaseInsert(Connection connection) throws SQLException {
        PreparedStatement pstmt = connection.prepareStatement(
                "INSERT INTO manufacturer (m_id, m_name, m_address, m_phone) VALUES (?, ?, ?, ?)");
        pstmt.setInt(1, m_id);
        pstmt.setString(2, m_name);
        pstmt.setString(3, m_address);
        pstmt.setInt(4, m_phone);
        pstmt.execute();
    }
}
