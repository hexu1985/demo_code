#include <iostream>
#include <SQLiteCpp/Database.h>
#include "try_catch_decorator.h"

void insert()
{
    /* Open database */
    SQLite::Database db("test.db", SQLite::OPEN_READWRITE);
    std::cout << "Opened database successfully\n";

    /* Create SQL statement */
    char *sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
           "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
           "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
           "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
           "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
           "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
           "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
           "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

    /* Execute SQL statement */
    db.exec(sql);
    std::cout << "Records created successfully\n";
}

int main(int argc, char* argv[])
{
    try_catch_decorator(insert);
    return 0;
}
