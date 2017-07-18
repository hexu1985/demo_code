#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

#include "sqlite3.h"

sqlite3 *open_db(int argc, char* argv[])
{
	int opt;
    std::string skey;
    std::string rkey;
    bool skey_flag = false;
    bool rkey_flag = false;
	while ((opt = getopt(argc, argv, "hs:r:")) != -1) {
		switch (opt) {
			case 's':
                skey_flag = true;
                skey = optarg;
				break;
			case 'r':
                rkey_flag = true;
                rkey = optarg;
				break;
            case 'h':
			default: /* '?' */
				fprintf(stderr, "Usage: %s [-s skey] [-r rkey] db\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-s skey] [-r rkey] db\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	printf("db argument = %s\n", argv[optind]);
    char *filename = argv[optind];

    sqlite3 *db;
    int rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "sqlite3_open fail: %s\n", sqlite3_errmsg(db));
        exit(0);
    } else {
        fprintf(stderr, "sqlite3_open ok\n");
    }

    if (skey_flag) {
        rc = sqlite3_key(db, skey.c_str(), skey.length());
        if (rc != SQLITE_OK) {
            fprintf(stderr, "sqlite3_key fail: %s\n", sqlite3_errmsg(db));
            exit(0);
        } else {
            fprintf(stderr, "sqlite3_key ok\n");
        }
    }

    if (rkey_flag) {
        rc = sqlite3_rekey(db, rkey.c_str(), rkey.length());
        if (rc != SQLITE_OK) {
            fprintf(stderr, "sqlite3_rekey fail: %s\n", sqlite3_errmsg(db));
            exit(0);
        } else {
            fprintf(stderr, "sqlite3_rekey ok\n");
        }
    }

    return db;
}
