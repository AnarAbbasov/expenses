#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct i_data{
    char * Date;
    double gallons;
    double price;
    char * address;

}data_to_insert;

data_to_insert  sql_insert_data;


int validate_datetime(char * field_value);
int validate_number(char *field_value) ;
void make_insert_data(char* Date,char * gallons,char * price,char * address);




