#include <mysql/mysql.h>
#include <stdio.h>


MYSQL_RES *res = NULL;
MYSQL_ROW row = NULL;
MYSQL *conn;
char *server = "192.168.1.211";
char *user = "root";
char *password = "password"; // Replace with your actual password
char *database = "expenses"; // Replace with your desired database name
int add_gas_expense(char *datetime, double gallons, double price, char *address)
{

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        exit(1);
    }

    char *query;
    snprintf(query, 255, "INSERT INTO `expenses`.`gas_business` (`purshase_date`, `gallons`, `price_g`, `store_addr`) VALUES ('%s', '%.2f', '%.2f', '%s');", datetime, gallons, price, address);
    printf(query);
   
    if (mysql_query(conn, query) == 0)
    {
       
        return 0;
    }
    else
    {
        printf("Error: %s\n", mysql_error(conn));
        return 1;
    }
}



int main()
{
/*
    res = sendquery("SELECT * FROM expenses.gas_business");

    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%s\n", row[1]);
    }
*/
  
    add_gas_expense("2024-05-05",2.5,3.6,"ttest3");
    add_gas_expense("2024-07-05",2,3,"ttesft3");
    add_gas_expense("2024-06-05",2.7,3,"ttest3");
    add_gas_expense("2024-08-05",2,3,"ff");
    add_gas_expense("2024-06-05",2,3.9,"normalnm");
    add_gas_expense("2024-09-05",2,3,"ttfbbest3");
    add_gas_expense("2024-04-27",4.45,4.799,"1515 164 ave SW Lynnwood WA");
    

 /*    res = sendquery("select sum(gallons *price_g) from expenses.gas_business");
 while ((row = mysql_fetch_row(res)) != NULL)
 {
     printf("%s\n", row[0]);
 }
  */
 mysql_free_result(res);
    mysql_close(conn);

    return 0;
}