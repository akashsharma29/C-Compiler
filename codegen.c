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
#include "codegen.h"
#include "symbolTableDef.h"

//generates the code for write operation.
void write(treeNode *AST){
	if(AST==NULL) return;

	if(strcmp("TK_ID",AST->nodeSymbol)==0){
		fprintf(ASM,"	mov	rsi,[%s]\n",AST->lexemeCurrentNode);
		fprintf(ASM,"	mov	rdi,scanint\n");
		fprintf(ASM,"	call printf\n\n");
	}	
	
	write(AST->ASTchild);
	write(AST->ASTnext);
}

//generates the code for read operation.
void read(treeNode *AST){
	if(AST==NULL) return;
	
	if(strcmp("TK_ID",AST->nodeSymbol)==0){
		fprintf(ASM,"	mov	rsi,%s\n",AST->lexemeCurrentNode);
		fprintf(ASM,"	mov	rdi,scanint\n");
		fprintf(ASM,"	call scanf\n\n");
	}	
	
	read(AST->ASTchild);
	read(AST->ASTnext);
}

//generates the code for LHSassign.
char *LHSassign(treeNode *AST,char* LHS){
	
	if(AST==NULL) return LHS;
	
	if(strcmp("TK_ID",AST->nodeSymbol)==0){

		LHS= AST->lexemeCurrentNode;
		
	}
	
	LHS=LHSassign(AST->ASTchild,LHS);
	LHS=LHSassign(AST->ASTnext,LHS);
	
	return LHS;
	
}

//generates the code for termPrime.
void termPrime(treeNode *AST){
	
	factor(AST->ASTchild->ASTnext); 
	if(AST->ASTchild->ASTnext->ASTnext!=NULL){
		termPrime(AST->ASTchild->ASTnext->ASTnext);
		fprintf(ASM,"	pop rbx\n");
		fprintf(ASM,"	pop rax\n");
		if(strcmp(AST->ASTchild->ASTnext->ASTnext->ASTchild->nodeSymbol,"TK_MUL")==0){
			fprintf(ASM,"	mul	rax,rbx\n");
		}else if(strcmp(AST->ASTchild->ASTnext->ASTnext->ASTchild->nodeSymbol,"TK_DIV")==0){
			fprintf(ASM,"	div	rax,rbx\n");
		}
		fprintf(ASM,"	pop rax\n");
	}
	

}

//generates the code for ID
void ID(treeNode *AST){
	if(AST==NULL) return;

	if(strcmp(AST->nodeSymbol,"TK_NUM")==0){
		fprintf(ASM,"	mov rax,%s\n",AST->lexemeCurrentNode);
		fprintf(ASM,"	push rax\n");
	}else if(strcmp(AST->nodeSymbol,"TK_ID")==0){
		fprintf(ASM,"	mov rax,[%s]\n",AST->lexemeCurrentNode);
		fprintf(ASM,"	push rax\n");
	}
	
	ID(AST->ASTchild);
	ID(AST->ASTnext);

}

//generates the code for factor
void factor(treeNode *AST){
		
	if(AST->ASTchild!=NULL){
	if(strcmp(AST->ASTchild->nodeSymbol,"<arithmeticExpression>")!=0){
		ID(AST->ASTchild);

	}else{
		type_arithmetic(AST->ASTchild);
	}
	}
}

//generates the code for term
void term(treeNode *AST){
		
	factor(AST->ASTchild); 

	if(AST->ASTchild->ASTnext!=NULL){
		
		termPrime(AST->ASTchild->ASTnext);
		fprintf(ASM,"	pop rbx\n");
		fprintf(ASM,"	pop rax\n");
		if(strcmp(AST->ASTchild->ASTnext->ASTchild->nodeSymbol,"TK_MUL")==0){
			fprintf(ASM,"	mul	rbx\n");
		}else if(strcmp(AST->ASTchild->ASTnext->ASTchild->nodeSymbol,"TK_DIV")==0){
			fprintf(ASM,"	div	rbx\n");
		}
		fprintf(ASM,"	push rax\n");
	}
		
}

