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
int nextToken;
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
                } while (nextToken != EOF);
            }
        }
    }
}

int lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        default:
            addChar();
            nextToken = EOF;
            break;
    }
    return nextToken;
}

void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else
        printf("Error - lexeme is too long \n");
}
