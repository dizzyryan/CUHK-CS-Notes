package db.user_op;

import java.io.*;
import java.sql.*;
import java.util.*;

import db.GeneralFileHandler;
import db.file_op.*;
import java.text.SimpleDateFormat;

public class AdminOp {
    final String[] tables = { "Category", "Manufacturer", "Part", "Salesperson", "Transaction" };

    private Connection connection;

    public AdminOp(Connection connection) {
        this.connection = connection;
    }

    public void createAllTables() throws SQLException {
        PreparedStatement[] pstmts = {
                connection.prepareStatement(
                        "CREATE TABLE Category (" +
                                "cID NUMBER(1) PRIMARY KEY, " +
                                "cName VARCHAR2(20) NOT NULL UNIQUE" +
                                ")"),
                connection.prepareStatement(
                        "CREATE TABLE Manufacturer (" +
                                "mID NUMBER(2) PRIMARY KEY, " +
                                "mName VARCHAR2(20) NOT NULL, " +
                                "mAddress VARCHAR2(50) NOT NULL, " +
                                "mPhoneNumber NUMBER(8) NOT NULL" +
                                ")"),
                connection.prepareStatement(
                        "CREATE TABLE Part (" +
                                "pID NUMBER(3) PRIMARY KEY, " +
                                "pName VARCHAR2(20) NOT NULL, " +
                                "pPrice NUMBER(5) NOT NULL, " +
                                "mID NUMBER(2) NOT NULL, " +
                                "cID NUMBER(1) NOT NULL, " +
                                "pWarranty NUMBER(2) NOT NULL, " +
                                "pAvailableQuantity NUMBER(2) NOT NULL, " +
                                "FOREIGN KEY (mID) REFERENCES Manufacturer(mID), " +
                                "FOREIGN KEY (cID) REFERENCES Category(cID)" +
                                ")"),
                connection.prepareStatement(
                        "CREATE TABLE Salesperson (" +
                                "sID NUMBER(2) PRIMARY KEY, " +
                                "sName VARCHAR2(20) NOT NULL, " +
                                "sAddress VARCHAR2(50) NOT NULL, " +
                                "sPhoneNumber NUMBER(8) NOT NULL, " +
                                "sExperience NUMBER(1) NOT NULL" +
                                ")"),
                connection.prepareStatement(
                        "CREATE TABLE Transaction (" +
                                "tID NUMBER(4) PRIMARY KEY, " +
                                "pID NUMBER(3) NOT NULL, " +
                                "sID NUMBER(2) NOT NULL, " +
                                "tDate DATE NOT NULL, " +
                                "FOREIGN KEY (pID) REFERENCES Part(pID), " +
                                "FOREIGN KEY (sID) REFERENCES Salesperson(sID)" +
                                ")")
        };

        for (PreparedStatement pstmt : pstmts) {
            pstmt.execute();
            pstmt.close();
        }
    }

    public void deleteAllTables() throws SQLException {
        PreparedStatement[] pstmts = {
                connection.prepareStatement("DROP TABLE Transaction"),
                connection.prepareStatement("DROP TABLE Part"),
                connection.prepareStatement("DROP TABLE Salesperson"),
                connection.prepareStatement("DROP TABLE Manufacturer"),
                connection.prepareStatement("DROP TABLE Category")
        };

        for (PreparedStatement pstmt : pstmts) {
            pstmt.execute();
            pstmt.close();
        }
    }

    public void loadFromDatafile(String folderPath) throws Exception {
        readFile(folderPath + "/category.txt", CategoryParse.class);
        readFile(folderPath + "/manufacturer.txt", ManufacturerParse.class);
        readFile(folderPath + "/part.txt", PartParse.class);
        readFile(folderPath + "/salesperson.txt", SalespersonParse.class);
        readFile(folderPath + "/transaction.txt", TransactionParse.class);
    }

    private void readFile(String filePath, Class<?> type) throws Exception {
        BufferedReader r = new BufferedReader(new FileReader(filePath));
        List<String> lines = new ArrayList<>();
        String line = r.readLine();
        while (line != null) {
            lines.add(line);
            line = r.readLine();
        }
        r.close();

        GeneralFileHandler model = (GeneralFileHandler) type.getDeclaredConstructor().newInstance();
        model.parseLines(lines);
        model.insertBatchToDB(connection);
    }

    public void showTableContent(String tableName) throws SQLException {
        boolean isValidTable = false;
        for (String table : tables) {
            if (table.equalsIgnoreCase(tableName)) {
                tableName = table;
                isValidTable = true;
                break;
            }
        }

        if (!isValidTable) {
            throw new SQLException(
                    "Invalid table name! Please choose from: Category, Manufacturer, Part, Salesperson, Transaction");
        }

        SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
        PreparedStatement pstmt = connection.prepareStatement("SELECT * FROM " + tableName);
        ResultSet result = pstmt.executeQuery();
        ResultSetMetaData metaData = result.getMetaData();
        int columnCount = metaData.getColumnCount();
        System.out.println("Content of table " + tableName + ":");

        System.out.print("|");
        for (int i = 1; i <= columnCount; i++) {
            System.out.printf(" %s |", metaData.getColumnName(i));
        }
        System.out.println();

        while (result.next()) {
            System.out.print("|");
            for (int i = 1; i <= columnCount; i++) {
                String value = result.getString(i);
                if (value == null)
                    value = "NULL";
                if (metaData.getColumnType(i) == Types.DATE) {
                    value = sdf.format(result.getDate(i));
                    continue;
                }
                System.out.printf(" %s |", value);
            }
            System.out.println();
        }
        System.out.println();
        result.close();
        pstmt.close();
    }

}
