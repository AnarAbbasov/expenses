 #ifndef SQLH
 #define SQLH
 #include <mysql/mysql.h>
 #endif
 #ifndef STDIOH
 #define STDIOH
 #include <stdio.h>
 #endif
 
 MYSQL *conn;
 MYSQL_RES *res;
 MYSQL_ROW row;

MYSQL_RES * sendquery(char * query){
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
 if (mysql_query(conn, "SHOW TABLES")) {
     fprintf(stderr, "Error: %s\n", mysql_error(conn));
     exit(1);
 }
 // Retrieve and print table names
 res = mysql_use_result(conn);
 printf("MySQL Tables in %s database:\n", database);
 while ((row = mysql_fetch_row(res)) != NULL) {
     printf("%s\n", row[0]);
 }
 // Clean up
 mysql_free_result(res);
 mysql_close(conn);
 return 0;
}
