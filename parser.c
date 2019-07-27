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
#include "lexer.h"

//Instantiate stack
Stack *createStack(){
    Stack *S;
    S=(Stack *)malloc(sizeof(Stack));
    int i=0;
    for(i=0;i<NO_OF_SYMBOLS;i++){
      S->symbolValue[i]=NULL;
    }
    S->size=0;
    
    return S;
}

//Push element on top of stack
void push(Stack *S,treeNode* symbolValue){
    if(S->size>=NO_OF_SYMBOLS){
        return;
     }
     else{
        S->symbolValue[S->size]=symbolValue;
        S->size++;
     }
     return;
}

//remove element from stack
treeNode* pop(Stack *S){
    treeNode* poppedValue;
    if(S->size==0) return NULL;   
    else{
        poppedValue=S->symbolValue[S->size-1];
        S->symbolValue[S->size-1]=NULL;
        S->size--;
    }
    
    return poppedValue;
}

//returns top element of stack
treeNode* top(Stack *S){
    if(S->size==0)
        return NULL;
    else
        return S->symbolValue[S->size-1];
}

int lookup_symbol(char *non_terminal){  //lookup value for symbols

    //Non terminals
	if(strcmp(non_terminal, "<program>") == 0)return 0;
	if(strcmp(non_terminal, "<mainFunction>") == 0)return 1;
	if(strcmp(non_terminal, "<otherFunctions>") == 0)return 2;
	if(strcmp(non_terminal, "<function>") == 0)return 3;
	if(strcmp(non_terminal, "<input_par>") == 0)return 4;
	if(strcmp(non_terminal, "<output_par>") == 0)return 5;
	if(strcmp(non_terminal, "<parameter_list>") == 0)return 6;
	if(strcmp(non_terminal, "<dataType>") == 0)return 7;
	if(strcmp(non_terminal, "<primitiveDatatype>") == 0)return 8;
	if(strcmp(non_terminal, "<constructedDatatype>") == 0)return 9;
	if(strcmp(non_terminal, "<remaining_list>") == 0)return 10;
	if(strcmp(non_terminal, "<stmts>") == 0)return 11;
	if(strcmp(non_terminal, "<typeDefinitions>") == 0)return 12;
	if(strcmp(non_terminal, "<typeDefinition>") == 0)return 13;
	if(strcmp(non_terminal, "<fieldDefinitions>") == 0)return 14;
	if(strcmp(non_terminal, "<fieldDefinition>") == 0)return 15;
	if(strcmp(non_terminal, "<moreFields>") == 0)return 16;
	if(strcmp(non_terminal, "<declarations>") == 0)return 17;
	if(strcmp(non_terminal, "<declaration>") == 0)return 18;
	if(strcmp(non_terminal, "<global_or_not>") == 0)return 19;
	if(strcmp(non_terminal, "<otherStmts>") == 0)return 20;
	if(strcmp(non_terminal, "<stmt>") == 0)return 21;
	if(strcmp(non_terminal, "<assignmentStmt>") == 0)return 22;
	if(strcmp(non_terminal, "<singleOrRecId>") == 0)return 23;
	if(strcmp(non_terminal, "<new_24>") == 0)return 24;
	if(strcmp(non_terminal, "<funCallStmt>") == 0)return 25;
	if(strcmp(non_terminal, "<outputParameters>") == 0)return 26;
	if(strcmp(non_terminal, "<inputParameters>") == 0)return 27;
	if(strcmp(non_terminal, "<iterativeStmt>") == 0)return 28;
	if(strcmp(non_terminal, "<conditionalStmt>") == 0)return 29;
	if(strcmp(non_terminal, "<elsePart>") == 0)return 30;
	if(strcmp(non_terminal, "<ioStmt>") == 0)return 31;
	if(strcmp(non_terminal, "<allVar>") == 0)return 32;
	if(strcmp(non_terminal, "<arithmeticExpression>") == 0)return 33;
	if(strcmp(non_terminal, "<expPrime>") == 0)return 34;
	if(strcmp(non_terminal,"<term>") == 0)return 35;
	if(strcmp(non_terminal, "<termPrime>") == 0)return 36;
	if(strcmp(non_terminal, "<factor>") == 0)return 37;
	if(strcmp(non_terminal, "<highPrecedenceOperators>") == 0)return 38;
	if(strcmp(non_terminal, "<lowPrecedenceOperators>") == 0)return 39;	
	if(strcmp(non_terminal, "<all>") == 0)return 40;		
    if(strcmp(non_terminal, "<temp>") == 0)return 41;
	if(strcmp(non_terminal, "<booleanExpression>") == 0)return 42;
	if(strcmp(non_terminal, "<var>") == 0)return 43;	    
    if(strcmp(non_terminal, "<logicalOp>") == 0)return 44;
	if(strcmp(non_terminal, "<relationalOp>") == 0)return 45;
	if(strcmp(non_terminal, "<returnStmt>") == 0)return 46;
	if(strcmp(non_terminal, "<optionalReturn>") == 0)return 47;
	if(strcmp(non_terminal, "<idList>") == 0)return 48;	
	if(strcmp(non_terminal, "<more_ids>") == 0)return 49;
	if(strcmp(non_terminal, "<allVar1>") == 0)return 50;
	
	//Temrinals
	if(strcmp(non_terminal, "TK_ASSIGNOP") == 0)return 51;
	if(strcmp(non_terminal, "TK_COMMENT") == 0)return 52;
	if(strcmp(non_terminal, "TK_FIELDID") == 0)return 53;
	if(strcmp(non_terminal, "TK_ID") == 0)return 54;
	if(strcmp(non_terminal, "TK_NUM") == 0)return 55;
	if(strcmp(non_terminal, "TK_RNUM") == 0)return 56;
	if(strcmp(non_terminal, "TK_FUNID") == 0)return 57;
	if(strcmp(non_terminal, "TK_RECORDID") == 0)return 58;
	if(strcmp(non_terminal, "TK_WITH") == 0)return 59;
	if(strcmp(non_terminal, "TK_PARAMETERS") == 0)return 60;
	if(strcmp(non_terminal, "TK_END") == 0)return 61;
	if(strcmp(non_terminal, "TK_WHILE") == 0)return 62;
	if(strcmp(non_terminal, "TK_INT") == 0)return 63;	
	if(strcmp(non_terminal, "TK_REAL") == 0)return 64;
	if(strcmp(non_terminal, "TK_TYPE") == 0)return 65;
	if(strcmp(non_terminal, "TK_MAIN") == 0)return 66;
	if(strcmp(non_terminal, "TK_GLOBAL") == 0)return 67;
	if(strcmp(non_terminal, "TK_LIST") == 0)return 68;
	if(strcmp(non_terminal, "TK_SQL") == 0)return 69;
	if(strcmp(non_terminal, "TK_SQR") == 0)return 70;
	if(strcmp(non_terminal, "TK_INPUT") == 0)return 71;
	if(strcmp(non_terminal, "TK_SEM") == 0)return 72;
	if(strcmp(non_terminal, "TK_COLON") == 0)return 73;
	if(strcmp(non_terminal, "TK_DOT") == 0)return 74;
	if(strcmp(non_terminal, "TK_ENDWHILE") == 0)return 75;
	if(strcmp(non_terminal, "TK_OP") == 0)return 76;
	if(strcmp(non_terminal, "TK_CL") == 0)return 77;
	if(strcmp(non_terminal, "TK_IF") == 0)return 78;
	if(strcmp(non_terminal, "TK_THEN") == 0)return 79;
	if(strcmp(non_terminal, "TK_ENDIF") == 0)return 80;
	if(strcmp(non_terminal, "TK_READ") == 0)return 81;
	if(strcmp(non_terminal, "TK_WRITE") == 0)return 82;
	if(strcmp(non_terminal, "TK_RETURN") == 0)return 83;
	if(strcmp(non_terminal, "TK_PLUS") == 0)return 84;
	if(strcmp(non_terminal, "TK_MINUS") == 0)return 85;
	if(strcmp(non_terminal, "TK_MUL") == 0)return 86;
	if(strcmp(non_terminal, "TK_DIV") == 0)return 87;		
	if(strcmp(non_terminal, "TK_CALL") == 0)return 88;
	if(strcmp(non_terminal, "TK_RECORD") == 0)return 89;
	if(strcmp(non_terminal, "TK_ENDRECORD") == 0)return 90;
	if(strcmp(non_terminal, "TK_ELSE") == 0)return 91;
	if(strcmp(non_terminal, "TK_AND") == 0)return 92;
	if(strcmp(non_terminal, "TK_OR") == 0)return 93;
	if(strcmp(non_terminal,"TK_NOT")==0) return 94;
	if(strcmp(non_terminal,"TK_LT")==0) return 95;
	if(strcmp(non_terminal,"TK_LE")==0) return 96;
	if(strcmp(non_terminal,"TK_EQ")==0) return 97;
	if(strcmp(non_terminal,"TK_GT")==0) return 98;
	if(strcmp(non_terminal,"TK_NE")==0) return 99;
	if(strcmp(non_terminal,"TK_COMMA")==0) return 100;
    if(strcmp(non_terminal, "TK_PARAMETER") == 0)return 101;
    if(strcmp(non_terminal, "TK_OUTPUT") == 0)return 102;
    if(strcmp(non_terminal, "TK_GE") == 0)return 103;
    
    //epsilon
    if(strcmp(non_terminal, "eps") == 0)return 104;
    
    //end marker symbol
    if(strcmp(non_terminal, "$") == 0)return 105;
    
    //errors
    if(strcmp(non_terminal, "LEN_ERROR") == 0)return 106;
    if(strcmp(non_terminal, "UN_PATT") == 0)return 107;
    if(strcmp(non_terminal, "UN_SYM") == 0)return 108;
    if(strcmp(non_terminal, "LEN1_ERROR") == 0)return 109;
    
    //end of file symbol
    if(strcmp(non_terminal, "EOF") == 0)return 110;
	else return -1;
}


