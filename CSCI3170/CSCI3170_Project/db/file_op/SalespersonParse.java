package db.file_op;

import java.sql.*;

import db.GeneralFileHandler;
import db.db_op.*;

public class SalespersonParse implements GeneralFileHandler {
    private int s_id;
    private String s_name;
    private String s_address;
    private int s_phone;
    private int s_experience;

    public void parseLine(String line) {
        String[] parts = line.split("\t");
        this.s_id = Integer.parseInt(parts[0]);
        this.s_name = parts[1];
        this.s_address = parts[2];
        this.s_phone = Integer.parseInt(parts[3]);
        this.s_experience = Integer.parseInt(parts[4]);
    }

    public void insertToDB(Connection connection) throws SQLException {
        SalespersonTable item = new SalespersonTable(s_id, s_name, s_address, s_phone, s_experience);
        item.databaseInsert(connection);
    }
}
