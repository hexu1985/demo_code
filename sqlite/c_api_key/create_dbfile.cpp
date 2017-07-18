#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "open_db.h"

int main(int argc, char* argv[])
{
   sqlite3 *db = open_db(argc, argv);
   sqlite3_close(db);
   return 0;
}