char * reverse_lookup_non_terminal(int number) //original  symbol corresponing to lookup value
{
    //non-terminals
    if(number ==0) return "<program>";
	if(number ==1) return "<mainFunction>";
	if(number ==2) return "<otherFunctions>";
	if(number ==3) return "<function>";
	if(number ==4) return "<input_par>";
	if(number ==5) return "<output_par>";
	if(number ==6) return "<parameter_list>";
	if(number ==7) return "<dataType>";
	if(number ==8) return "<primitiveDatatype>";
	if(number ==9) return "<constructedDatatype>";
	if(number ==10) return "<remaining_list>";
	if(number ==11) return "<stmts>";
	if(number ==12) return "<typeDefinitions>";
	if(number ==13) return "<typeDefinition>";
	if(number ==14) return "<fieldDefinitions>";
	if(number ==15) return "<fieldDefinition>";
	if(number ==16) return "<moreFields>";
	if(number ==17) return "<declarations>";
	if(number ==18) return "<declaration>";
	if(number ==19) return "<global_or_not>";
	if(number ==20) return "<otherStmts>";
	if(number ==21) return "<stmt>";
	if(number ==22) return "<assignmentStmt>";
	if(number ==23) return "<singleOrRecId>";
	if(number ==24) return "<new_24>";
	if(number ==25) return "<funCallStmt>";
	if(number ==26) return "<outputParameters>";
	if(number ==27) return "<inputParameters>";
	if(number ==28) return "<iterativeStmt>";
	if(number ==29) return "<conditionalStmt>";
	if(number ==30) return "<elsePart>";
	if(number ==31) return "<ioStmt>";
	if(number ==32) return "<allVar>";
	if(number ==33) return "<arithmeticExpression>";
	if(number ==34) return "<expPrime>";
	if(number ==35) return "<term>";
	if(number ==36) return "<termPrime>";
	if(number ==37) return "<factor>";
	if(number ==38) return "<highPrecedenceOperators>";
	if(number ==39) return "<lowPrecedenceOperators>";
	if(number ==40) return "<all>";
	if(number ==41) return "<temp>";
	if(number ==42) return "<booleanExpression>";
	if(number ==43) return "<var>";
	if(number ==44) return "<logicalOp>";
	if(number ==45) return "<relationalOp>";
	if(number ==46) return "<returnStmt>";
	if(number ==47) return "<optionalReturn>";
	if(number ==48) return "<idList>";
	if(number ==49) return "<more_ids>";
	if(number ==50) return "<allVar1>";
	
	//Terminals
	if(number ==51) return "TK_ASSIGNOP";
	if(number ==52) return "TK_COMMENT";
	if(number ==53) return "TK_FIELDID";
	if(number ==54) return "TK_ID";
	if(number ==55) return "TK_NUM";
	if(number ==56) return "TK_RNUM";
	if(number ==57) return "TK_FUNID";
	if(number ==58) return "TK_RECORDID";
	if(number ==59) return "TK_WITH";
	if(number ==60) return "TK_PARAMETERS";
	if(number ==61) return "TK_END";
	if(number ==62) return "TK_WHILE";
	if(number ==63) return "TK_INT";
	if(number ==64) return "TK_REAL";
	if(number ==65) return "TK_TYPE";
	if(number ==66) return "TK_MAIN";
	if(number ==67) return "TK_GLOBAL";
	if(number ==68) return "TK_LIST";
	if(number ==69) return "TK_SQL";
	if(number ==70) return "TK_SQR";
	if(number ==71) return "TK_INPUT";
	if(number ==72) return "TK_SEM";
	if(number ==73) return "TK_COLON";
	if(number ==74) return "TK_DOT";
	if(number ==75) return "TK_ENDWHILE";
	if(number ==76) return "TK_OP";
	if(number ==77) return "TK_CL";
	if(number ==78) return "TK_IF";
	if(number ==79) return "TK_THEN";	
	if(number ==80) return "TK_ENDIF";
	if(number ==81) return "TK_READ";
	if(number ==82) return "TK_WRITE";
	if(number ==83) return "TK_RETURN";
	if(number ==84) return "TK_PLUS";
	if(number ==85) return "TK_MINUS";
	if(number ==86) return "TK_MUL";
	if(number ==87) return "TK_DIV";
	if(number ==88) return "TK_CALL";
	if(number ==89) return "TK_RECORD";
	if(number ==90) return "TK_ENDRECORD";
	if(number==91) return "TK_ELSE";
	if(number == 92)return "TK_AND";
	if(number== 93) return "TK_OR";
	if(number== 94) return "TK_NOT";
	if(number == 95) return "TK_LT";
	if(number==96) return "TK_LE";
	if(number ==97) return "TK_EQ";
	if(number ==98) return "TK_GT";
	if(number ==99) return "TK_NE";
	if(number ==100) return "TK_COMMA";
	if(number ==101) return "TK_PARAMETER";
	if(number ==102) return "TK_OUTPUT";
	if(number ==103) return "TK_GE";
	
	//epsilon
    if(number ==104) return "eps";
    
    //end marker symbol
    if(number ==105) return "$";
    
    //errors
    if(number ==106) return "LEN_ERROR";
    if(number ==107) return "UN_PATT";   
    if(number ==108) return "UN_SYM"; 
    if(number ==109) return "LEN1_ERROR";
    
    //end of file symbol    
    if(number ==110) return "EOF";                     
	else return NULL;

}

