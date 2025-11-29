#ifndef CONNECT_H
#define CONNECT_H
#include <sqlite3.h>
sqlite3 *mustConnect(const char *connString);

#endif // CONNECT_H
