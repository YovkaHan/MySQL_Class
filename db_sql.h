//
//First of all!
//include paths to include and libs of "Connector C++", "MySQL Server", "Boost"
//
#pragma once
#pragma comment(lib, "mysqlcppconn-static.lib")
#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "mysqlcppconn.lib")
#pragma comment(lib, "mysqlclient.lib")

#include <string>
#include <locale>
#include <map>
#include <iomanip>
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


class MySQL_QC {
	sql::Driver *MySQL_QC_driver;
	sql::Connection *MySQL_QC_con;
	sql::Statement *MySQL_QC_stmt;
	sql::ResultSet *MySQL_QC_res;
	sql::PreparedStatement *MySQL_QC_pstmt;

	sql::SQLString addr_db;      // user parameters
	sql::SQLString login_db;     // 
	sql::SQLString pass_db;      // 
	sql::SQLString name_db;      // 

	size_t rows_count;
	size_t columns_count;

	//int    out_format;

public:
									// Create connection to DB
	MySQL_QC(sql::SQLString addr_db, sql::SQLString login_db, sql::SQLString pass_db, sql::SQLString name_db);

	std::map<std::string, std::string> query();      // ["1:2" ; "something"] <---construction of "return" map
	sql::SQLString                     input_q();
	void                               output_q(std::map<std::string, std::string>); // strings at output
	//void                               table_output_q(std::map<std::string, std::string>);

};