#include <stdio.h>
#include <regex.h>

int main() {
    regex_t regex;
    int reti;
    char msgbuf[100];

    // Compile regular expression
    reti = regcomp(&regex, "^[a-zA-Z]+$", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    // Execute regular expression
    reti = regexec(&regex, "HelloWorld", 0, NULL, 0);
    if (!reti) {
        puts("Match");
    } else if (reti == REG_NOMATCH) {
        puts("No match");
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return 1;
    }

    // Free compiled regular expression
    regfree(&regex);

    return 0;
}
