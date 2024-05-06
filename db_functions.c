#ifndef SQLH
#define SQLH
#include <mysql/mysql.h>
#endif
#ifndef STDIOH
#define STDIOH
#include <stdio.h>
#endif

MYSQL *conn;
// MYSQL_RES *res;
// MYSQL_ROW row;
 char *server = "192.168.1.110";
 char *user = "root";
 char *password = "password"; // Replace with your actual password
 char *database = "expenses"; // Replace with your desired database name
#define MAX_STRING 256
void freemysqlrsource(MYSQL_RES *res, MYSQL *conn)
{
    mysql_free_result(res);
    mysql_close(conn);
}

MYSQL_RES *sendquery(char *query)
{
    MYSQL_RES *res;
    //char *server = "192.168.1.110";
    //char *user = "root";
    //char *password = "password"; // Replace with your actual password
    //char *database = "expenses"; // Replace with your desired database name
    conn = mysql_init(NULL);
    // Connect to the database
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        exit(1);
    }
    // Execute an SQL query
    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        exit(1);
    }
    // Retrieve and print table names
    res = mysql_use_result(conn);
    return res;
}


int add_gas_expense(char * datetime,double gallons,double price,char * address)
{
   //snprintf(query, MAX_STRING, "INSERT INTO users (id, name) VALUES (%d, '%s')", id, name);
   //INSERT INTO `expenses`.`gas_business` (`purshase_date`, `gallons`, `price_g`, `store_addr`) VALUES ('2024-05-05 14:30:00.0000', '3', '4', 'test');
   conn = mysql_init(NULL);
     if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
  {
      fprintf(stderr, "Error: %s\n", mysql_error(conn));
      exit(1);
  }
   
    char * query;
     snprintf(query, MAX_STRING, "INSERT INTO `expenses`.`gas_business` (`purshase_date`, `gallons`, `price_g`, `store_addr`) VALUES ('%s', '%.2f', '%.2f', '%s');", datetime, gallons,price,address);
 printf(query);
 printf("\n");
        if (mysql_query(conn, query) == 0) {
            printf("Data inserted successfully!\n");
            return 0;
        } else {
            printf("Error: %s\n", mysql_error(conn));
            return 1;
        }

}


