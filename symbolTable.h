/**********************
Batch number 39
SAMISH BEDI 
2012B3A7735P
AKASH SHARMA
2012B2A7771P
**********************/

#ifndef ST_H
#define ST_H
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>

#include "symbolTableDef.h"

STElem* initialize_table(int size);
STNode *create_STnode(char *lexeme, char *type, char *scope, int offset,STNode *next);
int hash_key(char *name);
char* checkID(treeNode *AST,char *function_name);
void check_arithmetic(treeNode *AST,char* type_LHS,char *function_name,int type_check);
void check_boolean(treeNode *AST,char *function_name);
char* getSTNodetype(char* name,char *function_name);
char* check_termPrime(treeNode *AST,char *type_LHS,char *function_name,int lineNo);
char *check_factor(treeNode *AST,char *type_LHS,char *function_name,int lineNo);
char* check_term(treeNode *AST,char *type_LHS,char *function_name,int lineNo);
char* check_expPrime(treeNode *AST,char *type_LHS,char *function_name,int lineNo);
char *check_type_arithmetic(treeNode *AST,char *type_LHS,char *function_name,int lineNo);
STElem *fill_function_table(treeNode *AST,STElem *Table,char *function_name,int offset);
void create_ParTable(treeNode *AST,char* function_name);
void create_ST(treeNode *AST);
void printST(STElem *Table);
void printRecord(STElem *Table);
void create_recordTypes(treeNode *AST);
void create_GTvar(treeNode *AST);
void printpar(list *Table);
void ST_main(parseTree *PT);

#endif
