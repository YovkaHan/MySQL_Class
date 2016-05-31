#include "db_sql.h"

int main()
{
	MySQL_QC first("tcp://localhost:3306", "root", "pass", "mydb");

	char answer = 'y';
	do
	{
		first.output_q(first.query());
		std::cout << "\nDo you want to continue? (input 'n' for NO also 's' to Clear Screen)";
		std::cin >> answer;
		std::cin.ignore();
		if (answer == 'n')
			break;
		else if (answer == 's')
			system("cls");
	} while (1);
	system("pause");
	return 0;
}