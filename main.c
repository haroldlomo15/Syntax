//
//  main.c
//  Syntax Analysis
//
//  Created by Harold  on 3/23/17.
//  Copyright © 2017 Harold . All rights reserved.
//



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int charClass;
int indexLine;
int lexLen;
int token;
int nxtToken;
size_t expression_length = 0;
ssize_t read_exression;
char lexeme [100];
char nextChar;
char endCharacter;
char * expression = NULL;
FILE *in_fp, *fopen();

//*** Function Declarations ***//
void addChar();
void getChar();
void getNonBlank();
int lex();
void getLine();
void addLine();
void expr();
void term();
void factor();
void error();

//*** Character Classes ***//
#define LETTER 0
#define DIGIT 1
#define NEWLINE 2
#define UNKNOWN 99

//*** Token Codes ***//
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("No file given at function call.... \n");
        exit(0);
    }
    if ((in_fp = fopen(argv[1], "r")) == NULL)
        printf("ERROR - cannot open front.in \n");
    else {
        while ((read_exression = getline(&expression, &expression_length, in_fp)) != EOF) {
            indexLine = 0;
            getChar();
            if (expression != NULL) {
                do {
                    lex();
                    expr();
                } while (nxtToken != EOF);
            }
        }
    }
}

int lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            nxtToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nxtToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nxtToken = ADD_OP;
            break;
        case '-':
            addChar();
            nxtToken = SUB_OP;
            break;
        case '*':
            addChar();
            nxtToken = MULT_OP;
            break;
        case '/':
            addChar();
            nxtToken = DIV_OP;
            break;
        default:
            addChar();
            nxtToken = EOF;
            break;
    }
    return nxtToken;
}

void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else
        printf("Error - lexeme is too long \n");
}

void getChar() {
    if (expression[indexLine] != '\n' && expression[indexLine] != '\0') {
        nextChar = expression[indexLine++];
        if (isalpha(nextChar)) {
            charClass = LETTER;
        }
        else if (isdigit(nextChar)) {
            charClass = DIGIT;
        }
        else if (nextChar == '\n')
            charClass = NEWLINE;
        else charClass = UNKNOWN;
    }
    else
        charClass = EOF;
}

void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

int lex() {
    lexLen = 0;
    getNonBlank();
    endCharacter = nextChar;
    switch (charClass) {
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nxtToken = IDENT;
            break;
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nxtToken = INT_LIT;
            break;
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;
        case EOF:
            nxtToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    }
    printf("Next token is: %d, Next lexeme is %s\n",
           nxtToken, lexeme);
    return nxtToken;
}

void expr() {
    printf("Enter <expr>\n");
    term();
    while (nxtToken == ADD_OP || nxtToken == SUB_OP) {
        lex();
        term();
    }
    printf("Exit <expr>\n");
}

void term() {
    printf("Enter <term>\n");
    factor();
    while (nxtToken == MULT_OP || nxtToken == DIV_OP) {
        lex();
        factor();
    }
    printf("Exit <term>\n");
}
