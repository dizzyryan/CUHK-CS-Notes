package db.file_op;

import java.sql.*;

import db.GeneralFileHandler;
import db.db_op.*;

public class PartTableParse implements GeneralFileHandler {
    private int p_id;
    private String p_name;
    private int p_price;
    private int m_id;
    private int c_id;
    private int p_warranty;
    private int p_quantity;

    public void parseLine(String line) {
        String[] parts = line.split("\t");
        this.p_id = Integer.parseInt(parts[0]);
        this.p_name = parts[1];
        this.p_price = Integer.parseInt(parts[2]);
        this.m_id = Integer.parseInt(parts[3]);
        this.c_id = Integer.parseInt(parts[4]);
        this.p_warranty = Integer.parseInt(parts[5]);
        this.p_quantity = Integer.parseInt(parts[6]);
    }

    public void insertToDB(Connection connection) throws SQLException {
        PartTable item = new PartTable(p_id, p_name, p_price, m_id, c_id, p_warranty, p_quantity);
        item.databaseInsert(connection);
    }
}
