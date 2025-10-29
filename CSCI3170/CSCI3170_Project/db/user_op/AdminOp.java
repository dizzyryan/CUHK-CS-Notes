package db.user_op;

import java.io.*;
import java.sql.*;
import java.text.SimpleDateFormat;

import db.GeneralFileHandler;
import db.file_op.*;

public class AdminOp {
    final String[] tables = { "part", "category", "manufacturer", "salesperson", "transactionrecords" };

    private Connection connection;

    public AdminOp(Connection connection) {
        this.connection = connection;
    }

    public void createAllTables() throws SQLException {
        PreparedStatement[] pstmts = {
                connection.prepareStatement(
                        "CREATE TABLE Part (p_id INTEGER NOT NULL PRIMARY KEY CHECK (p_id > 0 AND p_id < 1000), p_name VARCHAR2(20) NOT NULL, p_price INTEGER NOT NULL CHECK (p_price > 0 AND p_price < 100000), m_id INTEGER NOT NULL CHECK (m_id > 0 AND m_id < 100), c_id INTEGER NOT NULL CHECK (c_id > 0 AND c_id < 10), p_warranty INTEGER NOT NULL CHECK (p_warranty > 0 AND p_warranty < 100), p_quantity INTEGER NOT NULL CHECK (p_quantity >= 0 AND p_quantity <= 100))"),
                connection.prepareStatement(
                        "CREATE TABLE Category (c_id INTEGER NOT NULL PRIMARY KEY CHECK (c_id > 0 AND c_id < 10), c_name VARCHAR2(20) NOT NULL UNIQUE)"),
                connection.prepareStatement(
                        "CREATE TABLE Manufacturer (m_id INTEGER NOT NULL PRIMARY KEY CHECK (m_id > 0 AND m_id < 100),m_name VARCHAR2(20) NOT NULL,m_address VARCHAR2(50) NOT NULL,m_phone INTEGER NOT NULL CHECK (m_phone > 9999999 AND m_phone < 100000000))"),
                connection.prepareStatement(
                        "CREATE TABLE Salesperson (s_id INTEGER NOT NULL PRIMARY KEY CHECK (s_id > 0 AND s_id < 100),s_name VARCHAR2(20) NOT NULL,s_address VARCHAR2(50) NOT NULL,s_phone INTEGER NOT NULL CHECK (s_phone > 9999999 AND s_phone < 100000000),s_experience INTEGER NOT NULL CHECK (s_experience > 0 AND s_experience < 10))"),
                connection.prepareStatement(
                        "CREATE TABLE TransactionRecords (t_id INTEGER NOT NULL PRIMARY KEY CHECK (t_id > 0 AND t_id < 10000),p_id INTEGER NOT NULL CHECK (p_id > 0 AND p_id < 1000),s_id INTEGER NOT NULL CHECK (s_id > 0 AND s_id < 100),t_date DATE DEFAULT CURRENT_DATE)")
        };

        for (int i = 0; i < pstmts.length; i++) {
            pstmts[i].execute();
        }
    }

    public void deleteAllTables() throws SQLException {
        for (int i = 0; i < tables.length; i++) {
            PreparedStatement pstmt = connection.prepareStatement("DROP TABLE " + tables[i]);
            pstmt.execute();
        }
    }

    public void loadFromDatafile(String folderPath) throws Exception {
        readFile(folderPath + "/category.txt", CategoryParse.class);
        readFile(folderPath + "/manufacturer.txt", ManufacturerParse.class);
        readFile(folderPath + "/part.txt", PartTableParse.class);
        readFile(folderPath + "/salesperson.txt", SalespersonTableParse.class);
        readFile(folderPath + "/transaction.txt", TransactionRecordsParse.class);
    }

    private void readFile(String filePath, Class<?> type) throws Exception {
        BufferedReader r;
        r = new BufferedReader(new FileReader(filePath));
        String line = r.readLine();
        while (line != null) {
            GeneralFileHandler model = (GeneralFileHandler) type.getDeclaredConstructor().newInstance();
            model.parseLine(line);
            model.insertToDB(connection);
            line = r.readLine();
        }
        r.close();
    }

    public void showTableContent(String tableName) throws SQLException {
        SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
        PreparedStatement pstmt = connection.prepareStatement("SELECT * FROM " + tableName);
        ResultSet result = pstmt.executeQuery();
        System.out.println("Content of table " + tableName + ":");
        switch (tableName) {
            case "part":
                System.out.println("| p_id | p_name | p_price | m_id | c_id | p_warranty | p_quantity |");
                break;
            case "category":
                System.out.println("| c_id | c_name |");
                break;
            case "manufacturer":
                System.out.println("| m_id | m_name | m_address | m_phone |");
                break;
            case "salesperson":
                System.out.println("| s_id | s_name | s_address | s_phone | s_experience |");
                break;
            case "transactionrecords":
                System.out.println("| t_id | p_id | s_id | t_date |");
                break;
        }
        while (result.next()) {
            switch (tableName) {
                case "part":
                    System.out.println("| " + result.getInt(1) + " | " + result.getString(2) + " | "
                            + result.getInt(3) + " | " + result.getInt(4) + " | " + result.getInt(5) + " | "
                            + result.getInt(6) + " | " + result.getInt(7) + " |");
                    break;
                case "category":
                    System.out.println("| " + result.getInt(1) + " | " + result.getString(2) + " |");
                    break;
                case "manufacturer":
                    System.out.println("| " + result.getInt(1) + " | " + result.getString(2) + " | "
                            + result.getString(3) + " | " + result.getInt(4) + " |");
                    break;
                case "salesperson":
                    System.out.println("| " + result.getInt(1) + " | " + result.getString(2) + " | "
                            + result.getString(3) + " | " + result.getInt(4) + " | " + result.getInt(5) + " |");
                    break;
                case "transactionrecords":
                    System.out.println("| " + result.getInt(1) + " | " + result.getInt(2) + " | " + result.getInt(3)
                            + " | " + sdf.format(result.getDate(4)) + " |");
                    break;
            }
        }
        System.out.println();
        result.close();
        pstmt.close();
    }

}
