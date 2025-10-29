package db.file_op;

import java.sql.*;

import db.*;
import db.db_op.*;

public class CategoryParse implements GeneralFileHandler {
    private int c_id;
    private String c_name;

    public void parseLine(String line) {
        String[] parts = line.split("\t");
        this.c_id = Integer.parseInt(parts[0]);
        this.c_name = parts[1];
    }

    public void insertToDB(Connection connection) throws SQLException {
        CategoryTable item = new CategoryTable(c_id, c_name);
        item.databaseInsert(connection);
    }
}
