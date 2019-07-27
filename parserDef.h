/**********************
Batch number 39
SAMISH BEDI 
2012B3A7735P
AKASH SHARMA
2012B2A7771P
**********************/

#ifndef PARSER_DEF_H
#define PARSER_DEF_H

#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>
#define NO_OF_RULES 92
#define NO_OF_SYMBOLS 106
#define NO_OF_NTS 51
#define NO_OF_TS 55

int pstcount;
int astcount;
int parsecount;
int visited[NO_OF_NTS]; 
int syntax_error;

//structures for Grammar:
//structure for RHS NT/T for grammar and sets
typedef struct ruleNode{
    int value;
    int isTerminal;
    struct ruleNode* next;
}ruleNode; 

//structure for LHS NT
typedef struct ruleArrayNode{
    int ruleNo;
    int NTvalue;
    ruleNode *rHead;
}ruleArrayNode;

//structure for storing grammar rules
typedef struct ruleArray{
    ruleArrayNode ruleArray[NO_OF_RULES];
}rule; 

rule *Rule; //initialize grammar rule structure

//structures for first/follow:

//structure for LHS
typedef struct setArrayNode{
    int Svalue;
    ruleNode *rHead;
}setArrayNode;

//structure for storing sets
typedef struct setArray{
    setArrayNode setArray[NO_OF_SYMBOLS];
}set;
set *firstSet; //initialize first set
set *followSet; //initialize follow set

int ParseTable[NO_OF_NTS][NO_OF_TS]; //Parse Table

//data structures for parse tree

typedef struct treeNode{
    char *lexemeCurrentNode; //The lexeme of the current node is printed when it is the leaf node else a dummy string of characters "----" is printed. 
    int lineNo; //The line number is the information collected by the lexical analyzer during single pass of the source code.
    char *token; //The token name corresponding to the current node 
    char *valueIfNumber; // If the lexeme is an integer or real number, then its value computed by the lexical analyzer is printed 
    char *parentNodeSymbol; //non terminal symbol of the parent node of the currently visited node
    int isLeafNode;
    char *nodeSymbol; //the symbol of the node being currently visited at the 7th place

    struct treeNode *child;
    struct treeNode *next;
    
    struct treeNode *ASTparent;
    struct treeNode *ASTchild;
    struct treeNode *ASTnext;

}treeNode;

typedef struct Tree{
    treeNode *root;
}parseTree;


//Stack for predictive parsing

typedef struct stack{
    treeNode* symbolValue[NO_OF_SYMBOLS];
    int size;
}Stack;


#endif
