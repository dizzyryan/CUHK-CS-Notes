package db;

import java.sql.*;

public interface GeneralFileHandler {
    public void parseLine(String line);

    public void insertToDB(Connection connection) throws SQLException;
}
