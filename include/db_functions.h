#ifndef SQLH
#define SQLH
#include <mysql/mysql.h>
#endif
#ifndef STDIOH
#define STDIOH
#include <stdio.h>
#include <stdlib.h>
#endif


void freemysqlrsource(MYSQL_RES *res, MYSQL *conn);
MYSQL_RES *sendquery(char *query);
int add_gas_expense(char *datetime, double gallons, double price, char *address);