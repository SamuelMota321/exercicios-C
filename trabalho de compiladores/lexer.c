#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *keywords[] = {"program", "var", "integer", "real", "begin", "end", "if", "then", "else", "while", "do"};
int num_keywords = 11;

typedef enum {
    ID, NUM_INT, NUM_FLT, PAL_RES, OP_EQ, OP_GE, OP_MUL, OP_NE, OP_LE, OP_DIV, OP_GT, OP_AD, OP_ASS, OP_LT, OP_MIN,
    SMB_OBC, SMB_COM, SMB_CBC, SMB_SEM, SMB_OPA, SMB_CPA, UNKNOWN, END_OF_FILE
} TokenType;

typedef struct {
    TokenType type;
    char value[100];
} Token;

int is_keyword(char *word) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

Token next_token(FILE *file) {
    Token token;
    char ch;
    int i = 0;

    do {
        ch = fgetc(file);
    } while (isspace(ch));

    if (ch == EOF) {
        token.type = END_OF_FILE;
        strcpy(token.value, "EOF");
        return token;
    }

    if (isalpha(ch)) {
        while (isalnum(ch)) {
            token.value[i++] = ch;
            ch = fgetc(file);
        }
        token.value[i] = '\0';
        ungetc(ch, file);  

        if (is_keyword(token.value)) {
            token.type = PAL_RES;
        } else {
            token.type = ID;
        }
        return token;
    }

    if (isdigit(ch)) {
        int is_float = 0;
        while (isdigit(ch)) {
            token.value[i++] = ch;
            ch = fgetc(file);
        }
        if (ch == '.') {
            is_float = 1;
            token.value[i++] = ch;
            ch = fgetc(file);
            while (isdigit(ch)) {
                token.value[i++] = ch;
                ch = fgetc(file);
            }
        }
        token.value[i] = '\0';
        ungetc(ch, file);  

        token.type = is_float ? NUM_FLT : NUM_INT;
        return token;
    }

    switch (ch) {
        case '=':
            ch = fgetc(file);
            if (ch == '=') {
                strcpy(token.value, "=");
                token.type = OP_ASS;
            } else {
                strcpy(token.value, "=");
                token.type = OP_EQ;
                ungetc(ch, file); 
            }
            break;
        case '>':
            ch = fgetc(file);
            if (ch == '=') {
                strcpy(token.value, ">=");
                token.type = OP_GE;
            } else {
                strcpy(token.value, ">");
                token.type = OP_GT;
                ungetc(ch, file);
            }
            break;
        case '<':
            ch = fgetc(file);
            if (ch == '=') {
                strcpy(token.value, "<=");
                token.type = OP_LE;
            } else if (ch == '>') {
                strcpy(token.value, "<>");
                token.type = OP_NE;
            } else {
                strcpy(token.value, "<");
                token.type = OP_LT;
                ungetc(ch, file);
            }
            break;
        case '+':
            strcpy(token.value, "+");
            token.type = OP_AD;
            break;
        case '-':
            strcpy(token.value, "-");
            token.type = OP_MIN;
            break;
        case '*':
            strcpy(token.value, "*");
            token.type = OP_MUL;
            break;
        case '/':
            strcpy(token.value, "/");
            token.type = OP_DIV;
            break;
        case '{':
            strcpy(token.value, "{");
            token.type = SMB_OBC;
            break;
        case '}':
            strcpy(token.value, "}");
            token.type = SMB_CBC;
            break;
        case ',':
            strcpy(token.value, ",");
            token.type = SMB_COM;
            break;
        case ';':
            strcpy(token.value, ";");
            token.type = SMB_SEM;
            break;
        case '(':
            strcpy(token.value, "(");
            token.type = SMB_OPA;
            break;
        case ')':
            strcpy(token.value, ")");
            token.type = SMB_CPA;
            break;
        default:
            token.value[0] = ch;
            token.value[1] = '\0';
            token.type = UNKNOWN;
            break;
    }

    return token;
}

void print_token(Token token) {
    switch (token.type) {
        case ID:
            printf("ID: %s\n", token.value);
            break;
        case NUM_INT:
            printf("NUM_INT: %s\n", token.value);
            break;
        case NUM_FLT:
            printf("NUM_FLT: %s\n", token.value);
            break;
        case PAL_RES:
            printf("PAL-RES: %s\n", token.value);
            break;
        case OP_EQ:
            printf("OP_EQ: %s\n", token.value);
            break;
        case OP_GE:
            printf("OP_GE: %s\n", token.value);
            break;
        case OP_MUL:
            printf("OP_MUL: %s\n", token.value);
            break;
        case OP_NE:
            printf("OP_NE: %s\n", token.value);
            break;
        case OP_LE:
            printf("OP_LE: %s\n", token.value);
            break;
        case OP_DIV:
            printf("OP_DIV: %s\n", token.value);
            break;
        case OP_GT:
            printf("OP_GT: %s\n", token.value);
            break;
        case OP_AD:
            printf("OP_AD: %s\n", token.value);
            break;
        case OP_ASS:
            printf("OP_ASS: %s\n", token.value);
            break;
        case OP_LT:
            printf("OP_LT: %s\n", token.value);
            break;
        case OP_MIN:
            printf("OP_MIN: %s\n", token.value);
            break;
        case SMB_OBC:
            printf("SMB_OBC: %s\n", token.value);
            break;
        case SMB_COM:
            printf("SMB_COM: %s\n", token.value);
            break;
        case SMB_CBC:
            printf("SMB_CBC: %s\n", token.value);
            break;
        case SMB_SEM:
            printf("SMB_SEM: %s\n", token.value);
            break;
        case SMB_OPA:
            printf("SMB_OPA: %s\n", token.value);
            break;
        case SMB_CPA:
            printf("SMB_CPA: %s\n", token.value);
            break;
        case UNKNOWN:
            printf("UNKNOWN: %s\n", token.value);
            break;
        case END_OF_FILE:
            printf("EOF\n");
            break;
    }
}

int main() {
    FILE *file = fopen("code.pas", "r");

    if (!file) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    Token token;
    do {
        token = next_token(file);
        print_token(token);
    } while (token.type != END_OF_FILE);

    fclose(file);
    return 0;
}
