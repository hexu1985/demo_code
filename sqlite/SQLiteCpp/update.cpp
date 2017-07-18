#include <iostream>
#include <SQLiteCpp/Database.h>
#include "try_catch_decorator.h"

void update()
{
    /* Open database */
    SQLite::Database db("test.db", SQLite::OPEN_READWRITE);
    std::cout << "Opened database successfully\n";

    /* Create SQL statement */
    char *sql = "UPDATE COMPANY set SALARY = 25000.00 where ID=1";

    /* Execute SQL statement */
    db.exec(sql);
    std::cout << "Operation done successfully\n";
}

int main(int argc, char* argv[])
{
    try_catch_decorator(update);
    return 0;
}
