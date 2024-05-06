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
    add_gas_expense("2024-05-05",2.5,3.6,"ttest3");
    add_gas_expense("2024-07-05",2,3,"ttesft3");
    add_gas_expense("2024-06-05",2.7,3,"ttest3");
    add_gas_expense("2024-08-05",2,3,"ff");
    add_gas_expense("2024-06-05",2,3.9,"normalnm");
    add_gas_expense("2024-09-05",2,3,"ttfbbest3");
    add_gas_expense("2024-04-27",4.45,4.799,"1515 164 ave SW Lynnwood WA");
    

     res = sendquery("select sum(gallons *price_g) from expenses.gas_business");
 while ((row = mysql_fetch_row(res)) != NULL)
 {
     printf("%s\n", row[0]);
 }
  freemysqlrsource(res, conn);
    return 0;
}