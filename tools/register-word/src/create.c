#include "create.h"
#include "connect.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  int ret = 0;
  char *err_msg = NULL;

  const char *db_path = "data/dict/words.db";

  sqlite3 *db = NULL;
  char sql_str[255];
  memset(&sql_str[0], 0x00, sizeof(sql_str));

  db = mustConnect(db_path);
  snprintf(&sql_str[0], sizeof(sql_str) - 1, "drop table if exists testable");
  exec_sql(db, &sql_str[0], &err_msg);
  memset(&sql_str[0], 0x00, sizeof(sql_str));
  snprintf(&sql_str[0], sizeof(sql_str) - 1,
           "create table testtable (id2 integer primary key, name2 text)");
  memset(&sql_str[0], 0x00, sizeof(sql_str));
  snprintf(&sql_str[0], sizeof(sql_str) - 1,
           "select * from sqlite_master where type='table'");
  exec_cb(db, &sql_str[0], callback, &err_msg);

  sqlite3_close(db);

  return 0;
}

int callback(void *NotUsed, int result_num, char **result_values,
             char **column_names) {
  int i = 0;
  int *notused;
  notused = NotUsed;
  for (i = 0; i < result_num; i++) {
    printf("%s = %s\n", column_names[i],
           result_values[i] ? result_values[i] : "NULL");
  }
  printf("\n");
  return 0;
}

void exec_sql(sqlite3 *db, char *sql, char **err_msg) {
  int ret = 0;
  // Create table
  ret = sqlite3_exec(db, sql, NULL, NULL, err_msg);
  if (SQLITE_OK != ret) {
    fprintf(stderr, "SQL error: %s\n", *err_msg);
    sqlite3_free(*err_msg);
    sqlite3_close(db);
    exit(1);
  }
}

void exec_cb(sqlite3 *db, char *sql,
             int (*callback)(void *, int, char **, char **), char **err_msg) {
  int ret = 0;
  // Select data
  ret = sqlite3_exec(db, sql, callback, NULL, err_msg);
  if (SQLITE_OK != ret) {
    fprintf(stderr, "SQL error: %s\n", *err_msg);
    sqlite3_free(*err_msg);
    sqlite3_close(db);
    exit(1);
  }
}