int containsEpsilonRHS(int lookupNoRHS){ //list of non-terminals with epsilon RHS
    if(lookupNoRHS==lookup_symbol("<otherFunctions>") || lookupNoRHS==lookup_symbol("<output_par>") || lookupNoRHS==lookup_symbol("<remaining_list>") || lookupNoRHS==lookup_symbol("<moreFields>")|| lookupNoRHS==lookup_symbol("<declarations>")|| lookupNoRHS==lookup_symbol("<global_or_not>") || lookupNoRHS==lookup_symbol("<otherStmts>") || lookupNoRHS==lookup_symbol("<new_24>") || lookupNoRHS==lookup_symbol("<outputParameters>") || lookupNoRHS==lookup_symbol("<allVar1>") || lookupNoRHS==lookup_symbol("<expPrime>") || lookupNoRHS==lookup_symbol("<termPrime>") || lookupNoRHS==lookup_symbol("<temp>") || lookupNoRHS==lookup_symbol("<optionalReturn>") || lookupNoRHS==lookup_symbol("<more_ids>")){
        return 1;
    }
    
    return 0;
}

void addNTtoLoadedGrammar(int looked_up_value, int rule_count){ //function to add LHS NT to grammar
	Rule->ruleArray[rule_count-1].ruleNo = rule_count;
	Rule->ruleArray[rule_count-1].NTvalue = looked_up_value;
	return;
}

void addRHStoLoadedGrammar(int looked_up_value, int rule_count){ //create RHS grammar Node
	ruleNode *new_node = (ruleNode *) malloc(sizeof(ruleNode));
	new_node->value = looked_up_value;
	if(looked_up_value<NO_OF_NTS){
		new_node->isTerminal = 0;
	}
	else{
		new_node->isTerminal = 1;
	}
	new_node->next = NULL;
	
	ruleNode *temp = Rule->ruleArray[rule_count-1].rHead;
	if(temp == NULL){
		Rule->ruleArray[rule_count-1].rHead = new_node;
		Rule->ruleArray[rule_count-1].rHead->next = NULL;
		return;
	}
	while((temp->next)!=NULL){	
		temp = temp->next;	
	}
	temp->next = new_node;
	return;
}

