#include "connect.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int print_resp(void *get_prm, int col_cnt, char **row_txt, char **col_name);

int main(void) {
  // status and error message
  int ret = 0;
  char *err_msg = NULL;

  // database path
  const char *dict_path = "data/dict/words.db";

  // database handle and sqli string
  sqlite3 *db = NULL;
  char sql_str[255];
  memset(&sql_str[0], 0x00, sizeof(sql_str));

  db = mustConnect(dict_path);

  // Create SQL
  snprintf(&sql_str[0], sizeof(sql_str) - 1, "select * from tb_test;");
  ret = sqlite3_exec(db, &sql_str[0], print_resp, NULL, &err_msg);
  if (SQLITE_OK != ret) {
    // error
    sqlite3_close(db);
    sqlite3_free(err_msg);
    exit(-1);
  }

  ret = sqlite3_close(db);
  if (SQLITE_OK != ret) {
    // error
    exit(-1);
  }
  return 0;
}

int print_resp(void *get_prm, int col_cnt, char **row_txt, char **col_name) {
  printf("%s : %s\n", row_txt[0], row_txt[1]);
  return 0;
}
