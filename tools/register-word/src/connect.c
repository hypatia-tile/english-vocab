#include "connect.h"
#include <stdio.h>
#include <stdlib.h>

sqlite3 *mustConnect(const char *connString) {
  sqlite3 *db = NULL;
  int rc = sqlite3_open(connString, &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
    exit(1);
  }
  return db;
}
