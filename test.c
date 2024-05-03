#include <mysql/mysql.h>
#include <stdio.h>
#include "db_functions.c"

MYSQL_RES *res = NULL;
MYSQL_ROW row = NULL;
int main()
{

    res = sendquery("SELECT * FROM expenses.gas_business");

    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%s\n", row[1]);
    }

    freemysqlrsource(res, conn);
    return 0;
}