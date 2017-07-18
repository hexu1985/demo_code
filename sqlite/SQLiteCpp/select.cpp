#include <iostream>
#include <iomanip>
#include <SQLiteCpp/Database.h>
#include "try_catch_decorator.h"

void select()
{
    /* Open database */
    SQLite::Database db("test.db", SQLite::OPEN_READWRITE);
    std::cout << "Opened database successfully\n";

    /* Create SQL statement */
    char *sql = "SELECT * from COMPANY";
    SQLite::Statement query(db, sql);

    /* Execute SQL statement */
    bool print_header = false;
    while (query.executeStep())
    {
        if (!print_header) {
            for (int i = 0; i < query.getColumnCount(); i++) {
                std::cout << "|" << std::right << std::setw(10) << query.getColumnName(i);
            }
            std::cout << "|" << std::endl;
            print_header = true;
        }

        for (int i = 0; i < query.getColumnCount(); i++) {
            std::cout << "|" << std::right << std::setw(10) << query.getColumn(i);
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "Operation done successfully\n";
}

int main(int argc, char* argv[])
{
    try_catch_decorator(select);
    return 0;
}
