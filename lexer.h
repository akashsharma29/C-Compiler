/**********************
Batch number 39
SAMISH BEDI 
2012B3A7735P
AKASH SHARMA
2012B2A7771P
**********************/

#ifndef LEXER_H
#define LEXER_H
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>

#include "lexerDef.h"

FILE *getStream(FILE *fp, int buffersize);
tokenInfo *createToken(char *token,char *lexeme,int lineNo,int colNo);
char *appendChartoString(char *s1, char c);
tokenInfo *getNextToken(FILE *fp);
lookupTable *createLookUpTable();
void lexer_main(char *testcaseFile);

#endif
