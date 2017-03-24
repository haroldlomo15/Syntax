//
//  main.c
//  Syntax Analysis
//
//  Created by Harold  on 3/23/17.
//  Copyright © 2017 Harold . All rights reserved.
//


#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme [100];
char previouslexeme [100];
char errorstring[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();
char * expression = NULL;
size_t len = 0;
ssize_t read;
int current;
int temp;


