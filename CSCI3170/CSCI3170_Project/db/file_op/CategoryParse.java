package db.file_op;

import java.sql.*;
import java.util.*;

import db.GeneralFileHandler;
import db.db_op.*;

public class CategoryParse implements GeneralFileHandler {
    private List<CategoryTable> batchItems = new ArrayList<>();

    public void parseLines(List<String> lines) {
        batchItems.clear();
        for (String line : lines) {
            if (line == null || line.isEmpty())
                continue;
            String[] parts = line.split("\t");
            if (parts.length != 2) {
                continue;
            }
            int cId = Integer.parseInt(parts[0]);
            String cName = parts[1];
            batchItems.add(new CategoryTable(cId, cName));
        }
    }

    public void insertBatchToDB(Connection connection) throws SQLException {
        if (batchItems.isEmpty())
            return;
        CategoryTable.databaseInsertBatch(connection, batchItems);
    }
}
