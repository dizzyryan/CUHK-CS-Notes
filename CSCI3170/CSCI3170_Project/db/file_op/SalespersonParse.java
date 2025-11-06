package db.file_op;

import java.sql.*;
import java.util.*;

import db.GeneralFileHandler;
import db.db_op.*;

public class SalespersonParse implements GeneralFileHandler {
    private List<SalespersonTable> batchItems = new ArrayList<>();

    public void parseLines(List<String> lines) {
        batchItems.clear();
        for (String line : lines) {
            if (line == null || line.isEmpty())
                continue;
            String[] parts = line.split("\t");
            if (parts.length != 5) {
                continue;
            }
            int sId = Integer.parseInt(parts[0]);
            String sName = parts[1];
            String sAddress = parts[2];
            int sPhoneNumber = Integer.parseInt(parts[3]);
            int sExperience = Integer.parseInt(parts[4]);
            batchItems.add(new SalespersonTable(sId, sName, sAddress, sPhoneNumber, sExperience));
        }
    }

    public void insertBatchToDB(Connection connection) throws SQLException {
        if (batchItems.isEmpty())
            return;
        SalespersonTable.databaseInsertBatch(connection, batchItems);
    }
}