void loadGrammar(FILE *grammar){ //read grammar from file and store in data structure
	char *rule = NULL; //rule read from file
	size_t len = 0; 
	ssize_t read; //read line of
	char *tokenized; //tokenized symbol from grammar file
	char rule_token[300]; 
	const char delim[2] = " ";
	int rule_count = 1; //number of rules
	int RHS_count; //number of RHS grammar rules
	int looked_up_value; //lookup value of symbol
	while ((read = getline(&rule, &len, grammar)) != -1) {
	   memset(rule_token, 0, 300);
	   strcpy(rule_token, rule);
	   tokenized = strtok(rule_token, delim);
	   looked_up_value = lookup_symbol(tokenized);
	   addNTtoLoadedGrammar(looked_up_value, rule_count);
	   RHS_count = 0;
	   while((tokenized = strtok(NULL, delim))!=NULL){
		if(RHS_count == 0){
			RHS_count++;
		}
		else{
			if(*tokenized == ' ' || *tokenized == '\n' || *tokenized == '\t'){ //possible delimiters 
				continue;		
			}
		    looked_up_value = lookup_symbol(tokenized);
			addRHStoLoadedGrammar(looked_up_value, rule_count);
			RHS_count++;
		}	
	   }
	   rule_count++;
        }	
	return;
}

void addLHStoSet(int looked_up_value){ //function to add LHS terminals to first/follow sets
	firstSet->setArray[looked_up_value].Svalue = looked_up_value;
	return;
}

//function to traverse RHS of a rule/set and return true if RHS contains a given symbol
int checkList(ruleNode *l1,int n){
    while(l1!=NULL){
        if(l1->value==n){
            return 0;    
         }
         l1=l1->next;
    }

    return 1;
}

//function to merge two given first sets for first set generation
void appendLists(int l1,int l2){
    ruleNode *t1=firstSet->setArray[l1].rHead;
    ruleNode *t2=firstSet->setArray[l2].rHead;
   
    ruleNode *t21=firstSet->setArray[l2].rHead;
    ruleNode *temp;
    
    int i=0;
    while(t2!=NULL){
        i++;
        if(i>1 || (i==1 && t2->next!=NULL)){
            if(t2->value==lookup_symbol("eps")) {
                t2=t2->next;
                continue;
            }
        }
        
        if(checkList(firstSet->setArray[l1].rHead, t2->value)==1){    
        temp=(ruleNode *)malloc(sizeof(ruleNode));
        temp->value=t2->value;
        temp->isTerminal=t2->isTerminal;
        temp->next=firstSet->setArray[l1].rHead;
        firstSet->setArray[l1].rHead=temp;
        }
        t2=t2->next;
     }
     
} 

//function to create firstset automatically
void createFirstSet(int i){
    firstSet->setArray[i].Svalue=i; //initialize first set of given symbol
   if(i>=NO_OF_NTS){ 
       return; //first set of terminal is terminal itself
    }else{
        int j=0;   
        int flag=0;   
        for(j=0;j<NO_OF_RULES;j++){ //iterate through rules to find rules corresponding to given non temrinal
            int ruleNo=Rule->ruleArray[j].NTvalue;
            if(ruleNo==i){
                ruleNode *traverseNode=Rule->ruleArray[j].rHead; //Xi of grammar rule
                do{
                    createFirstSet(traverseNode->value);                  
                    appendLists(i,traverseNode->value);
                    ruleNode *temp=firstSet->setArray[traverseNode->value].rHead;
                        
                       while(temp!=NULL){ //traverse first set of Yi
                            if(temp->value==lookup_symbol("eps")){
                                flag=1;
                                break;
                            }else {
                                flag=0;
                            }
                            temp=temp->next;
                        } 

                    traverseNode=traverseNode->next; 
                
                }while(traverseNode!=NULL && flag==1);
                    
            }
               
        }
        return;
    }
        
       return;  
}

//function to append firstset and followset for follow set generation
void appendFirstInFollow(int l1,int l2){

    ruleNode *t1=followSet->setArray[l1].rHead;
    ruleNode *t2=firstSet->setArray[l2].rHead;
   
    ruleNode *temp;
    
    
    while(t2!=NULL){

            if(t2->value==lookup_symbol("eps")) {
                t2=t2->next;
                continue;
            }

        if(checkList(followSet->setArray[l1].rHead, t2->value)==1){    
        temp=(ruleNode *)malloc(sizeof(ruleNode));
        temp->value=t2->value;
        temp->isTerminal=t2->isTerminal;
        temp->next=followSet->setArray[l1].rHead;
        followSet->setArray[l1].rHead=temp;
        }
       
        t2=t2->next;
     }
  
}

//function to append two followsets for follow set generation
void appendFollowInFollow(int l1,int l2){

    ruleNode *t1=followSet->setArray[l1].rHead;
    ruleNode *t2=followSet->setArray[l2].rHead;
   
    ruleNode *temp;
    
    while(t2!=NULL){
        if(t2->value==lookup_symbol("eps")){
            t2=t2->next;
            continue;
            }
        
        
        if(checkList(followSet->setArray[l1].rHead, t2->value)==1){    
        temp=(ruleNode *)malloc(sizeof(ruleNode));
        temp->value=t2->value;
        temp->isTerminal=t2->isTerminal;
        temp->next=followSet->setArray[l1].rHead;
        followSet->setArray[l1].rHead=temp;
        }
       
        t2=t2->next;
     }  
}

//visited array to track followsets already formed

//funtion to generate followsets of non terminals automatically
void createFollowSet(int i){
    if(!visited[i]){ //if a non terminal symbol is not visited already
    visited[i]=1; //mark non terminal as visited
    followSet->setArray[i].Svalue=i; 
    int j=0;
    for(j=0;j<NO_OF_RULES;j++){ //traverse through rules to find occurence of non terminals
         int B,beta;
         ruleNode *temp=Rule->ruleArray[j].rHead;
         int A=Rule->ruleArray[j].NTvalue;
         
         //check if required non terminal occurs in RHS of rule j
         while(temp!=NULL){
            if(temp->value==i){ //RHS symbol of the rule in which no terminal of which follow set is to be formed occurs
                B=i;           
                break;
            }

            temp=temp->next;
         }

        if(temp==NULL) continue; //search next rule if RHS doesn't contain the required non terminal of which follow set is to be formed occurs
        
        int flag=1;
        while(temp->next!=NULL){

            int beta=temp->next->value;
            appendFirstInFollow(B,beta); //if there is a production A->alpha B beta, then everything in FIRST(beta) except epsilon is in FOLLOW(B)
            ruleNode *temp1=firstSet->setArray[beta].rHead;
            while(temp1!=NULL){
                if(temp1->value==lookup_symbol("eps")){ //if symbols of beta contains epsilon go to next symbol in beta
                    temp=temp->next;
                    flag=0; 
                    break;
                }else{
                    flag=1;
                    }
                    temp1=temp1->next;
            }
            
            if(flag==1) break; //if FIRST(beta) doesn't contain epsilon end the follow set of B
            
        }
        if(temp!=NULL && temp->next==NULL){ //if there is a production A->alpha B, or a production A->alpha B beta, where FIRST(beta) contains epsilon, then everything in FOLLOW(A) is in FOLLOW(B)
            
            if(!visited[A])
                createFollowSet(A);
            appendFollowInFollow(B,A);
        }
        
    }
    
    return;
}else{
    return;
}
}

