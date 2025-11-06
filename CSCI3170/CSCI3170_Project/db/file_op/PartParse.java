package db.file_op;

import java.sql.*;
import java.util.*;

import db.GeneralFileHandler;
import db.db_op.*;

public class PartParse implements GeneralFileHandler {
    private List<PartTable> batchItems = new ArrayList<>();

    public void parseLines(List<String> lines) {
        batchItems.clear();
        for (String line : lines) {
            if (line == null || line.isEmpty())
                continue;
            String[] parts = line.split("\t");
            if (parts.length != 7) {
                continue;
            }
            int pId = Integer.parseInt(parts[0]);
            String pName = parts[1];
            int pPrice = Integer.parseInt(parts[2]);
            int mId = Integer.parseInt(parts[3]);
            int cId = Integer.parseInt(parts[4]);
            int pWarranty = Integer.parseInt(parts[5]);
            int pAvailableQuantity = Integer.parseInt(parts[6]);
            batchItems.add(new PartTable(pId, pName, pPrice, mId, cId, pWarranty, pAvailableQuantity));
        }
    }

    public void insertBatchToDB(Connection connection) throws SQLException {
        if (batchItems.isEmpty())
            return;
        PartTable.databaseInsertBatch(connection, batchItems);
    }
}
