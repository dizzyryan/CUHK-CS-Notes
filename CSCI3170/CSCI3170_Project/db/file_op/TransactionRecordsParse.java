package db.file_op;

import java.sql.*;

import db.GeneralFileHandler;
import db.db_op.*;

public class TransactionRecordsParse implements GeneralFileHandler {
    private int t_id;
    private int p_id;
    private int s_id;
    private String t_date;

    public void parseLine(String line) {
        String[] parts = line.split("\t");
        this.t_id = Integer.parseInt(parts[0]);
        this.p_id = Integer.parseInt(parts[1]);
        this.s_id = Integer.parseInt(parts[2]);
        this.t_date = parts[3];
    }

    public void insertToDB(Connection conn) throws SQLException {
        TransactionRecordsTable item = new TransactionRecordsTable(t_id, p_id, s_id, t_date);
        item.databaseInsert(conn);
    }
}