//If epsilon is in FIRST(alpha), then for each terminal b in FOLLOW(A), add A->alpha to M[A,b].If epsilon is in FIRST(alpha) and $ is in FOLLOW(A),add A->alpha to M[A,$] as well.
void fill_current_symbol_follow_to_ParseTable(int left_non_terminal_index, int rule_number, ruleNode* follow_set_list){
	if(follow_set_list == NULL){
		return;
	}
	int terminal_index;
	ruleNode* traversing_temp = follow_set_list;
	
	while(follow_set_list!=NULL){
		//List traversal and append.
		terminal_index = follow_set_list->value-NO_OF_NTS;		
		ParseTable[left_non_terminal_index][terminal_index] = rule_number;
		follow_set_list = follow_set_list->next;
	}
	return;
}

//function to check epsilon and add A->alpha to M[A,a] for each terminal a is FIRST(alpha)  
int fill_current_symbol_first_to_ParseTable( int left_non_terminal_index, int rule_number, ruleNode* first_set_list){
	//Returns 0 if epsion not present and 1 if present.
	
	int flag = 0;
	if(first_set_list == NULL){
		return 0;
	}
	
	int terminal_index;
	
	while(first_set_list!=NULL){
		//List traversal and append.
		terminal_index = first_set_list->value-NO_OF_NTS;		
		if(first_set_list->value == lookup_symbol("eps")){
			//epsilon Found.
			flag = 1;
			first_set_list = first_set_list->next;
			continue;
		}
		
		ParseTable[left_non_terminal_index][terminal_index] = rule_number;
		first_set_list = first_set_list->next;
	}
	return flag;
}

//function to create and fill parse table
void createParseTable(){
    int i=0;
	for(i=0;i<NO_OF_RULES;i++) //For each production A->alpha of the grammar, do the following:
	{
		ruleNode* current_ptr = Rule->ruleArray[i].rHead;  //(alpha) pointer to first symbol on RHS of grammar rule
		int left_non_terminal_index = Rule->ruleArray[i].NTvalue; //LHS(A) of grammar rule
		int rule_number=i;
		int column_index;
	    int isEpsilonPresent = 0; //set when epsilon is present
	
	//For each temrinal a in FIRST(alpha),add A->alpha to M[A,a]
	while(current_ptr!=NULL)
	{
		if(current_ptr->isTerminal)
		{
			column_index=current_ptr->value-NO_OF_NTS;
			if(current_ptr->value != lookup_symbol("eps")){
					ParseTable[left_non_terminal_index][column_index] = rule_number;
				}
				
			else{
				ruleNode* follow_set_list = followSet->setArray[left_non_terminal_index].rHead;	
				fill_current_symbol_follow_to_ParseTable(left_non_terminal_index, rule_number, follow_set_list);
			}
			break;		
		
		}
		else{ 
//Non Terminal Symbol. Need to Add all terminals in first of this and check if epsilon present. M[A, a] = rule_number, a is FIRST(alpha).
			ruleNode* first_set_list = firstSet->setArray[current_ptr->value].rHead;
			isEpsilonPresent = fill_current_symbol_first_to_ParseTable(left_non_terminal_index, rule_number, first_set_list);
            
//If epsilon is in FIRST(alpha), then for each terminal b in FOLLOW(A), add A->alpha to M[A,b].If epsilon is in FIRST(alpha) and $ is in FOLLOW(A),add A->alpha to M[A,$] as well. 
			if(current_ptr->next == NULL && isEpsilonPresent){
				ruleNode* follow_set_list = followSet->setArray[left_non_terminal_index].rHead;	
				fill_current_symbol_follow_to_ParseTable(left_non_terminal_index, rule_number, follow_set_list);
				break;
			}
			if(!isEpsilonPresent){
				//Done with insertion.
				break;
			}
		}
		current_ptr = current_ptr->next;	
    }   		
}
}


//Fucntion to check if follow set corresponding to a particular non terminal contains a given symbol(Also acts as synch bit)
int checkFollow(int NTvalue,int RHSvalue){
    ruleNode *temp=followSet->setArray[NTvalue].rHead;
    while(temp!=NULL){
        if(temp->value==RHSvalue) return 1;
        temp=temp->next;
    }
    
    return 0;   
}

//function to create a node of parse tree
treeNode *createTreeNode(char *lexemeCurrentNode,int lineNo,char *token,char *valueIfNumber,char *parentNodeSymbol,int isLeafNode,char *nodeSymbol,treeNode *child,treeNode *next){
    treeNode *node=(treeNode*)malloc(sizeof(treeNode));
    
    node->lexemeCurrentNode=lexemeCurrentNode;
    node->lineNo=lineNo;
    node->token=token;
    node->valueIfNumber=valueIfNumber;
    node->parentNodeSymbol=parentNodeSymbol;
    node->isLeafNode=isLeafNode;
    node->nodeSymbol=nodeSymbol;
    
    node->child=child;
    node->next=NULL;
    
    return node;   
}

parseTree *createTree(){
    parseTree *t=(parseTree *)malloc(sizeof(parseTree));
    return t;
}



