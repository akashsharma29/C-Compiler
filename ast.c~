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
#include "ast.h"

//Function to check the non terminals to be removed.
int non_term_to_remove(char *non_terminal){  

	if( 
	(strcmp(non_terminal, "<otherFunctions>") == 0) || 
	(strcmp(non_terminal, "<typeDefinitions>") == 0) || 
	(strcmp(non_terminal, "<fieldDefinitions>") == 0) || 
	(strcmp(non_terminal, "<otherStmts>") == 0) || 	
		(strcmp(non_terminal, "<stmts>") == 0) || 	
	(strcmp(non_terminal, "<moreFields>") == 0) ||
	(strcmp(non_terminal, "<dataType>") == 0) || 
	(strcmp(non_terminal, "<primitiveDatatype>") == 0) ||
	(strcmp(non_terminal, "<constructedDatatype>") == 0) ||
	(strcmp(non_terminal, "<remaining_list>") == 0) || 
	(strcmp(non_terminal, "<global_or_not>") == 0) ||
	(strcmp(non_terminal, "<declarations>") == 0) ||
	(strcmp(non_terminal, "<stmt>") == 0) ||
	(strcmp(non_terminal, "<new_24>") == 0) ||
	(strcmp(non_terminal, "<highPrecedenceOperators>") == 0) ||
	(strcmp(non_terminal, "<lowPrecedenceOperators>") == 0) ||
    (strcmp(non_terminal, "<temp>") == 0) ||
    (strcmp(non_terminal, "<idList>") == 0) ||
	(strcmp(non_terminal, "<returnStmt>") == 0) ||
	(strcmp(non_terminal, "<allVar1>") == 0) ||
	(strcmp(non_terminal, "<all>") == 0) ||
	(strcmp(non_terminal, "<optionalReturn>") == 0) ||
	(strcmp(non_terminal, "<more_ids>") == 0) ) return 1;
	else return 0;	
}

//Terminals which are pointing to epsilon.
int to_eps(char *non_terminal){

	if( (strcmp(non_terminal, "<otherFunctions>") == 0) || 
		(strcmp(non_terminal, "<output_par>") == 0) ||
		(strcmp(non_terminal, "<remaining_list>") == 0) ||
		(strcmp(non_terminal, "<typeDefinitions>") == 0) ||
		(strcmp(non_terminal, "<moreFields>") == 0) ||
		(strcmp(non_terminal, "<declarations>") == 0) ||
		(strcmp(non_terminal, "<global_or_not>") == 0) ||
		(strcmp(non_terminal, "<otherStmts>") == 0) ||
		(strcmp(non_terminal, "<new_24>") == 0) ||
		(strcmp(non_terminal, "<outputParameters>") == 0) ||
		(strcmp(non_terminal, "<expPrime>") == 0) ||
		(strcmp(non_terminal, "<termPrime>") == 0) ||
		(strcmp(non_terminal, "<temp>") == 0) ||
		(strcmp(non_terminal, "<optionalReturn>") == 0) ||
		(strcmp(non_terminal, "<allVar1>") == 0) ||
		(strcmp(non_terminal, "<more_ids>") == 0) ) return 1;
		else return 0;	

}

//Function to check the terminals to be removed.
int term_to_remove(char *terminal){	
	if( (strcmp(terminal, "TK_COMMENT") == 0) ||
	(strcmp(terminal, "TK_WITH") == 0) ||
	(strcmp(terminal, "TK_PARAMETERS") == 0) ||
	(strcmp(terminal, "TK_END") == 0) ||
	(strcmp(terminal, "TK_TYPE") == 0) ||

	(strcmp(terminal, "TK_LIST") == 0) ||
	(strcmp(terminal, "TK_SQL") == 0) ||
	(strcmp(terminal, "TK_SQR") == 0) ||
	(strcmp(terminal, "TK_INPUT") == 0) ||
	(strcmp(terminal, "TK_SEM") == 0) ||
	(strcmp(terminal, "TK_COLON") == 0) ||
	(strcmp(terminal, "TK_DOT") == 0) ||
	(strcmp(terminal, "TK_OP") == 0) ||
	(strcmp(terminal, "TK_CL") == 0) ||
	(strcmp(terminal, "TK_RETURN") == 0) ||		
	(strcmp(terminal, "TK_CALL") == 0) ||
	(strcmp(terminal,"TK_COMMA")==0) ||
    (strcmp(terminal, "TK_PARAMETER") == 0) ||
    (strcmp(terminal, "TK_OUTPUT") == 0) ||
    (strcmp(terminal, "eps") == 0) ) return 1;
    else return 0;
}

//Function to create AST from a given Parsetree.
void createAST(treeNode *parent, treeNode *child){
	if(child==NULL) return;
	
	if((child->isLeafNode==0 && non_term_to_remove(child->nodeSymbol)==0 ) || (child->isLeafNode==1 && term_to_remove(child->nodeSymbol)==0) ){
	
	if(to_eps(child->nodeSymbol)==1 && (strcmp(child->child->nodeSymbol,"eps")==0)){
		
	}else{

		treeNode *temp=parent->ASTchild;
		treeNode *prevtemp;

		if(temp==NULL){
			parent->ASTchild=child;
			child->ASTparent=parent;
		}
		else{
			while(temp!=NULL){
				prevtemp=temp;
				temp=temp->ASTnext;
			}
			prevtemp->ASTnext=child;
			child->ASTparent=parent;
		}
			
	
		createAST(child,child->child);
	}

	}else{
		createAST(parent,child->child);
	}
		createAST(parent,child->next);
	
	return;
}

void constructAST(parseTree *PT){
	createAST(PT->root,PT->root->child);
	return;
}



//Function to print the complete AST
void printAST(treeNode *root){
	if(root==NULL){ return; } 
   
	if(strcmp(root->nodeSymbol,"TK_ASSIGNOP")!=0){   
    printf("%-20s",root->lexemeCurrentNode);
    
    if(root->isLeafNode==1){
        printf("%-20d",root->lineNo);
        printf("%-20s",root->token);
        char s[20];
        int i=0;
       
        
    }else{
        printf("%-20s"," - ");
        printf("%-20s"," - ");
         
    }
    if(lookup_symbol(root->token)==lookup_symbol("TK_NUM") || lookup_symbol(root->token)==lookup_symbol("TK_RNUM")){
        printf("%-20s",root->valueIfNumber);
        
    }else{
        printf("%-20s"," - ");
    }

	if(root->ASTparent!=NULL)
    printf("%-20s",root->ASTparent->nodeSymbol);
    else
   	printf("%-20s"," - ");
   	    
    if(root->isLeafNode==1){
        printf("%-20s","yes ");
        printf("%-20s\n"," - ");
        
    }else{
        printf("%-20s","no ");
        printf("%-20s\n",root->nodeSymbol);
        
    }
    
    }
    printAST(root->ASTchild);
    printAST(root->ASTnext);
    
    
    return;
}


//Function to calculate the nodes in AST
void countAST(treeNode *root){
	if(root==NULL) return;
	if(strcmp(root->nodeSymbol,"TK_ASSIGNOP")!=0 ){
	astcount++;
	countAST(root->ASTchild);
	countAST(root->ASTnext);
	}
	
}

void countPST(treeNode * t){
	if(t==NULL) return;

	pstcount++;
	countPST(t->child);
	countPST(t->next);
	
}
