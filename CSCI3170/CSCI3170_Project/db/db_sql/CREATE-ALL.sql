-- Table creation --
CREATE TABLE Part (
  p_id INTEGER NOT NULL PRIMARY KEY CHECK (p_id > 0 AND p_id < 1000), 
  p_name VARCHAR2(20) NOT NULL, 
  p_price INTEGER NOT NULL CHECK (p_price > 0 AND p_price < 100000), 
  m_id INTEGER NOT NULL CHECK (m_id > 0 AND m_id < 100), 
  c_id INTEGER NOT NULL CHECK (c_id > 0 AND c_id < 10), 
  p_warranty INTEGER NOT NULL CHECK (p_warranty > 0 AND p_warranty < 100), 
  p_quantity INTEGER NOT NULL CHECK (p_quantity >= 0 AND p_quantity <= 100)
);

CREATE TABLE Category (
  c_id INTEGER NOT NULL PRIMARY KEY CHECK (c_id > 0 AND c_id < 10),
  c_name VARCHAR2(20) NOT NULL UNIQUE
);

CREATE TABLE Manufacturer (
  m_id INTEGER NOT NULL PRIMARY KEY CHECK (m_id > 0 AND m_id < 100),
  m_name VARCHAR2(20) NOT NULL,
  m_address VARCHAR2(50) NOT NULL,
  m_phone INTEGER NOT NULL CHECK (m_phone > 0 AND m_phone < 100000000)
);

CREATE TABLE Salesperson (
  s_id INTEGER NOT NULL PRIMARY KEY CHECK (s_id > 0 AND s_id < 100),
  s_name VARCHAR2(20) NOT NULL,
  s_address VARCHAR2(50) NOT NULL,
  s_phone INTEGER NOT NULL CHECK (s_phone > 0 AND s_phone < 100000000),
  s_experience INTEGER NOT NULL CHECK (s_experience > 0 AND s_experience < 10)
);

CREATE TABLE TransactionRecords (
  t_id INTEGER NOT NULL PRIMARY KEY CHECK (t_id > 0 AND t_id < 10000),
  p_id INTEGER NOT NULL CHECK (p_id > 0 AND p_id < 1000),
  s_id INTEGER NOT NULL CHECK (s_id > 0 AND s_id < 100),
  t_date DATE DEFAULT CURRENT_DATE
);
  
-- Table deletion --
DROP TABLE Part;
DROP TABLE Category;
DROP TABLE Manufacturer;
DROP TABLE Salesperson;
DROP TABLE TransactionRecords;
