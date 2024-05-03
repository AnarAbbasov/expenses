 #ifndef SQLH
 #define SQLH
 #include <mysql/mysql.h>
 #endif
 #ifndef STDIOH
 #define STDIOH
 #include <stdio.h>
 #endif
 
 MYSQL *conn;
 //MYSQL_RES *res;
 //MYSQL_ROW row;

void freemysqlrsource(MYSQL_RES *res,MYSQL *conn)
{
mysql_free_result(res);
mysql_close(conn);
}

MYSQL_RES * sendquery(char * query){
    MYSQL_RES *res;
 char *server = "192.168.1.110";
 char *user = "root";
 char *password = "password"; // Replace with your actual password
 char *database = "expenses"; // Replace with your desired database name
 conn = mysql_init(NULL);
 // Connect to the database
 if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
     fprintf(stderr, "Error: %s\n", mysql_error(conn));
     exit(1);
 }
 // Execute an SQL query
 if (mysql_query(conn, query)) {
     fprintf(stderr, "Error: %s\n", mysql_error(conn));
     exit(1);
 }
 // Retrieve and print table names
 res = mysql_use_result(conn);
 return res;
}