//generates the code for expPrime.
char* expPrime(treeNode *AST){
	term(AST->ASTchild->ASTnext);
	if(AST->ASTchild->ASTnext->ASTnext!=NULL){
		expPrime(AST->ASTchild->ASTnext->ASTnext);
		fprintf(ASM,"	pop rbx\n");
		fprintf(ASM,"	pop rax\n");
		if(strcmp(AST->ASTchild->ASTnext->ASTnext->ASTchild->nodeSymbol,"TK_PLUS")==0){
			fprintf(ASM,"	add	rax,rbx\n");
		}else if(strcmp(AST->ASTchild->ASTnext->ASTnext->ASTchild->nodeSymbol,"TK_MINUS")==0){
			fprintf(ASM,"	sub	rax,rbx\n");
		}
		fprintf(ASM,"	push rax\n");
		
	}
	
}

//generates the code for arithmetic statements.
void type_arithmetic(treeNode *AST){

	
	term(AST->ASTchild);

	if(AST->ASTchild->ASTnext!=NULL){
		expPrime(AST->ASTchild->ASTnext);
		fprintf(ASM,"	pop rbx\n");
		fprintf(ASM,"	pop rax\n");
		if(strcmp(AST->ASTchild->ASTnext->ASTchild->nodeSymbol,"TK_PLUS")==0){
			fprintf(ASM,"	add	rax,rbx\n");
		}else if(strcmp(AST->ASTchild->ASTnext->ASTchild->nodeSymbol,"TK_MINUS")==0){
			fprintf(ASM,"	sub	rax,rbx\n");
		}
		fprintf(ASM,"	push rax\n");
		}
}
	
//generates the code for var	
void var(treeNode *AST){
	if(strcmp(AST->ASTchild->nodeSymbol,"TK_NUM")==0){
		fprintf(ASM,"	mov rax,%s\n",AST->ASTchild->lexemeCurrentNode);
	}else if(strcmp(AST->ASTchild->nodeSymbol,"TK_ID")==0){
		fprintf(ASM,"	mov rax,[%s]\n",AST->ASTchild->lexemeCurrentNode);
	}

}

//evaluates boolean expression.
void boolean(treeNode* AST){
	if(strcmp(AST->ASTchild->nodeSymbol,"<booleanExpression>")==0){
	boolean(AST->ASTchild);
	fprintf(ASM,"	push rax\n");
	
	boolean(AST->ASTchild->ASTnext->ASTnext);
	fprintf(ASM,"	pop rbx\n");
	
	if(strcmp(AST->ASTchild->ASTnext->ASTchild->nodeSymbol,"TK_AND")==0){
		fprintf(ASM, "	and rax, rbx\n\n");
	}
	else{
		fprintf(ASM, "	or rax, rbx\n\n");
	}
	}else if(strcmp(AST->ASTchild->nodeSymbol,"TK_NOT")==0){
		boolean(AST->ASTchild->ASTnext);
		fprintf(ASM, "	not rax\n\n");
	}else{
		var(AST->ASTchild);
		fprintf(ASM,"	push rax\n");
		
		var(AST->ASTchild->ASTnext->ASTnext);
		fprintf(ASM,"	mov rbx,rax\n");
		fprintf(ASM,"	pop rax\n");
		fprintf(ASM,"	cmp rax,rbx\n");
		
		if(strcmp(AST->ASTchild->ASTnext->ASTchild->nodeSymbol,"TK_LT")==0){
			fprintf(ASM, "	jl true%d\n",bool_no);
		}else if(strcmp(AST->ASTchild->ASTnext->ASTchild->nodeSymbol,"TK_LE")==0){
			fprintf(ASM, "	jle true%d\n",bool_no);
		}else if(strcmp(AST->ASTchild->ASTnext->ASTchild->nodeSymbol,"TK_EQ")==0){
			fprintf(ASM, "	je true%d\n",bool_no);
		}else if(strcmp(AST->ASTchild->ASTnext->ASTchild->nodeSymbol,"TK_GT")==0){
			fprintf(ASM, "	jg true%d\n",bool_no);
		}else if(strcmp(AST->ASTchild->ASTnext->ASTchild->nodeSymbol,"TK_GE")==0){
			fprintf(ASM, "	jge true%d\n",bool_no);
		}else if(strcmp(AST->ASTchild->ASTnext->ASTchild->nodeSymbol,"TK_NE")==0){
		}
		
		fprintf(ASM, "false%d:\n",bool_no);
		fprintf(ASM, "	mov rax,0\n");
		fprintf(ASM, "	jmp next%d\n",bool_no);
		fprintf(ASM, "true%d:\n",bool_no);
		fprintf(ASM, "	mov rax,1\n");
		fprintf(ASM, "next%d:\n",bool_no);
		                        
                    bool_no++;
	}
}

