#include "db_functions.h"

// MYSQL_RES *res;
// MYSQL_ROW row;
char *server = "192.168.1.110";
char *user = "root";
char *password = "password"; // Replace with your actual password
char *database = "expenses"; // Replace with your desired database name
#define MAX_STRING 556
void freemysqlrsource(MYSQL_RES *res, MYSQL *conn)
{
    mysql_free_result(res);
    mysql_close(conn);
}

MYSQL_RES *sendquery(char *query)
{
    /* check if required env vars set if not exit*/
    server = getenv("DB_SERVER");
    user = getenv("DBUSER");
    password = getenv("PASSWORD");
    printf(server);
    if (server == NULL || user == NULL || password == NULL)
    {
        printf("environment variables are not set.\n");
        exit(-1);
    }
    else
    {
    }
    /********************************************************* */

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

int add_gas_expense(char *datetime, double gallons, double price, char *address)
{
    char query[MAX_STRING];
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        exit(1);
    }

    snprintf(query, MAX_STRING, "INSERT INTO `expenses`.`gas_business` (`purshase_date`, `gallons`, `price_g`, `store_addr`) VALUES ('%s', '%.2f', '%.2f', '%s');", datetime, gallons, price, address);
    // printf(query);

    if (mysql_query(conn, query) == 0)
    {
        mysql_close(conn);
        return 0;
    }
    else
    {
        printf("Error: %s\n", mysql_error(conn));
        return 1;
    }
}