//function takes as input the source code file and parses using the rules as per the predictive parse table 
parseTree *parseInputSourceCode(char *testcaseFile){
      lexer_main(testcaseFile);  //initiate lexer
      parseTree *Ptree=createTree();//initialize parse tree
          
      int errorFlag=0; //set is there is error in code
      Stack *stack=createStack(); //create stack to perform predictive parsing
      
      treeNode *dollar=createTreeNode("$",-1,"$","","",0,"$",NULL,NULL); //create end of start symbol
      push(stack,dollar); //push end of stack symbol
      
      treeNode *start=createTreeNode("----",-1,"-","-","-",0,"<program>",NULL,NULL);
      Ptree->root=start;
      push(stack,start); //push start symbol of grammar
      
      tokenInfo *token=getNextToken(F); //get first token from code
      int a=lookup_symbol(token->token); //Let a be the first symbol of code
      int messageFlag=0;
      treeNode *removed; //node removed from stack
      int X=lookup_symbol(top(stack)->nodeSymbol); //Let X be top of the stack symbol
      
      while(X!=lookup_symbol("$")){  //iterate while stack is not empty
       if(X==lookup_symbol("eps")){ //pop epsilon from stack
        removed=pop(stack);
       }
       else if(X==a){ //pop the stack and let a be next symbol of code
            removed=pop(stack);
            if(lookup_symbol(removed->nodeSymbol)>=NO_OF_NTS){ //assign desired features to parse tree nodes
                removed->lexemeCurrentNode=token->lexeme;
                removed->lineNo=token->lineNo+1;
                removed->token=token->token;
            }
            
            if(Buffer[(bufferPointer+1)%BUFFER_SIZE]!='\0'){ //call lexer's getNextToken till buffer is empty
                token=getNextToken(F);
                a=lookup_symbol(token->token);
            }else{ //if buffer reaches end of code complete the parsing
                X=lookup_symbol(top(stack)->nodeSymbol);
                while(containsEpsilonRHS(X)==1){
                    removed=pop(stack);
                    X=lookup_symbol(top(stack)->nodeSymbol);
                }
                if(lookup_symbol(top(stack)->nodeSymbol)==lookup_symbol("$")){
                    if(!errorFlag){ 
                        if(!messageFlag)
                            //printf("\nCompiled Successfully: Input source code is syntactically correct!!\n");
                        messageFlag++;
                        }
                    break;
               }else{ //handle the error and display the error message
                     errorFlag=1;
                    if(a==lookup_symbol("LEN_ERROR")){
                printf("ERROR 1: Identifier at line <%d> is longer than the prescribed length of 20 characters.\n",token->lineNo+1);
                token=getNextToken(F);
                a=lookup_symbol(token->token);

                continue;
            }else  if(a==lookup_symbol("LEN1_ERROR")){
                printf("ERROR 1: Function identifier at line <%d> is longer than the prescribed length of 30 characters.\n",token->lineNo+1);
                token=getNextToken(F);
                a=lookup_symbol(token->token);

                continue;
            }else if(a==lookup_symbol("UN_PATT")){
                printf("ERROR 3: Unknown pattern <%s> at line number <%d>\n",token->lexeme,token->lineNo+1);
                token=getNextToken(F);
                a=lookup_symbol(token->token);

                    continue;
            }else if(a==lookup_symbol("UN_SYM")){
                printf("ERROR_2: Unknown Symbol <%s> at line<%d>\n",token->lexeme,token->lineNo+1);
                token=getNextToken(F);
                a=lookup_symbol(token->token);

                      continue;
            }else if(a==lookup_symbol("EOF")){
                printf("ERROR_4: Input is consumed while it is expected to have token <%s> at line number <%d>\n",reverse_lookup_non_terminal(X),token->lineNo);
                     break;
            }else{
                if(X>=NO_OF_NTS){
                printf("ERROR_5: The token <%s> for lexeme <%s>  does not match at line <%d>. The expected token here is <%s>.\n", reverse_lookup_non_terminal(a), token->lexeme, token->lineNo+1,reverse_lookup_non_terminal(X)); 
                }else{
                printf("ERROR_5: The token <%s> for lexeme <%s>  does not match at line <%d>. The expected token here is of type <%s>.\n", reverse_lookup_non_terminal(a), token->lexeme, token->lineNo+1,reverse_lookup_non_terminal(X));
                }
               
            }
            //Error recovery in panic mode
                     while(containsEpsilonRHS(X)){
                     if(stack->size>2){
                         removed=pop(stack);
                            X=lookup_symbol(top(stack)->nodeSymbol);
                            }else{
                            token=getNextToken(F);
                            a=lookup_symbol(token->token);
                            if(a==lookup_symbol("EOF")) break;
                            }
                           
                    }
                    while(1){

                        if((!checkFollow(X,a)) && X<NO_OF_NTS){
                            token=getNextToken(F);
                            a=lookup_symbol(token->token);
                            if(a==lookup_symbol("EOF")) break;
                        }else{
                            if(stack->size>2){
                            removed=pop(stack);
                            X=lookup_symbol(top(stack)->nodeSymbol);
                            }else{
                                token=getNextToken(F);
                            a=lookup_symbol(token->token);
                            if(a==lookup_symbol("EOF")) break;
                            }
                            break;
                        }
                    }
                continue;
                }         
            }
            
        }else if(X>=NO_OF_NTS){ //display error()
        //handle the error and display the error message
                                 errorFlag=1;
                    if(a==lookup_symbol("LEN_ERROR")){
                printf("ERROR 1: Identifier at line <%d> is longer than the prescribed length of 20 characters.\n",token->lineNo+1);
                token=getNextToken(F);
                a=lookup_symbol(token->token);

                continue;
            }else  if(a==lookup_symbol("LEN1_ERROR")){
                printf("ERROR 1: Function identifier at line <%d> is longer than the prescribed length of 30 characters.\n",token->lineNo+1);
                token=getNextToken(F);
                a=lookup_symbol(token->token);

                continue;
            }else if(a==lookup_symbol("UN_PATT")){
                printf("ERROR 3: Unknown pattern <%s> at line number <%d>\n",token->lexeme,token->lineNo+1);
                token=getNextToken(F);
                a=lookup_symbol(token->token);

                    continue;
            }else if(a==lookup_symbol("UN_SYM")){
                printf("ERROR_2: Unknown Symbol <%s> at line<%d>\n",token->lexeme,token->lineNo+1);
                token=getNextToken(F);
                a=lookup_symbol(token->token);

                      continue;
            }else if(a==lookup_symbol("EOF")){
                printf("ERROR_4: Input is consumed while it is expected to have token <%s> at line number <%d>\n",reverse_lookup_non_terminal(X),token->lineNo);
                     break;
            }else{
                if(X>=NO_OF_NTS){
                printf("ERROR_5: The token <%s> for lexeme <%s>  does not match at line <%d>. The expected token here is <%s>.\n", reverse_lookup_non_terminal(a), token->lexeme, token->lineNo+1,reverse_lookup_non_terminal(X)); 
                }else{
                printf("ERROR_5: The token <%s> for lexeme <%s>  does not match at line <%d>. The expected token here is of type <%s>.\n", reverse_lookup_non_terminal(a), token->lexeme, token->lineNo+1,reverse_lookup_non_terminal(X));
                }
               
            }
            //Error recovery in panic mode
                     while(containsEpsilonRHS(X)){
                     if(stack->size>2){
                         removed=pop(stack);
                            X=lookup_symbol(top(stack)->nodeSymbol);
                            }else{
                            token=getNextToken(F);
                            a=lookup_symbol(token->token);
                            if(a==lookup_symbol("EOF")) break;
                            }
                           
                    }
                    while(1){

                        if((!checkFollow(X,a)) && X<NO_OF_NTS){
                            token=getNextToken(F);
                            a=lookup_symbol(token->token);
                            if(a==lookup_symbol("EOF")) break;
                        }else{
                            if(stack->size>2){
                            removed=pop(stack);
                            X=lookup_symbol(top(stack)->nodeSymbol);
                            }else{
                                token=getNextToken(F);
                                a=lookup_symbol(token->token);
                            if(a==lookup_symbol("EOF")) break;
                            }
                            break;
                        }
                    }
                continue;
        }else if(ParseTable[X][a-NO_OF_NTS]==-1){ //error entry in parse table 
                     //handle the error and display the error message
                                 errorFlag=1;
                    if(a==lookup_symbol("LEN_ERROR")){
                printf("ERROR 1: Identifier at line <%d> is longer than the prescribed length of 20 characters.\n",token->lineNo+1);
                token=getNextToken(F);
                a=lookup_symbol(token->token);

                continue;
            }else  if(a==lookup_symbol("LEN1_ERROR")){
                printf("ERROR 1: Function identifier at line <%d> is longer than the prescribed length of 30 characters.\n",token->lineNo+1);
                token=getNextToken(F);
                a=lookup_symbol(token->token);

                continue;
            }else if(a==lookup_symbol("UN_PATT")){
                printf("ERROR 3: Unknown pattern <%s> at line number <%d>\n",token->lexeme,token->lineNo+1);
                token=getNextToken(F);
                a=lookup_symbol(token->token);

                    continue;
            }else if(a==lookup_symbol("UN_SYM")){
                printf("ERROR_2: Unknown Symbol <%s> at line<%d>\n",token->lexeme,token->lineNo+1);
                token=getNextToken(F);
                a=lookup_symbol(token->token);

                      continue;
            }else if(a==lookup_symbol("EOF")){
                printf("ERROR_4: Input is consumed while it is expected to have token <%s> at line number <%d>\n",reverse_lookup_non_terminal(X),token->lineNo);
                     break;
            }else{
                if(X>=NO_OF_NTS){
                printf("ERROR_5: The token <%s> for lexeme <%s>  does not match at line <%d>. The expected token here is <%s>.\n", reverse_lookup_non_terminal(a), token->lexeme, token->lineNo+1,reverse_lookup_non_terminal(X)); 
                }else{
                printf("ERROR_5: The token <%s> for lexeme <%s>  does not match at line <%d>. The expected token here is of type <%s>.\n", reverse_lookup_non_terminal(a), token->lexeme, token->lineNo+1,reverse_lookup_non_terminal(X));
                }
               
            }
            //Error recovery in panic mode
                     while(containsEpsilonRHS(X)){
                     if(stack->size>2){
                            removed=pop(stack);
                            X=lookup_symbol(top(stack)->nodeSymbol);
                            }else{
                            token=getNextToken(F);
                            a=lookup_symbol(token->token);
                            if(a==lookup_symbol("EOF")) break;
                            }
                           
                    }
                    while(1){

                        if((!checkFollow(X,a)) && X<NO_OF_NTS){
                            token=getNextToken(F);
                            a=lookup_symbol(token->token);
                            if(a==lookup_symbol("EOF")) break;
                        }else{
                            if(stack->size>2){
                            removed=pop(stack);
                            X=lookup_symbol(top(stack)->nodeSymbol);
                            }else{
                                token=getNextToken(F);
                                a=lookup_symbol(token->token);
                            if(a==lookup_symbol("EOF")) break;
                            }
                            break;
                        }
                    }
                continue;
        }else if(ParseTable[X][a-NO_OF_NTS]!=-1){ //M[X,a]=X->Y1Y2.....Yk
       
        int i=ParseTable[X][a-NO_OF_NTS];
        
        treeNode* tempRHS[10];
        int tempRHSIndex=0;
        treeNode *LHShead;
         
        removed=pop(stack); //pop the stack


        ruleNode *temp=Rule->ruleArray[i].rHead;
        
        
        if(temp->isTerminal==0){
            LHShead=createTreeNode("----",-1,"","",removed->nodeSymbol,temp->isTerminal,reverse_lookup_non_terminal(temp->value),NULL,NULL);
        }else{
            LHShead=createTreeNode(token->lexeme,token->lineNo+1,token->token,"",removed->nodeSymbol,temp->isTerminal,reverse_lookup_non_terminal(temp->value),NULL,NULL); 
            if(lookup_symbol(token->token)==lookup_symbol("TK_NUM") || lookup_symbol(token->token)==lookup_symbol("TK_RNUM")){
            LHShead->valueIfNumber=token->lexeme;        
            }               
        }
        removed->child=LHShead;
                  
        tempRHS[tempRHSIndex]=LHShead;
        tempRHSIndex++;        
        temp=temp->next;
        treeNode *prev=LHShead;
        treeNode *curr;
        while(temp!=NULL){
            if(temp->isTerminal==0){
            curr=createTreeNode("----",-1,"","",removed->nodeSymbol,temp->isTerminal,reverse_lookup_non_terminal(temp->value),NULL,NULL);
        }else{
            curr=createTreeNode(token->lexeme,token->lineNo+1,token->token,"",removed->nodeSymbol,temp->isTerminal,reverse_lookup_non_terminal(temp->value),NULL,NULL); 
            if(lookup_symbol(token->token)==lookup_symbol("TK_NUM") || lookup_symbol(token->token)==lookup_symbol("TK_RNUM")){
            curr->valueIfNumber=token->lexeme;        
            }               
        }
            tempRHS[tempRHSIndex]=curr;
            prev->next=curr;
            prev=curr;       
            tempRHSIndex++;
            temp=temp->next;
        }      
            
     
        int j;
        for(j=tempRHSIndex-1;j>=0;j--){ //push Y1,Y2,.....,Yk onto the stack with Y1 on top
            push(stack,tempRHS[j]);
            }
        }
        
         X=lookup_symbol(top(stack)->nodeSymbol);  
         
         }
  
      
       if(lookup_symbol(top(stack)->nodeSymbol)==lookup_symbol("$")){
            if(!errorFlag){
                       if(!messageFlag)
                            //printf("\nCompiled Successfully: Input source code is syntactically correct!!\n");
                        messageFlag++;
                        }
                   
                    }    
    if(!errorFlag){  
    	syntax_error=0;             
        return Ptree; 
        }
    else {
    	syntax_error=1;
        return NULL;
        }
}

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

