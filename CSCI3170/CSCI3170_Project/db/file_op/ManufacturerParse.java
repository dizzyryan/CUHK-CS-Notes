package db.file_op;

import java.sql.*;
import java.util.*;

import db.GeneralFileHandler;
import db.db_op.*;

public class ManufacturerParse implements GeneralFileHandler {
    private List<ManufacturerTable> batchItems = new ArrayList<>();

    public void parseLines(List<String> lines) {
        batchItems.clear();
        for (String line : lines) {
            if (line == null || line.isEmpty())
                continue;
            String[] parts;
            if (line.contains("\t")) {
                parts = line.split("\t");
            } else {
                parts = line.trim().split("\\s+");
            }
            if (parts.length != 4) {
                continue;
            }
            int mId = Integer.parseInt(parts[0]);
            String mName = parts[1];
            String mAddress = parts[2];
            int mPhoneNumber = Integer.parseInt(parts[3]);
            batchItems.add(new ManufacturerTable(mId, mName, mAddress, mPhoneNumber));
        }
    }

    public void insertBatchToDB(Connection connection) throws SQLException {
        if (batchItems.isEmpty())
            return;
        ManufacturerTable.databaseInsertBatch(connection, batchItems);
    }
}
