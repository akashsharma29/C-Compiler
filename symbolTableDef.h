/**********************
Batch number 39
SAMISH BEDI 
2012B3A7735P
AKASH SHARMA
2012B2A7771P
**********************/

#ifndef ST_DEF_H
#define ST_DEF_H

#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>
#define SIZE 50

//int nextTrack;
int off_track;
int error_flag;
int arithmetic_flag;
FILE *ASM;
int bool_no;
int cond_no;
int skip;
int itr_no;
int while_check;

typedef struct STNode{
	char *lexeme;
	char *type;
	char *scope;
	int offset;
	char *recordType;
	//int parameterType; //0 for input, 1 for output
	struct STElem *STnext;
	struct STNode *next;
	//struct STNode *prev;
}STNode;


typedef struct STElem
{
	STNode *head;
	int count;
}STElem;

typedef struct node{
	char *lexeme;
	struct node *next;
	struct node* nextL;
}node;

typedef struct list{
	node *head;
}list;

STElem globalTable[SIZE];

STElem recordTable[SIZE];

list outParTable[SIZE];

list inParTable[SIZE];


#endif