/* 
function provides an interface for observing the correctness of the creation of parse tree. The function prints the parse tree in depth first order in the file outfile. The output is such that each line of the file outfile must contain the information corresponding to the currently  visited node of the parse tree in the following format 
         lexemeCurrentNode     lineno   token   valueIfNumber   parentNodeSymbol   isLeafNode(yes/no)    NodeSymbol
*/

void printtree(treeNode* root)
{
    if(root==NULL){ return; } 
   
   if(lookup_symbol(root->nodeSymbol)==lookup_symbol("eps")){
        printf("%-20s%-20s%-20s%-20s","----", " - "," - " ," - ");
        printf("%-20s%-20s%-20s\n",root->parentNodeSymbol," - ",root->nodeSymbol);
        
    }
    else{
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
    printf("%-20s",root->parentNodeSymbol);
   
    if(root->isLeafNode==1){
        printf("%-20s","yes ");
        printf("%-20s\n"," - ");
        
    }else{
        printf("%-20s","no ");
        printf("%-20s\n",root->nodeSymbol);
        
    }
    }
    
    printtree(root->child);
    printtree(root->next);
    
    return;
}

void printParseTree(parseTree  *PT)
{
   printf("\nParse Tree is:\n");
   printf("%-20s%-20s%-20s%-20s%-20s%-20s%-20s\n","lexemeCurrentNode","lineno","token","valueIfNumber","parentNodeSymbol","isLeafNode(yes/no)","NodeSymbol");
   treeNode* root1=PT->root;
   printtree(root1);  
}

