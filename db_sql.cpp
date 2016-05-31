#include "db_sql.h"

MySQL_QC::MySQL_QC(sql::SQLString _addr_bd, sql::SQLString _login_bd, sql::SQLString _pass_bd, sql::SQLString name_bd)
{
	this->addr_db = _addr_bd;
	this->login_db = _login_bd;
	this->pass_db = _pass_bd;
	this->name_db = name_bd;
	
	setlocale(LC_ALL, "rus");           // Russian 

	try {
		/* Create a connection */
		MySQL_QC_driver = get_driver_instance();
		MySQL_QC_con = MySQL_QC_driver->connect(this->addr_db, this->login_db, this->pass_db);
		/* Connect to the MySQL database */
		MySQL_QC_con->setSchema(this->name_db);
		MySQL_QC_pstmt = MySQL_QC_con->prepareStatement("SET NAMES cp1251");  //Setting charset first
		MySQL_QC_res = MySQL_QC_pstmt->executeQuery();
		std::cout << "Connected to " << name_bd.c_str() << std::endl;

		delete MySQL_QC_res;
		delete MySQL_QC_pstmt;
		                               // After the creation of the connection user can input query into the next method
	}
	catch (sql::SQLException &e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line "
			<< __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() <<
			" )" << std::endl;
	}
}
                                        // Input into a map a ressult of "user_query"
std::map<std::string, std::string> MySQL_QC::query()
{
	inception:
	std::map<std::string, std::string> result;
	try {
		MySQL_QC_pstmt = MySQL_QC_con->prepareStatement(MySQL_QC::input_q());
		MySQL_QC_res = MySQL_QC_pstmt->executeQuery();

		//MySQL_QC_res->afterLast();
		int column = 0;
		this->rows_count = MySQL_QC_res->rowsCount(); // How many rows 

		while (MySQL_QC_res->next())       // Gathering data from MySQL_QC_res
		{
			try
			{
				while (1)
				{
					char buf1[10];         // Source to convert two ints + ":" to string 
					char buf2[10];
					itoa(MySQL_QC_res->getRow(), buf1, 10);
					itoa(column, buf2, 10);
					strcat(buf1, ":");
					result[strcat(buf1, buf2)] = MySQL_QC_res->getString(++column).c_str();
				}
			}
			catch (sql::SQLException &er)
			{
			}
			this->columns_count = column-1;    // How many columns
			column = 0;
		}
		delete MySQL_QC_res;

		delete MySQL_QC_pstmt;
	}
	catch (sql::SQLException &e) {
		std::cout << "\n# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line "
			<< __LINE__ << std::endl;
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ")" << std::endl << std::endl;
		/*std::cout << ", SQLState: " << e.getSQLState() <<
			" )" << std::endl;*/
		goto inception;
	}
	return result;
}

sql::SQLString MySQL_QC::input_q()
{
	inception:
	std::shared_ptr<std::string> str (new std::string);
	std::cout << "Input query (to exit input \"x\"): ";
	getline(std::cin, *str);
	if (*str == "")
		goto inception;
	else if (*str == "x")
		exit(0);
	const char * c = str->c_str();
	sql::SQLString *q = new sql::SQLString(c);
	return *q;
}

void MySQL_QC::output_q(std::map<std::string, std::string> result_from_q)
{
	std::cout << "Queries output: " << std::endl;
	if (!this->columns_count)
	{

	}
	else
	{
		size_t columns = this->columns_count;
		for (std::map<std::string, std::string>::iterator it = result_from_q.begin(); it != result_from_q.end(); it++)
		{
			/*if (it->second.size() > int(80/ this->columns_count))
			{
				std::cout << it->second.substr(0,int( 80 / this->columns_count)) + "..";
			}
			else
			{*/
				std::cout <<it->second;
			//}
			--columns;
			if (columns == 0)
			{
				std::cout << ";" << std::endl;
				columns = this->columns_count;
			}
			else
				std::cout << ", ";
		}
	}
}