package db.db_op;

import java.sql.*;

public class SalespersonTable {
    private int s_id;
    private String s_name;
    private String s_address;
    private int s_phone;
    private int s_experience;

    public SalespersonTable(int s_id, String s_name, String s_address, int s_phone, int s_experience) {
        this.s_id = s_id;
        this.s_name = s_name;
        this.s_address = s_address;
        this.s_phone = s_phone;
        this.s_experience = s_experience;
    }

    public void databaseInsert(Connection connection) throws SQLException {
            PreparedStatement pstmt = connection.prepareStatement(
                    "INSERT INTO salesperson (s_id, s_name, s_address, s_phone, s_experience) VALUES (?, ?, ?, ?, ?)");
            pstmt.setInt(1, s_id);
            pstmt.setString(2, s_name);
            pstmt.setString(3, s_address);
            pstmt.setInt(4, s_phone);
            pstmt.setInt(5, s_experience);
            pstmt.execute();
    }
}
