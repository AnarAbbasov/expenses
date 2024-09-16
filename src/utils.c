
#include "../include/utils.h"
#include "string.h"




void make_insert_data(char* Date,char * gallons,char * price,char * address)
{

sql_insert_data.Date=Date;
sql_insert_data.gallons=atof(gallons);
sql_insert_data.price=atof(price);
sql_insert_data.address=address;

}


void trimTrailing(char *str) {
    int index, i;

    // Set default index
    index = -1;

    // Find last index of non-white space character
    i = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            index = i;
        }
        i++;
    }

    // Mark next character to last non-white space character as NULL
    str[index + 1] = '\0';
}


int validate_datetime(char *field_value) {
    trimTrailing(field_value);
    regex_t regex;
    int reti;
    char msgbuf[100];
    regmatch_t pmatch[1]; // Array to store match information

    // Compile regular expression
    reti = regcomp(&regex,"^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 5;
    }

    

    // Execute regular expression
    reti = regexec(&regex, field_value, 1, pmatch, 0); // Pass pmatch array
    if (!reti) {
        return 0;
    } else if (reti == REG_NOMATCH) {
        return 1;
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 2;
    }

    // Free compiled regular expression
    regfree(&regex);

    return 0;
}




int validate_number(char *field_value) {
    trimTrailing(field_value);
    regex_t regex;
    int reti;
    char msgbuf[100];
    regmatch_t pmatch[1]; // Array to store match information

    // Compile regular expression
    reti = regcomp(&regex,"^[0-9]+(\\.[0-9]+)?$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 5;
    }

    // Execute regular expression
    reti = regexec(&regex, field_value, 1, pmatch, 0); // Pass pmatch array
    if (!reti) {
        return 0;
    } else if (reti == REG_NOMATCH) {
        return 1;
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 2;
    }

    // Free compiled regular expression
    regfree(&regex);

    return 0;
}
