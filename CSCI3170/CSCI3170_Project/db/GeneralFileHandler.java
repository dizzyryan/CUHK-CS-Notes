package db;

import java.sql.*;
import java.util.List;

public interface GeneralFileHandler {
    public void parseLines(List<String> lines);

    public void insertBatchToDB(Connection connection) throws SQLException;
}
