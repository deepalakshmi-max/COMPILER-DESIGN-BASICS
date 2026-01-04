#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 50

/* List of keywords */
char keywords[][10] = {
    "int", "float", "char", "double",
    "if", "else", "for", "while",
    "return", "void"
};

/* Function to check whether a string is a keyword */
int isKeyword(char word[]) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    FILE *fp;
    char ch, token[MAX];
    int i = 0;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error: Cannot open input file.\n");
        return 1;
    }

    printf("----- LEXICAL ANALYZER OUTPUT -----\n\n");

    while ((ch = fgetc(fp)) != EOF) {

        /* Operators */
        if (ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '=' || ch == '<' || ch == '>') {
            printf("Operator   : %c\n", ch);
        }

        /* Collect identifiers / keywords / numbers */
        else if (isalnum(ch)) {
            token[i++] = ch;
        }

        /* End of token */
        else if ((ch == ' ' || ch == '\n' || ch == ';' || ch == '\t') && i > 0) {
            token[i] = '\0';

            if (isKeyword(token))
                printf("Keyword    : %s\n", token);
            else if (isdigit(token[0]))
                printf("Number     : %s\n", token);
            else
                printf("Identifier : %s\n", token);

            i = 0;
        }
    }

    fclose(fp);
    return 0;
}
