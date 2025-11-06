package db.db_op;

import java.sql.*;
import java.util.List;

public class ManufacturerTable {
    private int mId;
    private String mName;
    private String mAddress;
    private int mPhoneNumber;

    public ManufacturerTable(int mId, String mName, String mAddress, int mPhoneNumber) {
        this.mId = mId;
        this.mName = mName;
        this.mAddress = mAddress;
        this.mPhoneNumber = mPhoneNumber;
    }

    public static void databaseInsertBatch(Connection connection, List<ManufacturerTable> items) throws SQLException {
        PreparedStatement pstmt = connection.prepareStatement(
                "INSERT INTO manufacturer (mId, mName, mAddress, mPhoneNumber) VALUES (?, ?, ?, ?)");
        for (ManufacturerTable item : items) {
            pstmt.setInt(1, item.mId);
            pstmt.setString(2, item.mName);
            pstmt.setString(3, item.mAddress);
            pstmt.setInt(4, item.mPhoneNumber);
            pstmt.addBatch();
        }
        pstmt.executeBatch();
        pstmt.close();
    }
}
