#include <iostream>
#include <SQLiteCpp/Database.h>
#include "try_catch_decorator.h"

void create_table()
{
    /* Open database */
    SQLite::Database db("test.db", SQLite::OPEN_READWRITE);
    std::cout << "Opened database successfully\n";

    /* Create SQL statement */
    char *sql = "CREATE TABLE COMPANY("  \
                 "ID INT PRIMARY KEY     NOT NULL," \
                 "NAME           TEXT    NOT NULL," \
                 "AGE            INT     NOT NULL," \
                 "ADDRESS        CHAR(50)," \
                 "SALARY         REAL );";

   /* Execute SQL statement */
   db.exec(sql);
   std::cout << "Table created successfully\n";
}

int main(int argc, char* argv[])
{
    try_catch_decorator(create_table);
    return 0;
}
