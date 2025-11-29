#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

sqlite3 *mustConnect(const char *connString);

int print_resp(void *get_prm, int col_cnt, char **row_txt, char **col_name);

int main(void) {
  int ret = 0;
  const char *dict_path = "data/dict/words.db";
  sqlite3 *conn = NULL;
  char *err_msg = NULL;
  char sql_str[255];
  memset(&sql_str[0], 0x00, sizeof(sql_str));
  ret = sqlite3_open(dict_path, &conn);
  if (SQLITE_OK != ret) {
    // error
    exit(-1);
  }

  // Create SQL
  snprintf(&sql_str[0], sizeof(sql_str) - 1, "select * from tb_test;");
  ret = sqlite3_exec(conn, &sql_str[0], print_resp, NULL, &err_msg);
  if (SQLITE_OK != ret) {
    // error
    sqlite3_close(conn);
    sqlite3_free(err_msg);
    exit(-1);
  }

  ret = sqlite3_close(conn);
  if (SQLITE_OK != ret) {
    // error
    exit(-1);
  }
  return 0;
}

sqlite3 *mustConnect(const char *connString) {
  sqlite3 *db = NULL;
  int rc = sqlite3_open(connString, &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
    exit(1);
  }
  return db;
}

int print_resp(void *get_prm, int col_cnt, char **row_txt, char **col_name) {
  printf("%s : %s\n", row_txt[0], row_txt[1]);
  return 0;
}
