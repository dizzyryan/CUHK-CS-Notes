package db.db_op;

import java.sql.*;
import java.util.List;

public class SalespersonTable {
    private int sId;
    private String sName;
    private String sAddress;
    private int sPhoneNumber;
    private int sExperience;

    public SalespersonTable(int sId, String sName, String sAddress, int sPhoneNumber, int sExperience) {
        this.sId = sId;
        this.sName = sName;
        this.sAddress = sAddress;
        this.sPhoneNumber = sPhoneNumber;
        this.sExperience = sExperience;
    }

    public static void databaseInsertBatch(Connection connection, List<SalespersonTable> items) throws SQLException {
        PreparedStatement pstmt = connection.prepareStatement(
                "INSERT INTO salesperson (sId, sName, sAddress, sPhoneNumber, sExperience) VALUES (?, ?, ?, ?, ?)");
        for (SalespersonTable item : items) {
            pstmt.setInt(1, item.sId);
            pstmt.setString(2, item.sName);
            pstmt.setString(3, item.sAddress);
            pstmt.setInt(4, item.sPhoneNumber);
            pstmt.setInt(5, item.sExperience);
            pstmt.addBatch();
        }
        pstmt.executeBatch();
        pstmt.close();
    }
}
