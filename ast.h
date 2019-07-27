/**********************
Batch number 39
SAMISH BEDI 
2012B3A7735P
AKASH SHARMA
2012B2A7771P
**********************/

#ifndef AST_H
#define AST_H
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>

#include "parserDef.h"

int non_term_to_remove(char *non_terminal);
int term_to_remove(char *terminal);	
void createAST(treeNode *parent, treeNode *child);
void constructAST(parseTree *PT);
void printAST(treeNode *root);
void printAST(treeNode *root);
void countAST(treeNode *root);

#endif
