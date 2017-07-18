#include <iostream>
#include <SQLiteCpp/Database.h>
#include "try_catch_decorator.h"

void create_dbfile()
{
    SQLite::Database db("test.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    std::cout << "Opened database successfully\n";
}

int main(int argc, char* argv[])
{
    try_catch_decorator(create_dbfile);
    return 0;
}