void parser_main(){
    FILE *grammar = fopen("grammar.txt","r");
	syntax_error=0;
    Rule=(rule *)malloc(sizeof(rule));
    //Initialize Grammar Rules
    int i=0;
    for(i=0;i<NO_OF_RULES;i++){
        Rule->ruleArray[i].ruleNo=i+1;
        Rule->ruleArray[i].NTvalue=-1;
        Rule->ruleArray[i].rHead=NULL;
        }
        
    loadGrammar(grammar);
    
    //initialize first set 
   firstSet=(set *)malloc(sizeof(set));
   for(i=0;i<NO_OF_SYMBOLS;i++){
        firstSet->setArray[i].Svalue=-1;
        firstSet->setArray[i].rHead=NULL;
        }
        
   //assign first set of terminals
   for(i=NO_OF_NTS;i<NO_OF_SYMBOLS;i++){
        firstSet->setArray[i].Svalue=i;
        firstSet->setArray[i].rHead=(ruleNode*) malloc(sizeof(ruleNode));
        firstSet->setArray[i].rHead->value=i;
        firstSet->setArray[i].rHead->isTerminal=1;
        firstSet->setArray[i].rHead->next=NULL;
        }
        
   //create firstset of non terminals     
   for(i=0;i<NO_OF_NTS;i++){
        if( firstSet->setArray[i].rHead==NULL){
            //printf("%d\n",i);
            firstSet->setArray[i].Svalue=i;
            createFirstSet(i);        
        }
     } 
     
   //Initialize follow sets
    followSet=(set *)malloc(sizeof(set));
    for(i=0;i<NO_OF_NTS;i++){
        visited[i]=0;
        if(i==0){
            followSet->setArray[i].Svalue=i;
            followSet->setArray[i].rHead=(ruleNode*) malloc(sizeof(ruleNode));
            followSet->setArray[i].rHead->value=lookup_symbol("$");
            followSet->setArray[i].rHead->isTerminal=1;
            followSet->setArray[i].rHead->next=NULL;
            visited[i]=1;
        }else{        
            followSet->setArray[i].Svalue=-1;
            followSet->setArray[i].rHead=NULL;
            }
        }
        
   //Create follow sets    
   for(i=0;i<NO_OF_NTS;i++){
        //printf("%d\n",visited[i]);
        if( !visited[i]){
            //printf("%d\n",i);
            followSet->setArray[i].Svalue=i;
            createFollowSet(i);        
        }
        }

    int j=0;
    //Initialize parse table
    for(i=0;i<NO_OF_NTS;i++){
		for(j=0;j<NO_OF_TS;j++){
			//printf("%d %d", i, j);	
			ParseTable[i][j] = -1;
		}
	}
	
	createParseTable();
	
	
	
 
    return;
}
