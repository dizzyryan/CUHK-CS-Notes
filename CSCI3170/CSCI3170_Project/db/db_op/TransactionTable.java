package db.db_op;

import java.sql.*;

public class TransactionTable {
    private int t_id;
    private int p_id;
    private int s_id;
    private String t_date;

    public TransactionTable(int t_id, int p_id, int s_id, String t_date) {
        this.t_id = t_id;
        this.p_id = p_id;
        this.s_id = s_id;
        this.t_date = t_date;
    }

    public void databaseInsert(Connection conn) throws SQLException {
        PreparedStatement stmt = conn
                .prepareStatement("INSERT INTO transactionrecords (t_id, p_id, s_id, t_date) VALUES (?, ?, ?, TO_DATE('" + t_date + "', 'DD/MM/YYYY'))");
        stmt.setInt(1, t_id);
        stmt.setInt(2, p_id);
        stmt.setInt(3, s_id);
        stmt.execute();
    }
}
