package db.file_op;

import java.sql.*;

import db.GeneralFileHandler;
import db.db_op.*;

public class ManufacturerParse implements GeneralFileHandler {
    private int m_id;
    private String m_name;
    private String m_address;
    private int m_phone;

    public void parseLine(String line) {
        String[] parts = line.split("\t");
        this.m_id = Integer.parseInt(parts[0]);
        this.m_name = parts[1];
        this.m_address = parts[2];
        this.m_phone = Integer.parseInt(parts[3]);
    }

    public void insertToDB(Connection connection) throws SQLException {
        ManufacturerTable item = new ManufacturerTable(m_id, m_name, m_address, m_phone);
        item.databaseInsert(connection);
    }
}
