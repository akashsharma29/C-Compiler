/**********************
Batch number 39
SAMISH BEDI 
2012B3A7735P
AKASH SHARMA
2012B2A7771P
**********************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "parserDef.h"
#include "symbolTable.h"
#include "symbolTableDef.h"

//Initializes the data structure for symbol table.
STElem* initialize_table(int size){
	STElem *table = (STElem *)malloc(sizeof(STElem)*size);
	int i=0;
	for(i=0;i<size;i++){
		table[i].head=NULL;
		table[i].count=0;
	}
	
	return table;	
}

//Creates a symbol table node.
STNode *create_STnode(char *lexeme, char *type, char *scope, int offset,STNode *next){
	STNode *node = (STNode *) malloc(sizeof(STNode));
	
	node->lexeme=lexeme;

	node->type=type;
	node->scope=scope;
	node->offset=offset;
	node->STnext=NULL;
	node->next=next;
	node->recordType="";

	return node;
	
}

//Hash Function
int hash_key(char *name){
	int i;
	int key=0;
	for(i=0;i<strlen(name);i++){
		key+=(int)name[i];
	}
	
	return key%SIZE;
}

//returns the Identifier's type.   
char* checkID(treeNode *AST,char *function_name){
	char *type="";
	
	char *record="";
	if(strcmp(AST->nodeSymbol,"TK_ID")==0){
		
		
		int global_flag=0;
		int function_flag=0;

		STNode* temp=globalTable[hash_key(AST->lexemeCurrentNode)].head;
		while(temp!=NULL){
			if(strcmp(temp->lexeme,AST->lexemeCurrentNode)==0){
				type=temp->type;
				record=temp->recordType;
				global_flag=1;
				break;
			}
			temp=temp->next;
								
		}

		temp=globalTable[hash_key(function_name)].head;
		while(temp!=NULL){
			if(strcmp(temp->lexeme,function_name)==0){
				STNode *temp1=(temp->STnext)[hash_key(AST->lexemeCurrentNode)].head;
				while(temp1!=NULL){
					if(strcmp(temp1->lexeme,AST->lexemeCurrentNode)==0){
						if(strcmp(type,"")==0){
							type=temp1->type;
							record=temp1->recordType;
						}
						function_flag=1;
						break;
					}
					temp1=temp1->next;

				}
				break;
			}
			temp=temp->next;
		}		
		
		if(global_flag==0 && function_flag==0){
		error_flag=1;
		printf("Line %d: varaible <%s> is not declared.\n",AST->lineNo,AST->lexemeCurrentNode);
		return "";
			}
		else{

			if(AST->ASTnext!=NULL && strcmp(AST->ASTnext->nodeSymbol,"TK_FIELDID")==0 && strcmp(record,"")!=0){

				temp=recordTable[hash_key(record)].head;
				while(temp!=NULL){
					if(strcmp(temp->lexeme,record)==0){
						STNode *temp1=(temp->STnext)[hash_key(AST->ASTnext->lexemeCurrentNode)].head;
						while(temp1!=NULL){
							if(strcmp(temp1->lexeme,AST->ASTnext->lexemeCurrentNode)==0){
								
									type=temp1->type;
									record=temp1->recordType;
									
								break;
							}
							temp1=temp1->next;

						}
						break;
					}
					temp=temp->next;
				} 
		
			}
		}
		
		
	}else if(strcmp(AST->nodeSymbol,"TK_NUM")==0){
		type="int";
	}else if(strcmp(AST->nodeSymbol,"TK_RNUM")==0){
		type="real";
	}
	
					
	return type;

}


//Function to check the type of all variables except records.
void check_arithmetic(treeNode *AST,char* type_LHS,char *function_name,int type_check){
	if(AST==NULL) return;
	
	if(!type_check){
		if(strcmp("TK_ID",AST->nodeSymbol)==0){
			checkID(AST,function_name);
		}
	}else{
		if(strcmp("TK_ID",AST->nodeSymbol)==0){
			char* type_RHS=checkID(AST,function_name);
			if(strcmp(type_RHS,"")!=0){
				if(strcmp(type_RHS,type_LHS)!=0){
error_flag=1;					
printf("Line %d: Type Mismatch <%s,%s>. Type should be %s.\n",AST->lineNo,AST->lexemeCurrentNode,type_RHS,type_LHS);
				}
			}
	
		}else if(strcmp("TK_NUM",AST->nodeSymbol)==0){
			char* type_RHS="int";
			if(strcmp(type_RHS,type_LHS)!=0){
					printf("Line %d: Type Mismatch <%s,%s>. Type should be %s.\n",AST->lineNo,AST->lexemeCurrentNode,type_RHS,type_LHS);
			}	
		}else if(strcmp("TK_RNUM",AST->nodeSymbol)==0){
			char* type_RHS="real";
			if(strcmp(type_RHS,type_LHS)!=0){
error_flag=1;					
printf("Line %d: Type Mismatch <%s,%s>. Type should be %s.\n",AST->lineNo,AST->lexemeCurrentNode,type_RHS,type_LHS);
			}	
		}
	}

	check_arithmetic(AST->ASTchild,type_LHS,function_name,type_check);
	check_arithmetic(AST->ASTnext,type_LHS,function_name,type_check);
}

//Type checking of boolean expressions.
void check_boolean(treeNode *AST,char *function_name){
	if(AST==NULL) return;
	
	char* type_RHS;
	char* type_LHS;
	int var_flag=0;

	if(strcmp("TK_ID",AST->nodeSymbol)==0 && strcmp("<var>",AST->ASTparent->nodeSymbol)==0 && AST->ASTparent->ASTnext!=NULL && strcmp("<relationalOp>",AST->ASTparent->ASTnext->nodeSymbol)==0){

			type_LHS=checkID(AST,function_name);
			var_flag=1;
		}else if(strcmp("TK_NUM",AST->nodeSymbol)==0 && strcmp("<var>",AST->ASTparent->nodeSymbol)==0&& AST->ASTparent->ASTnext!=NULL&&strcmp("<relationalOp>",AST->ASTparent->ASTnext->nodeSymbol)==0){
					type_LHS="int";
					var_flag=1;			
		}else if(strcmp("TK_RNUM",AST->nodeSymbol)==0 && strcmp("<var>",AST->ASTparent->nodeSymbol)==0&& AST->ASTparent->ASTnext!=NULL&&strcmp("<relationalOp>",AST->ASTparent->ASTnext->nodeSymbol)==0){
					type_LHS="real";
					var_flag=1;
		}

		if(var_flag==1 && strcmp(type_LHS,"")!=0){
				if(strcmp(AST->ASTparent->ASTnext->nodeSymbol,"<relationalOp>")==0){

					if(strcmp(AST->ASTparent->ASTnext->ASTnext->ASTchild->nodeSymbol,"TK_ID")==0){
										
						type_RHS=checkID(AST->ASTparent->ASTnext->ASTnext->ASTchild,function_name);

					}else if(strcmp("TK_NUM",AST->ASTparent->ASTnext->ASTnext->ASTchild->nodeSymbol)==0){
							type_RHS="int";

					}else if(strcmp("TK_RNUM",AST->ASTparent->ASTnext->ASTnext->ASTchild->nodeSymbol)==0){
						type_RHS="real";
				}
						if(strcmp(type_RHS,"")!=0 && strcmp(type_RHS,type_LHS)!=0){
error_flag=1;							
printf("Line %d: Boolean Type Mismatch <%s,%s> and <%s,%s>.\n",AST->lineNo,AST->lexemeCurrentNode,type_LHS,AST->ASTparent->ASTnext->ASTnext->ASTchild->lexemeCurrentNode,type_RHS);
						}
					
				}
			}else if(var_flag==1){
				checkID(AST->ASTparent->ASTnext->ASTnext->ASTchild,function_name);
			}

	check_boolean(AST->ASTchild,function_name);
	check_boolean(AST->ASTnext,function_name);
}

//Extracts the node type of symbol table.
char* getSTNodetype(char* name,char *function_name){
	if(globalTable[hash_key(name)].head!=NULL){
		STNode* temp=globalTable[hash_key(name)].head;
		while(temp!=NULL){
			if(strcmp(temp->lexeme,name)==0){
						return temp->type;
						break;
					}
			temp=temp->next;
		}
	}else{
	STNode* temp=globalTable[hash_key(function_name)].head;
		while(temp!=NULL){
			if(strcmp(temp->lexeme,function_name)==0){
				STNode* temp1=(temp->STnext)[hash_key(name)].head;
				while(temp1!=NULL){
					if(strcmp(temp1->lexeme,name)==0){
						return temp1->type;
						break;
					}
					temp1=temp1->next;

				}
				break;
			}
			temp=temp->next;
		}
		}
	return "";		

}

//Evaluates the type of <termPrime> in calculation of arithmetic expression.
char* check_termPrime(treeNode *AST,char *type_LHS,char *function_name,int lineNo){
	char *type_RHS;
	char *type1;
	char *type2;
	
	type1=check_factor(AST->ASTchild->ASTnext,type_LHS,function_name,lineNo); //ID
	if(AST->ASTchild->ASTnext->ASTnext!=NULL){
		type2=check_termPrime(AST->ASTchild->ASTnext->ASTnext,type_LHS,function_name,lineNo);
		if(strcmp(type1,type2)==0){
			type_RHS=type1;
			if(strlen(type1)>5){
				error_flag=1;
				printf("Line %d: Records cannot be operated with high precedence operators.\n",lineNo);
				}
		}else{
						
			if(strlen(type1)>5 && strlen(type2)<5){
				type_RHS=type1;
			}else if((strlen(type1)<5 && strlen(type2)>5) && strcmp(AST->ASTchild->ASTnext->ASTchild->nodeSymbol,"TK_MUL")==0){

				type_RHS=type2;
			}else{
				error_flag=1;
				printf("Line %d: Type Mismatch in record operations.\n",lineNo);
				type_RHS="";
			}
		}
	}else{
		type_RHS=type1;
	}
		
	return type_RHS;
}

//Evaluates the type of <factor> in calculation of arithmetic expression.
char *check_factor(treeNode *AST,char *type_LHS,char *function_name,int lineNo){
	char *type_RHS;
		
	if(AST->ASTchild!=NULL){
	if(strcmp(AST->ASTchild->nodeSymbol,"<arithmeticExpression>")!=0){
		type_RHS=checkID(AST->ASTchild,function_name); 

	}else{
		type_RHS=check_type_arithmetic(AST->ASTchild,type_LHS,function_name,lineNo);
	}
	
	}
	return type_RHS;
}

//Evaluates the type of <term> in calculation of arithmetic expression.
char* check_term(treeNode *AST,char *type_LHS,char *function_name,int lineNo){
	char *type_RHS;
	char *type1;
	char *type2;
	
	type1=check_factor(AST->ASTchild,type_LHS,function_name,lineNo); 

	if(AST->ASTchild->ASTnext!=NULL){

		type2=check_termPrime(AST->ASTchild->ASTnext,type_LHS,function_name,lineNo);
						
		if(strcmp(type1,type2)==0){
			type_RHS=type1;
			if(strlen(type1)>5){
				error_flag=1;
				printf("Line %d: Records cannot be operated with high precedence operators.\n",lineNo);
				}
		}else{
						
			if(strlen(type1)>5 && strlen(type2)<5){
				type_RHS=type1;
			}else if((strlen(type1)<5 && strlen(type2)>5) && strcmp(AST->ASTchild->ASTnext->ASTchild->nodeSymbol,"TK_MUL")==0){

				type_RHS=type2;
			}else{
				error_flag=1;
				printf("Line %d: Type Mismatch in record operations.\n",lineNo);
				type_RHS="";
			}
		}
	}else{
		type_RHS=type1;
	}
	return type_RHS;
}

//Evaluates the type of <expPrime> in calculation of arithmetic expression.
char* check_expPrime(treeNode *AST,char *type_LHS,char *function_name,int lineNo){
	char *type_RHS;
	char *type1;
	char *type2;
	
	type1=check_term(AST->ASTchild->ASTnext,type_LHS,function_name,lineNo);
	if(AST->ASTchild->ASTnext->ASTnext!=NULL){
		type2=check_expPrime(AST->ASTchild->ASTnext->ASTnext,type_LHS,function_name,lineNo);
		if(strcmp(type1,type2)==0){
			error_flag=1;			
			printf("Line %d: Type Mismatch in record operations.\n",lineNo);
			type_RHS=type1;
		}else{
			type_RHS="";
		}
	}else{
		type_RHS=type1;
	}
	return type_RHS;
}

//Function to check the arithmetic expression that involves record variables.
char *check_type_arithmetic(treeNode *AST,char *type_LHS,char *function_name,int lineNo){
	char *type_RHS;
	char *type1;
	char *type2;
	
	type1=check_term(AST->ASTchild,type_LHS,function_name,lineNo);
	if(AST->ASTchild->ASTnext!=NULL){
		type2=check_expPrime(AST->ASTchild->ASTnext,type_LHS,function_name,lineNo);
		if(strcmp(type1,type2)==0){
			type_RHS=type1;
		}else{
			error_flag=1;
			printf("Line %d: Type Mismatch in record operations.\n",lineNo);
			type_RHS="";
		}
	}else{
		type_RHS=type1;
	}
	//printf("%s %s\n\n",type_RHS,AST->ASTchild->lexemeCurrentNode);
	return type_RHS;
}

//Function to fill the function table.
STElem *fill_function_table(treeNode *AST,STElem *Table,char *function_name,int offset){

	if(AST==NULL) return Table;
	char *scope;
	offset=off_track;
	int offset_t=offset;

	if(strcmp(AST->nodeSymbol,"TK_INT")==0){
		if(AST->ASTnext!=NULL && strcmp(AST->ASTnext->nodeSymbol,"TK_ID")==0){
			
			if(AST->ASTnext->ASTnext!=NULL && strcmp(AST->ASTnext->ASTnext->nodeSymbol,"TK_GLOBAL")==0){
				
			}else{
				offset_t=offset;
				scope = function_name;
				offset+=2;
				off_track=offset;
				int flag=0;
				int g_flag=0;
				
				STNode *temp_g=globalTable[hash_key(AST->ASTnext->lexemeCurrentNode)].head;
				if(temp_g!=NULL){
		
					STNode *temp1=temp_g;
					while(temp1!=NULL){
						if(strcmp(temp1->lexeme,AST->ASTnext->lexemeCurrentNode)==0){			
								error_flag=1;
								g_flag=1;
								break;
							}
							temp1=temp1->next;
						}
				}
				
				if(g_flag==0){
				STNode *temp=Table[hash_key(AST->ASTnext->lexemeCurrentNode)].head;
				if(temp==NULL){
				Table[hash_key(AST->ASTnext->lexemeCurrentNode)].head=create_STnode(AST->ASTnext->lexemeCurrentNode, AST->lexemeCurrentNode,scope,offset_t,temp);
				}else{
						STNode *temp1=temp;
						while(temp1!=NULL){
							if(strcmp(temp1->lexeme,AST->ASTnext->lexemeCurrentNode)==0){			
								error_flag=1;
								flag=1;
								break;
							}
							temp1=temp1->next;
						}
				}
				if(flag==0){
//						int type;
						Table[hash_key(AST->ASTnext->lexemeCurrentNode)].head=create_STnode(AST->ASTnext->lexemeCurrentNode, AST->lexemeCurrentNode,scope,offset_t,temp);
							
							 							
				}else{
					offset-=2;
					off_track=offset;
					error_flag=1;
error_flag=1;					
printf("Line %d: The identifier <%s> is declared more than once.\n",AST->ASTnext->lineNo,AST->ASTnext->lexemeCurrentNode);
				}
			}else{
				error_flag=1;
error_flag=1;				
printf("Line %d: Variable <%s> is a global variable and cannot be declared again.\n",AST->ASTnext->lineNo,AST->ASTnext->lexemeCurrentNode);
			}
			
			}
		}
	}
	else if(strcmp(AST->nodeSymbol,"TK_RECORDID")==0 && (strcmp(AST->ASTparent->nodeSymbol,"<parameter_list>")==0 || strcmp(AST->ASTparent->nodeSymbol,"<declaration>")==0)){
	

				int size=0;
				char *type="";

		if(AST->ASTnext!=NULL && strcmp(AST->ASTnext->nodeSymbol,"TK_ID")==0){
		
		if(AST->ASTnext->ASTnext!=NULL && strcmp(AST->ASTnext->ASTnext->nodeSymbol,"TK_GLOBAL")==0){
				
			}else{
						
				if(recordTable[hash_key(AST->lexemeCurrentNode)].head!=NULL){

					STNode *temp=recordTable[hash_key(AST->lexemeCurrentNode)].head;

					while(strcmp(temp->lexeme,AST->lexemeCurrentNode)!=0){

						temp=temp->next;
					}
					STElem* record=temp->STnext;
					
					int i=0;
					for(i=0;i<SIZE;i++){
						if(record[i].head!=NULL){
							STNode *temp_1=record[i].head;
							
						
							while(temp_1!=NULL){

								if(strcmp(temp_1->type,"int")==0) {
									int len=strlen(type);
									char* type1=(char *)malloc((len+4)*sizeof(char));
									strcpy(type1,type);  
									strcat(type1,"int x ");
									type=type1;

									size+=2;
								}
								else if(strcmp(temp_1->type,"real")==0) {
								
									int len=strlen(type);
									char* type1=(char *)malloc((len+7)*sizeof(char));
									strcpy(type1,type);  
									strcat(type1,"real x ");
									type=type1;
									
									size+=4;
								}
								
								temp_1=temp_1->next;
																
							}
						}
					}
					
				}
				char *type_t=(char *)malloc((strlen(type)-3)*sizeof(char));
				strncpy(type_t,type,strlen(type)-3);
				type=type_t;
				offset_t=offset;
				scope = function_name;
				offset=offset+size;
				off_track=offset;
				int flag=0;
				int g_flag=0;
				
				STNode *temp_g=globalTable[hash_key(AST->ASTnext->lexemeCurrentNode)].head;
				if(temp_g!=NULL){
		
					STNode *temp1=temp_g;
					while(temp1!=NULL){
						if(strcmp(temp1->lexeme,AST->ASTnext->lexemeCurrentNode)==0){			
								error_flag=1;
								g_flag=1;
								break;
							}
							temp1=temp1->next;
						}
				}
				
				if(g_flag==0){
				STNode *temp=Table[hash_key(AST->ASTnext->lexemeCurrentNode)].head;
				if(temp==NULL){
				Table[hash_key(AST->ASTnext->lexemeCurrentNode)].head=create_STnode(AST->ASTnext->lexemeCurrentNode, type,scope,offset_t,temp);
				}else{
						STNode *temp1=temp;
						while(temp1!=NULL){
							if(strcmp(temp1->lexeme,AST->ASTnext->lexemeCurrentNode)==0){			
								error_flag=1;
								flag=1;
								break;
							}
							temp1=temp1->next;
						}
				}
				if(flag==0){

						Table[hash_key(AST->ASTnext->lexemeCurrentNode)].head=create_STnode(AST->ASTnext->lexemeCurrentNode, type,scope,offset_t,temp);
						Table[hash_key(AST->ASTnext->lexemeCurrentNode)].head->recordType=AST->lexemeCurrentNode;
					
				}else{
					offset-=2;
					off_track=offset;
					error_flag=1;
error_flag=1;					
printf("Line %d: The identifier <%s> is declared more than once.\n",AST->ASTnext->lineNo,AST->ASTnext->lexemeCurrentNode);
				}
			}else{
				error_flag=1;
error_flag=1;				
printf("Line %d: Variable <%s> is a global variable and cannot be declared again.\n",AST->ASTnext->lineNo,AST->ASTnext->lexemeCurrentNode);
			}	
			}
		} 
	}else if(strcmp(AST->nodeSymbol,"TK_REAL")==0){
		if(AST->ASTnext!=NULL && strcmp(AST->ASTnext->nodeSymbol,"TK_ID")==0){
			
			if(AST->ASTnext->ASTnext!=NULL && strcmp(AST->ASTnext->ASTnext->nodeSymbol,"TK_GLOBAL")==0){
				
			}else{
				offset_t=offset;
				scope = function_name;
				offset+=4;
				off_track=offset;
				int flag=0;
				int g_flag=0;
				
				STNode *temp_g=globalTable[hash_key(AST->ASTnext->lexemeCurrentNode)].head;
				if(temp_g!=NULL){
		
					STNode *temp1=temp_g;
					while(temp1!=NULL){
						if(strcmp(temp1->lexeme,AST->ASTnext->lexemeCurrentNode)==0){			
								error_flag=1;
								g_flag=1;
								break;
							}
							temp1=temp1->next;
						}
				}
				
				if(g_flag==0){
				STNode *temp=Table[hash_key(AST->ASTnext->lexemeCurrentNode)].head;
				if(temp==NULL){
				Table[hash_key(AST->ASTnext->lexemeCurrentNode)].head=create_STnode(AST->ASTnext->lexemeCurrentNode, AST->lexemeCurrentNode,scope,offset_t,temp);
				}else{
						STNode *temp1=temp;
						while(temp1!=NULL){
							if(strcmp(temp1->lexeme,AST->ASTnext->lexemeCurrentNode)==0){			
								error_flag=1;
								flag=1;
								break;
							}
							temp1=temp1->next;
						}
				}
				if(flag==0){
//						int type;
						Table[hash_key(AST->ASTnext->lexemeCurrentNode)].head=create_STnode(AST->ASTnext->lexemeCurrentNode, AST->lexemeCurrentNode,scope,offset_t,temp);
							 							
				}else{
					offset-=4;
					off_track=offset;
					error_flag=1;
error_flag=1;					
printf("Line %d: The identifier <%s> is declared more than once.\n",AST->ASTnext->lineNo,AST->ASTnext->lexemeCurrentNode);
				}
			}else{
				error_flag=1;
error_flag=1;				
printf("Line %d: Variable <%s> is a global variable and cannot be declared again.\n",AST->ASTnext->lineNo,AST->ASTnext->lexemeCurrentNode);
			}
			
			}
		}
	}else if(strcmp(AST->nodeSymbol,"TK_FUNID")==0){			
		if(strcmp(function_name,AST->lexemeCurrentNode)==0 && strcmp("<function>",AST->ASTparent->nodeSymbol)!=0){
			error_flag=1;
error_flag=1;			
printf("Line %d: The function <%s> is invoked recursively.\n",AST->lineNo,AST->lexemeCurrentNode);
		}else if(strcmp("<function>",AST->ASTparent->nodeSymbol)!=0){
		
			int global_flag=0;
			STNode* temp=globalTable[hash_key(AST->lexemeCurrentNode)].head;
			while(temp!=NULL){
				if(strcmp(temp->lexeme,AST->lexemeCurrentNode)==0){
					
					break;
				}
				temp=temp->next;
			}
			
			if(temp==NULL){
				error_flag=1;
error_flag=1;				
printf("Line %d: The function %s is undefined.\n",AST->lineNo,AST->lexemeCurrentNode);
			}else if(temp->STnext==NULL){
				error_flag=1;
error_flag=1;				
printf("Line %d: The function %s must preceded function %s.\n",AST->lineNo,AST->lexemeCurrentNode,function_name);
			}
					
		
		}
		
	}else if(strcmp(AST->nodeSymbol,"TK_MAIN")==0){			
		if(strcmp(function_name,AST->lexemeCurrentNode)==0 && strcmp("<mainFunction>",AST->ASTparent->nodeSymbol)!=0){
			error_flag=1;
			printf("Line %d: The function <%s> is invoked recursively.\n",AST->lineNo,AST->lexemeCurrentNode);
		}
	}
	
	else if(strcmp("<assignmentStmt>",AST->nodeSymbol)==0){
		treeNode *temp=AST;
		temp=AST->ASTchild->ASTchild; //TK_ID
		
		char* type_LHS=checkID(temp,function_name);	

		if(strlen(type_LHS) < 5){
		if(strcmp(type_LHS,"")!=0){
			temp=AST->ASTchild->ASTnext->ASTnext; //<arithmeticExpression>
			check_arithmetic(temp,type_LHS,function_name,1);
		}else{
			temp=AST->ASTchild->ASTnext->ASTnext; //<arithmeticExpression>
			check_arithmetic(temp,type_LHS,function_name,0); 
		}	
		}else{
			
			temp=AST->ASTchild->ASTnext->ASTnext;
			//printf("%s\n", temp->nodeSymbol);
			char *type=check_type_arithmetic(temp,type_LHS,function_name,AST->ASTchild->ASTnext->lineNo);

			if(strcmp(type_LHS,type)!=0){
error_flag=1;				
printf("Line %d: Type Mismatch at RHS of <---. Type should be %s.\n",AST->ASTchild->ASTnext->lineNo,type_LHS);
			}
				
		}
		
	}
	
	else if(strcmp("<booleanExpression>",AST->nodeSymbol)==0 && strcmp("<booleanExpression>",AST->ASTparent->nodeSymbol)!=0){

		check_boolean(AST,function_name);
	}
	
	else if(strcmp("<funCallStmt>",AST->nodeSymbol)==0){
		treeNode *callFun;
		treeNode *inPar;
		treeNode *outPar=NULL;

		if(AST->ASTchild->ASTchild!=NULL){
			outPar=AST->ASTchild->ASTchild;
			callFun = AST->ASTchild->ASTnext;
			inPar= AST->ASTchild->ASTnext->ASTnext->ASTchild;
		}else{
			callFun = AST->ASTchild;
			inPar= AST->ASTchild->ASTnext->ASTchild;

		}

		node *funOutPar = outParTable[hash_key(callFun->lexemeCurrentNode)].head;

		if((funOutPar!=NULL && funOutPar->nextL!=NULL && outPar==NULL) || ((funOutPar==NULL || funOutPar->nextL==NULL) && outPar!=NULL)){
			error_flag=1;
			
			
			if(funOutPar==NULL && outPar!=NULL){
			error_flag=1;

			printf("Line %d: The function %s must preceded function %s.\n",callFun->lineNo,callFun->lexemeCurrentNode,function_name);			
			}else{
			error_flag=1;
			printf("Line %d: In function %s output parameter mismatch with %s.\n",callFun->lineNo,function_name,callFun->lexemeCurrentNode);
			}
			
		}
		

		if(funOutPar!=NULL && funOutPar->nextL!=NULL){


		while(strcmp(funOutPar->lexeme,callFun->lexemeCurrentNode)!=0){
			funOutPar=funOutPar->next;
		}
			funOutPar=funOutPar->nextL;
		if(funOutPar==NULL && outPar!=NULL){
			error_flag=1;

			printf("Line %d: The function %s must preceded function %s.\n",callFun->lineNo,callFun->lexemeCurrentNode,function_name);			
			}else{


				while(outPar!=NULL && funOutPar!=NULL){

					if(strcmp("TK_ID",outPar->nodeSymbol)==0){
																							
						if(strcmp(checkID(outPar,function_name),"")!=0 && strcmp(checkID(outPar,function_name),getSTNodetype(funOutPar->lexeme,callFun->lexemeCurrentNode))!=0){
							error_flag=1;
							printf("Line %d: Type mismatch <%s,%s> must be of type <%s>.\n",outPar->lineNo,outPar->lexemeCurrentNode,checkID(outPar,function_name),getSTNodetype(funOutPar->lexeme,callFun->lexemeCurrentNode));

						}
						
						
						funOutPar=funOutPar->nextL;
					}
					outPar=outPar->ASTnext;
				}
				if(outPar->ASTnext!=NULL || funOutPar!=NULL){
					error_flag=1;
					printf("Line %d: The number of output parametrs at function call <%s> is incorrect.\n",outPar->lineNo,callFun->lexemeCurrentNode);
				}
		
		}
		}
		

		node *funInPar = inParTable[hash_key(callFun->lexemeCurrentNode)].head;

				
		if(funInPar!=NULL && funInPar->nextL!=NULL){
		while(strcmp(funInPar->lexeme,callFun->lexemeCurrentNode)!=0){
			funInPar=funInPar->next;
		}


		funInPar=funInPar->nextL;

		if(funInPar==NULL){
			error_flag=1;

			printf("Line %d: The function %s must preceded function %s.\n",callFun->lineNo,callFun->lexemeCurrentNode,function_name);			
			}else{
																					
				while(inPar!=NULL && funInPar!=NULL){

					if(strcmp("TK_ID",inPar->nodeSymbol)==0){
						if(strcmp(checkID(inPar,function_name),"")!=0 && strcmp(checkID(inPar,function_name),getSTNodetype(funInPar->lexeme,callFun->lexemeCurrentNode))!=0){
							error_flag=1;
							printf("Line %d: Type mismatch <%s,%s> must be of type <%s>.\n",inPar->lineNo,inPar->lexemeCurrentNode,checkID(inPar,function_name),getSTNodetype(funInPar->lexeme,callFun->lexemeCurrentNode));

						}
						funInPar=funInPar->nextL;
					}
					inPar=inPar->ASTnext;
				}
				if(inPar!=NULL || funInPar!=NULL){
					error_flag=1;
					printf("Line %d: The number of input parametrs at function call <%s> is incorrect.\n",outPar->lineNo,callFun->lexemeCurrentNode);
				}
		
		}
		
		}if((funInPar!=NULL && funInPar->nextL!=NULL && inPar==NULL) || ((funInPar==NULL || funInPar->nextL==NULL) && inPar!=NULL)){
			error_flag=1;
			
			
			if(funInPar==NULL && inPar!=NULL){
			error_flag=1;

			printf("Line %d: The function %s must preceded function %s.\n",callFun->lineNo,callFun->lexemeCurrentNode,function_name);			
			}else{
error_flag=1;			
printf("Line %d: In function %s output parameter mismatch with %s.\n",callFun->lineNo,function_name,callFun->lexemeCurrentNode);
			}
			
		}
	} 
	
	else if(strcmp(AST->nodeSymbol,"TK_ID")==0 && (strcmp("<declaration>",AST->ASTparent->nodeSymbol)!=0 || strcmp("<parameter_list>",AST->ASTparent->nodeSymbol)!=0)){
		if((strcmp(AST->ASTparent->nodeSymbol,"<singleOrRecId>")==0 && strcmp(AST->ASTparent->ASTparent->nodeSymbol,"<assignmentStmt>")==0) || (strcmp(AST->ASTparent->nodeSymbol,"<var>")==0 && strcmp(AST->ASTparent->ASTparent->nodeSymbol,"<booleanExpression>")==0)){
						
			}else{

			checkID(AST,function_name);	
			}
	}
	
	//	if(nextTrack!=1){
	Table=fill_function_table(AST->ASTchild,Table,function_name,offset);
	//}
	Table=fill_function_table(AST->ASTnext,Table,function_name,offset);
	return Table;
}

//Insert function parameters in input and output parameter tables. 
node *insertPar(node *list,treeNode *AST){
	if(AST==NULL) return list;
											
	if(strcmp(AST->nodeSymbol,"TK_ID")==0){

					if(list==NULL){
						list=(node *)malloc(sizeof(node));
						list->lexeme=AST->lexemeCurrentNode;
						
					}
		list->nextL=insertPar(list->nextL,AST->ASTchild);
		list->nextL=insertPar(list->nextL,AST->ASTnext);
				}else{
		list=insertPar(list,AST->ASTchild);
		list=insertPar(list,AST->ASTnext);
				
				}
				
	
	return list;	
				
}

//Table for input and output parameters
void create_ParTable(treeNode *AST,char* function_name){

	if(AST==NULL) return;
	
	if(strcmp(AST->nodeSymbol,"<input_par>")==0){
		node *temp;
		node *head=inParTable[hash_key(function_name)].head;
		
		if(head==NULL){
			inParTable[hash_key(function_name)].head=(node *)malloc(sizeof(node));
			temp=inParTable[hash_key(function_name)].head;
			temp->lexeme=function_name;
			temp->next=NULL;

		}else{
			while(head->next!=NULL){
				head=head->next;
			}
			head->next=(node *)malloc(sizeof(node));
			temp=head->next;
			temp->lexeme=function_name;
			temp->next=NULL;
		}
		temp->nextL=NULL;


		if(AST->ASTchild!=NULL && strcmp(AST->ASTchild->nodeSymbol,"<parameter_list>")==0){
				
			

					temp->nextL=insertPar(temp->nextL,AST->ASTchild);

				

				
			
		} 
	}else if(strcmp(AST->nodeSymbol,"<output_par>")==0){
		node *temp;
		node *head=outParTable[hash_key(function_name)].head;
		if(head==NULL){
			outParTable[hash_key(function_name)].head=(node *)malloc(sizeof(node));
			temp=outParTable[hash_key(function_name)].head;
			temp->lexeme=function_name;
			temp->next=NULL;
		}else{
			while(head->next!=NULL){
				head=head->next;
			}
			head->next=(node *)malloc(sizeof(node));
			temp=head->next;
			temp->lexeme=function_name;
			temp->next=NULL;
		}
		temp->nextL=NULL;

		if(AST->ASTchild!=NULL && strcmp(AST->ASTchild->nodeSymbol,"<parameter_list>")==0){
								temp->nextL=insertPar(temp->nextL,AST->ASTchild);
		} 
	}
			
	create_ParTable(AST->ASTchild,function_name);
	create_ParTable(AST->ASTnext,function_name);

}

//Function to create the symbol table
void create_ST(treeNode *AST){

	if(AST==NULL) return;

	if(strcmp(AST->nodeSymbol,"<function>")==0 || strcmp(AST->nodeSymbol,"<mainFunction>")==0){
		int flag=0;
		STElem *Table = initialize_table(SIZE);
		STNode *temp=globalTable[hash_key(AST->ASTchild->lexemeCurrentNode)].head;
		
		while(temp!=NULL){
				if(strcmp(temp->lexeme,AST->ASTchild->lexemeCurrentNode)==0){			
								break;
							}
							temp=temp->next;
						}
		
		if(temp->STnext==NULL){	
				temp->STnext=Table;
				if(strcmp(AST->nodeSymbol,"<function>")==0){
				
					create_ParTable(AST,AST->ASTchild->lexemeCurrentNode);	
				}
				Table=fill_function_table(AST->ASTchild,Table,AST->ASTchild->lexemeCurrentNode,0);	
				off_track=0;
		}
		
	
		
	}
	
	create_ST(AST->ASTnext);
	
	return;
}

//Function to print the symbol table
void printST(STElem *Table){
	int i=0;
	for(i=0;i<SIZE;i++){
		if(Table[i].head!=NULL){
			STNode *temp=Table[i].head;
						
			while(temp!=NULL){
				if(strcmp(temp->type,"function")==0) printST(temp->STnext);
				else printf("%-30s %-30s %-30s %-30d\n",temp->lexeme,temp->type,temp->scope,temp->offset);
				temp=temp->next;
			}
		}
	}
}

//Function to print the record table
void printRecord(STElem *Table){
	int i=0;
	for(i=0;i<SIZE;i++){
		if(Table[i].head!=NULL){
			STNode *temp=Table[i].head;
						
			while(temp!=NULL){
				if(strcmp(temp->type,"record")==0){
					printf("---%s---\n",temp->lexeme);
					printST(temp->STnext);
				}
				else printf("%-30s %-30s %-30s %-30d\n",temp->lexeme,temp->type,temp->scope,temp->offset);
				temp=temp->next;
			}
		}
	}
}

//Defines the fields of Record
void create_recordTypes(treeNode *AST){

	if(AST==NULL) return;
	int flag=0;

	if(strcmp(AST->nodeSymbol,"TK_RECORDID")==0 && strcmp(AST->ASTparent->nodeSymbol,"<typeDefinition>")==0){

		STElem *Table = initialize_table(SIZE);
		STNode *temp=recordTable[hash_key(AST->lexemeCurrentNode)].head;

		if(temp==NULL){
		recordTable[hash_key(AST->lexemeCurrentNode)].head=create_STnode(AST->lexemeCurrentNode, "record", "global", -1 ,temp);

		}else{
			STNode *temp1=temp;
			while(temp1!=NULL){
				if(strcmp(temp1->lexeme,AST->lexemeCurrentNode)==0){			
								error_flag=1;
								flag=1;
								break;
							}
							temp1=temp1->next;
						}
		
		}
		
		if(flag==1){
			error_flag=1;
			printf("Line %d: Record <%s> redeclared\n",AST->lineNo,AST->lexemeCurrentNode);
		}else{
		flag=0;
			recordTable[hash_key(AST->lexemeCurrentNode)].head=create_STnode(AST->lexemeCurrentNode, "record", "global", -1 ,temp);
			recordTable[hash_key(AST->lexemeCurrentNode)].head->STnext=Table;
			treeNode *temp_next=AST->ASTnext;
			int off=0;

			while(strcmp(temp_next->nodeSymbol,"TK_ENDRECORD")!=0){

				if(temp_next->ASTchild!=NULL){

					temp=Table[hash_key(temp_next->ASTchild->ASTnext->lexemeCurrentNode)].head;
					
					if(temp==NULL){
				
						Table[hash_key(temp_next->ASTchild->ASTnext->lexemeCurrentNode)].head=create_STnode(temp_next->ASTchild->ASTnext->lexemeCurrentNode, temp_next->ASTchild->lexemeCurrentNode, "global", off ,temp);

		}else{
			STNode *temp1=temp;
			while(temp1!=NULL){
				if(strcmp(temp1->lexeme,temp_next->ASTchild->ASTnext->lexemeCurrentNode)==0){			
								error_flag=1;
								flag=1;
								break;
							}
							temp1=temp1->next;
						}
		
		}if(flag==1){
			error_flag=1;
			printf("Line %d: Field <%s> redeclared\n",temp_next->ASTchild->ASTnext->lineNo,temp_next->ASTchild->ASTnext->lexemeCurrentNode);
		}else{
					
					Table[hash_key(temp_next->ASTchild->ASTnext->lexemeCurrentNode)].head=create_STnode(temp_next->ASTchild->ASTnext->lexemeCurrentNode, temp_next->ASTchild->lexemeCurrentNode, "global", off ,temp);
									
					if(strcmp(temp_next->ASTchild->nodeSymbol,"TK_INT")==0){
						off+=2;
					}else if(strcmp(temp_next->ASTchild->nodeSymbol,"TK_REAL")==0){
						off+=4;
					}

				}
				}
flag=0;
					temp_next=temp_next->ASTnext;

			
			}
		}
	}

	create_recordTypes(AST->ASTchild);
	create_recordTypes(AST->ASTnext);

}


//Creates the global table which includes global variable and function declaration.
void create_GTvar(treeNode *AST){

	if(AST==NULL) return;
	char *scope;
	int offset_t;
	
	if(strcmp(AST->nodeSymbol,"TK_INT")==0){
		if(AST->ASTnext!=NULL && strcmp(AST->ASTnext->nodeSymbol,"TK_ID")==0){
			
			if(AST->ASTnext->ASTnext!=NULL && strcmp(AST->ASTnext->ASTnext->nodeSymbol,"TK_GLOBAL")==0){
				offset_t=-1;
				scope="global";
				int flag=0;
				STNode *temp=globalTable[hash_key(AST->ASTnext->lexemeCurrentNode)].head;
				
				if(temp==NULL){
				globalTable[hash_key(AST->ASTnext->lexemeCurrentNode)].head=create_STnode(AST->ASTnext->lexemeCurrentNode, AST->lexemeCurrentNode,scope,offset_t,temp);
				}else{
						STNode *temp1=temp;
						while(temp1!=NULL){
							if(strcmp(temp1->lexeme,AST->ASTnext->lexemeCurrentNode)==0){			
								error_flag=1;
								flag=1;
								break;
							}
							temp1=temp1->next;
						}
				}
				if(flag==0){
								globalTable[hash_key(AST->ASTnext->lexemeCurrentNode)].head=create_STnode(AST->ASTnext->lexemeCurrentNode, AST->lexemeCurrentNode,scope,offset_t,temp);								
				}else{
					error_flag=1;
					printf("Line %d: The variable <%s> being a global variable is declared more than once.\n",AST->ASTnext->lineNo,AST->ASTnext->lexemeCurrentNode);
				}
					
						
				
			}
		}
	}else if(strcmp(AST->nodeSymbol,"TK_REAL")==0){
		if(AST->ASTnext!=NULL && strcmp(AST->ASTnext->nodeSymbol,"TK_ID")==0){
			
			if(AST->ASTnext->ASTnext!=NULL && strcmp(AST->ASTnext->ASTnext->nodeSymbol,"TK_GLOBAL")==0){
				offset_t=-1;
				scope="global";
				int flag=0;
				STNode *temp=globalTable[hash_key(AST->ASTnext->lexemeCurrentNode)].head;
				if(temp==NULL){
				globalTable[hash_key(AST->ASTnext->lexemeCurrentNode)].head=create_STnode(AST->ASTnext->lexemeCurrentNode, AST->lexemeCurrentNode,scope,offset_t,temp);
				}else{
						STNode *temp1=temp;
						while(temp1!=NULL){
							if(strcmp(temp1->lexeme,AST->ASTnext->lexemeCurrentNode)==0){			
								error_flag=1;
								flag=1;
								break;
							}
							temp1=temp1->next;
						}
				}
				if(flag==0){
								globalTable[hash_key(AST->ASTnext->lexemeCurrentNode)].head=create_STnode(AST->ASTnext->lexemeCurrentNode, AST->lexemeCurrentNode,scope,offset_t,temp);								
				}else{
					error_flag=1;
					printf("Line %d: The variable <%s> being a global variable is declared more than once.\n",AST->ASTnext->lineNo,AST->ASTnext->lexemeCurrentNode);
				}
				
				
			}
		}
	}else if(strcmp(AST->nodeSymbol,"TK_RECORDID")==0 && (strcmp(AST->ASTparent->nodeSymbol,"<parameter_list>")==0 || strcmp(AST->ASTparent->nodeSymbol,"<declaration>")==0)){
	

				int size=0;
				char *type="";

		if(AST->ASTnext!=NULL && strcmp(AST->ASTnext->nodeSymbol,"TK_ID")==0){
						if(AST->ASTnext->ASTnext!=NULL && strcmp(AST->ASTnext->ASTnext->nodeSymbol,"TK_GLOBAL")==0){
				if(recordTable[hash_key(AST->lexemeCurrentNode)].head!=NULL){

					STNode *temp=recordTable[hash_key(AST->lexemeCurrentNode)].head;

					while(strcmp(temp->lexeme,AST->lexemeCurrentNode)!=0){

						temp=temp->next;
					}
					STElem* record=temp->STnext;
					
					int i=0;
					for(i=0;i<SIZE;i++){
						if(record[i].head!=NULL){
							STNode *temp_1=record[i].head;
							
						
							while(temp_1!=NULL){

								if(strcmp(temp_1->type,"int")==0) {
									int len=strlen(type);
									char* type1=(char *)malloc((len+4)*sizeof(char));
									strcpy(type1,type);  
									strcat(type1,"int x ");
									type=type1;

									size+=2;
								}
								else if(strcmp(temp_1->type,"real")==0) {
								
									int len=strlen(type);
									char* type1=(char *)malloc((len+7)*sizeof(char));
									strcpy(type1,type);  
									strcat(type1,"real x ");
									type=type1;
									
									
									size+=4;
								}
								
								temp_1=temp_1->next;
																
							}
						}
					}
					
				}
				char *type_t=(char *)malloc((strlen(type)-3)*sizeof(char));
				strncpy(type_t,type,strlen(type)-3);
				type=type_t;
				offset_t=-1;
				scope="global";
				int flag=0;
				STNode *temp=globalTable[hash_key(AST->ASTnext->lexemeCurrentNode)].head;
															
				if(temp==NULL){
				globalTable[hash_key(AST->ASTnext->lexemeCurrentNode)].head=create_STnode(AST->ASTnext->lexemeCurrentNode, AST->lexemeCurrentNode,scope,offset_t,temp);
				}else{
						STNode *temp1=temp;
						while(temp1!=NULL){
							if(strcmp(temp1->lexeme,AST->ASTnext->lexemeCurrentNode)==0){			
								error_flag=1;
								flag=1;
								break;
							}
							temp1=temp1->next;
						}
				}
				if(flag==0){
								globalTable[hash_key(AST->ASTnext->lexemeCurrentNode)].head=create_STnode(AST->ASTnext->lexemeCurrentNode, type_t,scope,offset_t,temp);	
								globalTable[hash_key(AST->ASTnext->lexemeCurrentNode)].head->recordType=AST->lexemeCurrentNode;							
				}else{
error_flag=1;					
printf("Line %d: The variable <%s> being a global variable is declared more than once.\n",AST->ASTnext->lineNo,AST->ASTnext->lexemeCurrentNode);
				}
					
			
		} 
	}
	
	}
	else if(strcmp(AST->nodeSymbol,"<function>")==0 || strcmp(AST->nodeSymbol,"<mainFunction>")==0){
		int flag=0;
		
		STNode *temp=globalTable[hash_key(AST->ASTchild->lexemeCurrentNode)].head;
		
		if(temp==NULL){	
		globalTable[hash_key(AST->ASTchild->lexemeCurrentNode)].head=create_STnode(AST->ASTchild->lexemeCurrentNode, "function", "global", -1 ,temp);
		}else{
			STNode *temp1=temp;
						while(temp1!=NULL){
							if(strcmp(temp1->lexeme,AST->ASTchild->lexemeCurrentNode)==0){			
								error_flag=1;
								flag=1;
								break;
							}
							temp1=temp1->next;
						}
		}
		
		if(flag==0){
				globalTable[hash_key(AST->ASTchild->lexemeCurrentNode)].head=create_STnode(AST->ASTchild->lexemeCurrentNode, "function", "global", -1 ,temp);	
				
				
					
				off_track=0;					
				}else{
					error_flag=1;
					printf("Line %d: The function %s is overloaded.\n",AST->ASTchild->lineNo,AST->ASTchild->lexemeCurrentNode);
				}

		

		
	}
	
	create_GTvar(AST->ASTchild);
	create_GTvar(AST->ASTnext);

}

//To print the symbol Table
void printpar(list *Table){
	int i=0;
	for(i=0;i<SIZE;i++){
		
		if(Table[i].head!=NULL){
			node *temp=Table[i].head;
			printf("%s\n\n",temp->lexeme);
			while(temp!=NULL){
				printf("**%s***\n",temp->lexeme);
				node *temp1=temp->nextL;
				while(temp1!=NULL){
					printf("%s->",temp1->lexeme);
					temp1=temp1->nextL;
				}
				printf("NULL\n\n");
				temp=temp->next;
			} 
		}
	}
}


//check assignment of value to ouput parameter in function
int check_assign_func(treeNode* AST,char *outPar,int flag){
	if(AST==NULL) return flag;


	if((strcmp(AST->lexemeCurrentNode,outPar)==0 && AST->ASTparent!=NULL && strcmp(AST->ASTparent->nodeSymbol,"<singleOrRecId>")==0 && AST->ASTparent->ASTparent!=NULL && strcmp(AST->ASTparent->ASTparent->nodeSymbol,"<assignmentStmt>")==0) || (strcmp(AST->lexemeCurrentNode,outPar)==0 && AST->ASTparent!=NULL && strcmp(AST->ASTparent->nodeSymbol,"<outputParameters>")==0 && AST->ASTparent->ASTparent!=NULL && strcmp(AST->ASTparent->ASTparent->nodeSymbol,"<funCallStmt>")==0)){
		flag=1;
	}
	
	flag=check_assign_func(AST->ASTchild,outPar,flag);
	flag=check_assign_func(AST->ASTnext,outPar,flag);
	
	return flag;

}


//check assignment of value to ouput parameter in function
void check_assign_output(treeNode *AST){
	if(AST==NULL) return;

	node *funOutPar = outParTable[hash_key(AST->ASTchild->lexemeCurrentNode)].head;

	if(funOutPar!=NULL){
		while(strcmp(funOutPar->lexeme,AST->ASTchild->lexemeCurrentNode)!=0){
			funOutPar=funOutPar->next;

		}


	funOutPar=funOutPar->nextL;

	while(funOutPar!=NULL){
		char *outpar=funOutPar->lexeme;
		int flag=check_assign_func(AST,outpar,0);
		if(!flag){
					error_flag=1;
		printf("Parameter <%s> does not get a value assigned within the function definition.\n",outpar);
	
	}
		funOutPar=funOutPar->nextL;
		}
	}
	
	check_assign_output(AST->ASTnext);
	
}


//check while variable is updated or ot
void check_update_while(char *id, treeNode *AST){
	if(AST==NULL) return;


	if((strcmp(AST->lexemeCurrentNode,id)==0 && AST->ASTparent!=NULL && strcmp(AST->ASTparent->nodeSymbol,"<singleOrRecId>")==0 && AST->ASTparent->ASTparent!=NULL && strcmp(AST->ASTparent->ASTparent->nodeSymbol,"<assignmentStmt>")==0) || (strcmp(AST->lexemeCurrentNode,id)==0 && AST->ASTparent!=NULL && strcmp(AST->ASTparent->nodeSymbol,"<outputParameters>")==0 && AST->ASTparent->ASTparent!=NULL && strcmp(AST->ASTparent->ASTparent->nodeSymbol,"<funCallStmt>")==0) || (-strcmp(AST->lexemeCurrentNode,id)==0 && AST->ASTparent!=NULL && strcmp(AST->ASTparent->nodeSymbol,"<singleOrRecId>")==0 && AST->ASTparent->ASTparent!=NULL && strcmp(AST->ASTparent->ASTparent->nodeSymbol,"<ioStmt>")==0))
	{
		while_check=1;
	}
	
	check_update_while(id,AST->ASTchild);
	check_update_while(id,AST->ASTnext);
	


}


//extract variables in boolean of while
void extract_iter_variables(treeNode *AST,treeNode *iter){
	if(AST==NULL) return;
	
	if(strcmp(AST->nodeSymbol,"TK_ID")==0){
		check_update_while(AST->lexemeCurrentNode, iter);
	}
	
	extract_iter_variables(AST->ASTchild,iter);
	extract_iter_variables(AST->ASTnext,iter);	

}

//check updation error in while
void check_iter(treeNode *AST){
	if(AST==NULL) return;
	if(strcmp(AST->nodeSymbol,"<iterativeStmt>")==0){
		while_check=0;
		//printf("%s\n",AST->nodeSymbol);
		extract_iter_variables(AST->ASTchild->ASTnext->ASTchild,AST->ASTchild);	
		if(!while_check){
			error_flag=1;
			treeNode *temp=AST->ASTchild;

			while(temp!=NULL && strcmp("TK_ENDWHILE",temp->nodeSymbol)!=0){
				temp=temp->ASTnext;
			}
			error_flag=1;
			printf("lines %d-%d: None of the variables participating in the iterations of the while loop gets updated.\n",AST->ASTchild->lineNo,temp->lineNo);
		
		}
	}
	
	check_iter(AST->ASTchild);
	check_iter(AST->ASTnext);
	
}



void ST_main(parseTree *PT){
	int i=0;
	for(i=0;i<SIZE;i++){
		globalTable[i].head=NULL;
		globalTable[i].count=0;
	}
	arithmetic_flag=0;
	error_flag=0;
	treeNode *AST=PT->root;

	create_recordTypes(AST);

	create_GTvar(AST);

	create_ST(AST->ASTchild);
	check_assign_output(AST->ASTchild);
	check_iter(AST);

}
