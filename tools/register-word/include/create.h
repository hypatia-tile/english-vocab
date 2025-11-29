#ifndef CREATE_H
#define CREATE_H
#include <sqlite3.h>
int callback(void *NotUsed, int result_num, char **result_values,
             char **colunm_names);
void exec_sql(sqlite3 *db, char *sql, char **err_msg);
void exec_cb(sqlite3 *db, char *sql,
             int (*callback)(void *, int, char **, char **), char **err_msg);

#endif // CREATE_H