//generates the code for if statement
void ifpart(treeNode *AST){
	skip=0;
	if(AST==NULL || strcmp(AST->nodeSymbol,"<elsePart>")==0 ) return;

	if(strcmp("TK_READ",AST->nodeSymbol)==0){

		read(AST);
	}else if(strcmp("TK_WRITE",AST->nodeSymbol)==0){
		write(AST);
	}else if(strcmp("<assignmentStmt>",AST->nodeSymbol)==0){
		char *LHS;
		LHS=LHSassign(AST->ASTchild->ASTchild,LHS);
		type_arithmetic(AST->ASTchild->ASTnext->ASTnext);
		//printf("%s\n\n",LHS);
		fprintf(ASM,"	mov [%s],rax\n",LHS);
		fprintf(ASM,"	pop rax\n\n");
	}else if(strcmp("<conditionalStmt>",AST->nodeSymbol)==0){
		fprintf(ASM,"\n\n");
		conditional(AST);
		skip=1;
	}else if(strcmp("<iterativeStmt>",AST->nodeSymbol)==0){

		fprintf(ASM,"\n\n");
		iterative(AST);
		skip=1;
	}
	
	if(!skip){
	ifpart(AST->ASTchild);
	}
	ifpart(AST->ASTnext);
	
}

//generates the code for else statement
void elsepart(treeNode *AST){

	if(AST==NULL) return;
	
	if(strcmp(AST->nodeSymbol,"<elsePart>")==0){

		ifpart(AST->ASTchild);
	}
	
	elsepart(AST->ASTchild);
	elsepart(AST->ASTnext);
	
}

//generates the code for while statement
void whilepart(treeNode *AST){
	skip=0;
	if(AST==NULL || strcmp(AST->nodeSymbol,"TK_ENDWHILE")==0 ) return;

	if(strcmp("TK_READ",AST->nodeSymbol)==0){

		read(AST);
	}else if(strcmp("TK_WRITE",AST->nodeSymbol)==0){
		write(AST);
	}else if(strcmp("<assignmentStmt>",AST->nodeSymbol)==0){
		char *LHS;
		LHS=LHSassign(AST->ASTchild->ASTchild,LHS);
		type_arithmetic(AST->ASTchild->ASTnext->ASTnext);
		//printf("%s\n\n",LHS);
		fprintf(ASM,"	mov [%s],rax\n",LHS);
		fprintf(ASM,"	pop rax\n\n");
	}else if(strcmp("<conditionalStmt>",AST->nodeSymbol)==0){
		fprintf(ASM,"\n\n");
		conditional(AST);
		skip=1;
	}else if(strcmp("<iterativeStmt>",AST->nodeSymbol)==0){

		fprintf(ASM,"\n\n");
		iterative(AST);
		skip=1;
	}
	
	if(!skip){
	ifpart(AST->ASTchild);
	}
	ifpart(AST->ASTnext);
	
}

//generates the code for conditional statements 
void conditional(treeNode *AST){

	boolean(AST->ASTchild->ASTnext);

	fprintf(ASM, "	cmp rax, 0\n");
    fprintf(ASM, "	je ELSE%d\n", cond_no);

    ifpart(AST->ASTchild->ASTnext->ASTnext);

    fprintf(ASM,"	jmp ENDIF%d\n", cond_no);
    fprintf(ASM,"ELSE%d:\n", cond_no);
	
	elsepart(AST);
	fprintf(ASM, "ENDIF%d:\n\n", cond_no);
	cond_no++;

}

