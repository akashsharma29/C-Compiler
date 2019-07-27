/**********************
Batch number 39
SAMISH BEDI 
2012B3A7735P
AKASH SHARMA
2012B2A7771P
**********************/

#ifndef LEXER_DEF_H
#define LEXER_DEF_H
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>
#define BUFFER_SIZE 4096 //size of buffer
#define NO_OF_KEYS 26 //size of hashtable

//Defines a token
typedef struct tokenInfo{
  char *token;
  int lineNo;
  int colNo;
  char *lexeme;
}tokenInfo;

//linked list of elements corresponding to a key of hashtable
typedef struct lookupNode{
  char *lexeme;
  char *token;
  struct lookupNode *next;
}lookupNode;

//Element of lookup table
typedef struct lookupElem{
  lookupNode *head;
  int count;
}lookupElem;

//Lookup table structure
typedef struct lookupTable{
  lookupElem table[NO_OF_KEYS];
}lookupTable;

char Buffer[BUFFER_SIZE]; //Buffer
int bufferPointer; //buffer pointer
lookupTable *lookUp; //lookup table
int lineNo; //line number of code
int colNo; //(optional) column number
FILE *F; //pointer of code file being read
int bufferCnt; //Number of elements in buffer
#endif
