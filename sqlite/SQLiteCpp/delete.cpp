#include <iostream>
#include <SQLiteCpp/Database.h>
#include "try_catch_decorator.h"

void table_delete()
{
    /* Open database */
    SQLite::Database db("test.db", SQLite::OPEN_READWRITE);
    std::cout << "Opened database successfully\n";

    /* Create SQL statement */
    char *sql = "DELETE from COMPANY where ID=2"; 

    /* Execute SQL statement */
    db.exec(sql);
    std::cout << "Operation done successfully\n";
}

int main(int argc, char* argv[])
{
    try_catch_decorator(table_delete);
    return 0;
}