//generates the code for iterative statements
void iterative(treeNode *AST){
	fprintf(ASM, "loop%d:\n", cond_no);
	boolean(AST->ASTchild->ASTnext);

	fprintf(ASM, "	cmp rax, 0\n");
    fprintf(ASM, "	je endloop%d\n", cond_no);

    whilepart(AST->ASTchild->ASTnext->ASTnext);

    fprintf(ASM,"	jmp loop%d\n", cond_no);
    fprintf(ASM,"endloop%d:\n", cond_no);
	
	cond_no++;

}

//starts the text section
void start(treeNode *AST){
	skip=0;
	if(AST==NULL) return;

	if(strcmp(AST->nodeSymbol,"TK_MAIN")==0){
		fprintf(ASM,"main:\n\n");
		fprintf(ASM,"\n	push rbp\n");
	}else if(strcmp("TK_READ",AST->nodeSymbol)==0){

		read(AST);
	}else if(strcmp("TK_WRITE",AST->nodeSymbol)==0){
		write(AST);
	}else if(strcmp("<assignmentStmt>",AST->nodeSymbol)==0){
		char *LHS;
		LHS=LHSassign(AST->ASTchild->ASTchild,LHS);
		type_arithmetic(AST->ASTchild->ASTnext->ASTnext);
		//printf("%s\n\n",LHS);
		fprintf(ASM,"	mov [%s],rax\n",LHS);
		fprintf(ASM,"	pop rax\n\n");
	}else if(strcmp("<conditionalStmt>",AST->nodeSymbol)==0){

		fprintf(ASM,"\n\n");
		conditional(AST);
		skip=1;
	}else if(strcmp("<iterativeStmt>",AST->nodeSymbol)==0){

		fprintf(ASM,"\n\n");
		iterative(AST);
		skip=1;
	}

	
	if(!skip){
		start(AST->ASTchild);
	}
	start(AST->ASTnext);

	
}

//traverse the symbol table for declaration.
void traverseST(STElem *Table){
	int i=0;
	for(i=0;i<SIZE;i++){
		if(Table[i].head!=NULL){
			STNode *temp=Table[i].head;
						
			while(temp!=NULL){
				if(strcmp(temp->type,"function")==0) traverseST(temp->STnext);
				else if(strcmp(temp->recordType,"")!=0){
					int size=strlen(temp->type)+3;
					size=size/6;
					size=size*8;
					fprintf(ASM,"	%s:	resb	%d\n",temp->lexeme,size);
				}
				else fprintf(ASM,"	%s:	resb	8\n",temp->lexeme);
				
				
				temp=temp->next;
			}
		}
	}
	
}

//Initiates the bss section
void bss(){

	fprintf(ASM,"section .bss\n");
	
	traverseST(globalTable);
	int i=0;
	
	for(i=0;i<10;i++){
		fprintf(ASM,"	buffer%d:	resb	8\n",i);
		}
}

//Initiates the data section
void data(){
	fprintf(ASM,"\nsection .data\n");
	fprintf(ASM,"	scanint:	dw \"%cd\", 0\n",37);
	fprintf(ASM,"	ft:	db \"a=%cd\", 10, 0\n",37);	
	
}

void codegen_main(parseTree *PT){
	ASM= fopen("codegen.asm","w");
	bool_no=0;
	skip=0;
	itr_no=0;
	fprintf(ASM,"extern printf\n");
	fprintf(ASM,"extern scanf\n\n");
	
	treeNode *AST=PT->root; 
	bss();
	
	data();
	
	fprintf(ASM,"\nsection .text\n\n");
	fprintf(ASM,"global main\n");
	
	start(AST);

	fprintf(ASM,"\n	pop rbp\n");
	fprintf(ASM,"	ret\n");
	
}
