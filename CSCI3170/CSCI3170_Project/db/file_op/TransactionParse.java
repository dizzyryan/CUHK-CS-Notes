package db.file_op;

import java.sql.*;
import java.util.*;

import db.GeneralFileHandler;
import db.db_op.*;

public class TransactionParse implements GeneralFileHandler {
    private List<TransactionTable> batchItems = new ArrayList<>();

    public void parseLines(List<String> lines) {
        batchItems.clear();
        for (String line : lines) {
            if (line == null || line.isEmpty())
                continue;
            String[] parts = line.split("\t");
            if (parts.length != 4) {
                continue;
            }
            int tId = Integer.parseInt(parts[0]);
            int pId = Integer.parseInt(parts[1]);
            int sId = Integer.parseInt(parts[2]);
            String tDate = parts[3];
            batchItems.add(new TransactionTable(tId, pId, sId, tDate));
        }
    }

    public void insertBatchToDB(Connection connection) throws SQLException {
        if (batchItems.isEmpty())
            return;
        TransactionTable.databaseInsertBatch(connection, batchItems);
    }
}
