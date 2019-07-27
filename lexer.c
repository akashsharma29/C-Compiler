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
#include "lexerDef.h"

//Gets file pointer and fills the buffer for token generation
FILE *getStream(FILE *fp, int buffersize){
/* int i=0;
	
  int k=buffersize;
  bufferCnt=0;
    char c;
	while(i<k){ //read characters from file into buffer with limit of BUFFER_SIZE
    bufferCnt++; //Buffer Counter
		c=getc(fp);
		if(c==EOF){
			Buffer[i]='\0'; //End of line symbol to mark end of code
      Buffer[i+1]='$';
			return fp;
		}
		else{
			Buffer[i]=c;
			i++;
		}
	} */
	bufferCnt=(int)fread(Buffer,1,buffersize,fp);
	//printf("size----> %d\n",i);
	if(bufferCnt<buffersize){
		Buffer[bufferCnt]='\0';
	} 
	return fp;
}


//Function for generating token
tokenInfo *createToken(char *token,char *lexeme,int lineNo,int colNo){
  tokenInfo *t=(tokenInfo *)malloc(sizeof(tokenInfo)); //Instantiate a token
  t->token=token; //Token name
  t->lexeme=lexeme; //Lexeme name
  t->lineNo=lineNo; //Line Number of code token is present at
  t->colNo=colNo-(int)strlen(lexeme); //Optional column Number of code token is present at

  return t; //return the token created
}

//Dynamic array to keep track of lexeme generated
char *appendChartoString(char *s1, char c){ 
  int len=strlen(s1); //Lexeme at previous state
  char *s2=(char *)malloc((len+1)*sizeof(char)); //increase memory space by one 
  strcpy(s2,s1); //new character array with incremented lexeme character
  s2[len]=c; //new character to be added to lexeme
  
  return s2; //return new lexeme string
}

//Function to read the buffer and return the token generated
tokenInfo *getNextToken(FILE *fp){
  char lookahead; //input lookahead symbol
  int state=0; //starting state
  char* lexeme=""; //initialize lexeme as empty
  tokenInfo *token; //token generated and to be returned
  int isLexicalError = 0; //set if there is a lexical error

  while(1){ //loop to iterate through states
    if(bufferPointer==0){ //refill the buffer when empty
      fp = getStream(F,BUFFER_SIZE);
      F=fp;
    }
    lookahead=Buffer[bufferPointer]; //lookahead read from  buffer
    if(lookahead=='\0') { //end of code reached
        token=createToken("EOF","eof",lineNo,colNo);
        return token;  //retrun EOF(to be ignored) to stop the compiler
        break;
    }
    
    switch(state){ //switch to particular state

    case 0:{ //initial state of DFA

        //lookahead for spaces and tabs
        if(lookahead==' ' || lookahead=='\t'|| lookahead=='\r'){
          state=0;
          colNo++;
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
        }

        //lookahead for new line
        else if(lookahead=='\n'){ 
          state=0;
          lineNo++;
          colNo=0;
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
        }
        
        //lookahead for comments
        else if(lookahead=='%'){ 
          state=40;
          colNo++;
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;    
        }  
        
        //lookahead for Assignment operator or Relational operator less than or equal to
        else if(lookahead=='<'){
          state=1;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;      
        } 
        
        //lookahead for Field name
        else if(lookahead=='a' || (lookahead>='e' && lookahead<='z')){
          state=4; 
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
        }
        
        //lookahead for Field Name or Identifier 
        else if(lookahead>='b' && lookahead<='d'){
          state=5; 
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
        }
      
        //lookahead for number 
        else if(lookahead-'0'>=0 && lookahead-'0'<=9){
          state=8; 
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
        }
        
        //lookahead for record
        else if(lookahead=='_'){
          state=12; 
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
        }
        
        //lookahead for recordid
        else if(lookahead=='#'){
          state=15; 
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
        }

       //lookahead for Left square bracket
       else if(lookahead=='['){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
          token=createToken("TK_SQL",lexeme,lineNo,colNo);
          return token;
        }

        //lookahead for Right square bracket
       else if(lookahead==']'){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          token=createToken("TK_SQR",lexeme,lineNo,colNo);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE; 
          return token; 
          //bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
        }

       //lookahead for semicolon
       else if(lookahead==';'){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE; 
          
          //final for semicolon   
          token=createToken("TK_SEM",lexeme,lineNo,colNo);
          return token; 
        }

       //lookahead for colon
       else if(lookahead==':'){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
          //final for colon    
          token=createToken("TK_COLON",lexeme,lineNo,colNo);
          return token;
        }

       //lookahead for dot
       else if(lookahead=='.'){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE; 
                //final for dot    
          token=createToken("TK_DOT",lexeme,lineNo,colNo);
          return token; 
        }

       //lookahead for Open parenthesis
       else if(lookahead=='('){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE; 
          token=createToken("TK_OP",lexeme,lineNo,colNo);
          return token; 
        }

      //lookahead for Closed parenthesis
       else if(lookahead==')'){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
         
          //final for Closed parenthesis    
          token=createToken("TK_CL",lexeme,lineNo,colNo);
          return token;  
          
        }

      //lookahead for addition
       else if(lookahead=='+'){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE; 
          //final for ADDITION   
          token=createToken("TK_PLUS",lexeme,lineNo,colNo);
          return token; 
        }

      //lookahead for subtraction
       else if(lookahead=='-'){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
          //final for SUBTRACTION 
          token=createToken("TK_MINUS",lexeme,lineNo,colNo);
          return token;
        }

      //lookahead for multiplication
       else if(lookahead=='*'){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
          //final for MULTIPLICATION 
      token=createToken("TK_MUL",lexeme,lineNo,colNo);
      return token;  
        }

      //lookahead for division
       else if(lookahead=='/'){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE; 
          //final for DVISION 
      token=createToken("TK_DIV",lexeme,lineNo,colNo);
      return token; 
        }

      //lookahead for and
      else if(lookahead=='&'){
          state=27; 
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
        }

      //lookahead for or
      else if(lookahead=='@'){
          state=30; 
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
        }

      //lookahead for not
      else if(lookahead=='~'){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
          //final for NOT 
      token=createToken("TK_NOT",lexeme,lineNo,colNo);
      return token; 
        }

      //lookahead for gt/ge
      else if(lookahead=='>'){
          state=34; 
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
        }

      //lookahead for not equal to
      else if(lookahead=='!'){
          state=36; 
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
        }

      //lookahead for comma
      else if(lookahead==','){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
          //final for ,
          token=createToken("TK_COMMA",lexeme,lineNo,colNo);
          return token;
        }
        
      //lookahead for == 
      else if(lookahead=='='){
          state=39; 
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
        }

      //No valid lookahead   
      else{
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
          token=createToken("UN_SYM",lexeme,lineNo,colNo); //Unidentifed Symbol error
          return token;   
          break;  
      }



        break;
      }

      case 1:{

        if(lookahead=='-'){ //for <---
          state=2;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
        }
        
        else if(lookahead=='='){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
          //final for <=
          token=createToken("TK_LE",lexeme,lineNo,colNo);
          return token;
        }else{
          //final for <
          token=createToken("TK_LT",lexeme,lineNo,colNo);
          return token;
        }

        break;
      }

      case 2:{

        if(lookahead=='-'){ //for <---
          state=3;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
        }else{ //Error in assignment operator
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          token=createToken("UN_PATT",lexeme,lineNo,colNo); //Unidentified Pattern Error
          return token;   
        } 

        break;
      }

      case 3:{

        //lookahead for spaces and tabs
        if(lookahead=='-'){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
          //final for <---
          token=createToken("TK_ASSIGNOP",lexeme,lineNo,colNo);
          return token;
        }else{ //Error in assignment operator
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          token=createToken("UN_PATT",lexeme,lineNo,colNo);
          return token;   
        } 

        break;
      }
      
      case 4:{
      // for a-z
      if(lookahead>='a' && lookahead<='z')
      {
          state=4;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
      }

      else{
          if(bufferPointer==0){
            fseek(F,-bufferCnt,SEEK_CUR);         
          } 

          //check for keyword
          int flag=0;
          lookupNode *temp=lookUp->table[lexeme[0]-'a'].head;
          while(temp!=NULL){
            if(strcmp(temp->lexeme,lexeme)==0){  
              flag=1;
              break;              
            }
            temp=temp->next;
          }
          
          //final for keyword
          if(flag==1){
            token=createToken(temp->token,lexeme,lineNo,colNo);
            return token;
          }
          //final for Field name          
          token=createToken("TK_FIELDID",lexeme,lineNo,colNo);
          return token;
      }

        break;
      }
 
     
    case 5:{
        
        if(lookahead>='a' && lookahead<='z'){ //for field name
          state=4;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
       }else if(lookahead-'0'>=2 && lookahead-'0'<=7){  //for identifiers
          colNo++;
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
          lexeme=appendChartoString(lexeme,lookahead);
          state=6;    
        }else{
          if(bufferPointer==0){
            fseek(F,-bufferCnt,SEEK_CUR);         
          } 

          //check for keyword
          int flag=0;
          lookupNode *temp=lookUp->table[lexeme[0]-'a'].head;
          while(temp!=NULL){
            if(strcmp(temp->lexeme,lexeme)==0){  
              flag=1;
              break;              
            }
            temp=temp->next;
          }
          
          //final for keyword
          if(flag==1){
            token=createToken(temp->token,lexeme,lineNo,colNo);
            return token;
          }
          //final for Field name          
          token=createToken("TK_FIELDID",lexeme,lineNo,colNo);
          return token;
      }
        
        break;
      }

    case 6:{
        
        if(lookahead>='b' && lookahead<='d'){ //for identifiers
          state=6;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
       }else if(lookahead-'0'>=2 && lookahead-'0'<=7){  //for identifiers
          state=7;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;   
        }
        else{ 
          if(bufferPointer==0){
            fseek(F,-bufferCnt,SEEK_CUR);         
          } 

          //check for length error(>20)
          if((int)strlen(lexeme)<2  || (int)strlen(lexeme)>20){
              token=createToken("LEN_ERROR",lexeme,lineNo,colNo);
              return token; 
          
          }

          //final for Identifier         
          token=createToken("TK_ID",lexeme,lineNo,colNo);
          return token;  
        } 

        break;
      }

    case 7:{
        
       if(lookahead-'0'>=2 && lookahead-'0'<=7){  //for idnetifiers
          state=7;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;      
        }
        else{ 
          if(bufferPointer==0){     //re reads the buffer to avoid double clearing when bufferPoiner is 0
            fseek(F,-bufferCnt,SEEK_CUR);         
          } 
          
          //check for length error(>20)
          if((int)strlen(lexeme)<2  || (int)strlen(lexeme)>20){
              token=createToken("LEN_ERROR",lexeme,lineNo,colNo);
              return token; 
          
          }

          //final for Identifier         
          token=createToken("TK_ID",lexeme,lineNo,colNo);
          return token;  
        } 

        break;
      }
      
       case 8:{
        
       if(lookahead-'0'>=0 && lookahead-'0'<=9){  //for interger/real numbers
          colNo++;
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
          lexeme=appendChartoString(lexeme,lookahead);
          state=8;    
        }
        else if(lookahead=='.'){ //for real numbers
          colNo++;
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
          lexeme=appendChartoString(lexeme,lookahead);
          state=9;
        }
        else{ 
          if(bufferPointer==0){
            fseek(F,-bufferCnt,SEEK_CUR);         
          } 

          //final for interger         
          token=createToken("TK_NUM",lexeme,lineNo,colNo);
          return token;  
        } 

        break;
      }

      case 9:{
        
       if(lookahead-'0'>=0 && lookahead-'0'<=9){ //for real numbers
          colNo++;
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
          lexeme=appendChartoString(lexeme,lookahead);
          state=10;    
        }
        
        else{ //Error
          colNo++;
          token=createToken("UN_PATT",lexeme,lineNo,colNo);
          return token;  
        } 

        break;
      }

     case 10:{
        
       if(lookahead-'0'>=0 && lookahead-'0'<=9){  //for real numbers
          colNo++;
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;  
          lexeme=appendChartoString(lexeme,lookahead);
          state=11;    
        }
        
        else{ //Error
          colNo++;
          token=createToken("UN_PATT",lexeme,lineNo,colNo);
          return token;  
        } 

        break;
      }

    //final for RNUM
    case 11:{
    if(bufferPointer==0){
            fseek(F,-bufferCnt,SEEK_CUR);         
          } 

          //final for real numbers       
          token=createToken("TK_RNUM",lexeme,lineNo,colNo);
          return token; 

      break;
     } 

    case 12:{
        
       if((lookahead>='a' && lookahead<='z') || (lookahead>='A' && lookahead<='Z')) { //for function identifier
          state=13;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
       }
        else{ //Error
          colNo++;
          token=createToken("UN_PATT",lexeme,lineNo,colNo);
          return token;  
        } 
      break;
    }

   case 13:{        
       if((lookahead>='a' && lookahead<='z') || (lookahead>='A' && lookahead<='Z')) { //for function identifier
          state=13;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
       }else if(lookahead-'0'>=0 && lookahead-'0'<=9) {  //for function identifier
          state=14;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
       }
        else{ 
          if(bufferPointer==0){
            fseek(F,-bufferCnt,SEEK_CUR);         
          } 
          
          char *mainKey="_main";
          //check for main
          if(strcmp(mainKey,lexeme)==0){  
            token=createToken("TK_MAIN","_main",lineNo,colNo);
            return token; //return _main
          }
           
          if((int)strlen(lexeme)>30){   //check for error in length(>30)
              token=createToken("LEN1_ERROR",lexeme,lineNo,colNo);
              return token; 
          
          }

          //final for FUNID         
          token=createToken("TK_FUNID",lexeme,lineNo,colNo);
          return token;  //return function identifier
        } 
        break;
    }

    case 14:{        //for function identifier
       if(lookahead-'0'>=0 && lookahead-'0'<=9) {
          state=14;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
       }
        else{ 
          if(bufferPointer==0){
            fseek(F,-bufferCnt,SEEK_CUR);         
          } 
          
          if((int)strlen(lexeme)>30){   //check for error in length(>30)
              token=createToken("LEN1_ERROR",lexeme,lineNo,colNo);
              return token; 
          
          }
          
          //final for FUNID         
          token=createToken("TK_FUNID",lexeme,lineNo,colNo);
          return token;   //return function identifier
        } 
      break;
    }

    case 15:{        
       if(lookahead>='a' && lookahead<='z'){ //for recordid
          state=15;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
       }else{ 
          if(bufferPointer==0){
            fseek(F,-bufferCnt,SEEK_CUR);         
          } 
         
          //final for RECORDID
          token=createToken("TK_RECORDID",lexeme,lineNo,colNo);
          return token;   
        } 
      break;
    }

    //and state1
    case 27:{
        
       if(lookahead=='&') {
          state=28;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
       }
        else{ //Error
          colNo++;
          token=createToken("UN_PATT",lexeme,lineNo,colNo);
          return token;  
        } 
      break;
    }
    
    //and state2
    case 28:{
       if(lookahead=='&') {
          //state=29;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
          //final for and 
          token=createToken("TK_AND",lexeme,lineNo,colNo);
          return token;
       }
        else{ //Error
          colNo++;
          token=createToken("UN_PATT",lexeme,lineNo,colNo);
          return token;  
        } 
      break;
    }
    
    //and state3
    case 29:{
      if(bufferPointer==0){
            fseek(F,-bufferCnt,SEEK_CUR);         
          } 
          
      //final for and 
      token=createToken("TK_AND",lexeme,lineNo,colNo);
      return token;  

      break;
    }
    
    //or state1
    case 30:{
        
       if(lookahead=='@') {
          state=31;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
       }
        else{ //Error
          colNo++;
          token=createToken("UN_SYM",lexeme,lineNo,colNo);
          return token;  
        } 
      break;
    }

    //or state2
    case 31:{
       if(lookahead=='@') {
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
          //final for OR 
          token=createToken("TK_OR",lexeme,lineNo,colNo);
          return token;
       }
        else{ //Error
          colNo++;
          token=createToken("UN_PATT",lexeme,lineNo,colNo);
          return token;  
        } 
      break;
    }
   
    case 34:{
       if(lookahead=='='){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
          //final for >=
          token=createToken("TK_GE",lexeme,lineNo,colNo);
          return token;
        }else{
          if(bufferPointer==0){
            fseek(F,-bufferCnt,SEEK_CUR);         
          }             
          //final for >
          token=createToken("TK_GT",lexeme,lineNo,colNo);
          return token;
        }
      break;
    }
    
    
    case 36:{
       if(lookahead=='='){
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
          //final for !=
          token=createToken("TK_NE",lexeme,lineNo,colNo);
          return token;  
        }else{ //Error
          colNo++;
          token=createToken("UN_SYM",lexeme,lineNo,colNo);
          return token;  
        } 
      break;
    }
    
    //for ==
    case 39:{
       if(lookahead=='='){
          //state=37;
          colNo++;
          lexeme=appendChartoString(lexeme,lookahead);
          bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
          //final for !=
          token=createToken("TK_EQ",lexeme,lineNo,colNo);
          return token;  
        }else{ //Error
          colNo++;
          token=createToken("UN_SYM",lexeme,lineNo,colNo);
          return token;  
        } 
      break;
    }
    
    //for comments
    case 40:
    {
       
       if(lookahead!='\n' && lookahead!='\0' && lookahead!='\r'){ //ignore comment till end of line        
            state=40;
            colNo++;
            bufferPointer=(bufferPointer+1)%BUFFER_SIZE;
            
            }else{
             if(bufferPointer==0){     //re reads the buffer to avoid double clearing when bufferPoiner is 0
            fseek(F,-bufferCnt,SEEK_CUR);         
          } 
                state=0;
            }
      break;
    }
    
    
    default:{ //error if nothing matches the next state
          colNo++;
          token=createToken("UN_PATT",lexeme,lineNo,colNo);
          return token;   
          break;  
    }
  }
}

  return token; //retruns the token generated
}

//HashTable used as lookup for Keywords
lookupTable *createLookUpTable(){
  lookupTable *lookUp;
  lookUp = (lookupTable *) malloc(sizeof(lookupTable));
  int i=0;
  for(i=0;i<26;i++){
      lookUp->table[i].head=NULL;
      lookUp->table[i].count=0;
  }
  
  //for c
  lookupNode *cElems;
  cElems=(lookupNode *)malloc(sizeof(lookupNode));
  cElems->lexeme="call";  
  cElems->token="TK_CALL";
  cElems->next=NULL;
  lookUp->table[(int)('c'-'a')].head= cElems;

  //for e
  lookupNode *eElems;
  eElems=(lookupNode *)malloc(sizeof(lookupNode));
  eElems->lexeme="end";  
  eElems->token="TK_END";
  eElems->next=(lookupNode *)malloc(sizeof(lookupNode));
  eElems->next->lexeme="endwhile";  
  eElems->next->token="TK_ENDWHILE";
  eElems->next->next=(lookupNode *)malloc(sizeof(lookupNode));
  eElems->next->next->lexeme="endif";  
  eElems->next->next->token="TK_ENDIF";
  eElems->next->next->next=(lookupNode *)malloc(sizeof(lookupNode));
  eElems->next->next->next->lexeme="else";  
  eElems->next->next->next->token="TK_ELSE";
  eElems->next->next->next->next=(lookupNode *)malloc(sizeof(lookupNode));
  eElems->next->next->next->next->lexeme="endrecord";  
  eElems->next->next->next->next->token="TK_ENDRECORD";
  eElems->next->next->next->next->next=NULL;
  lookUp->table[(int)('e'-'a')].head= eElems;

  //for g
  lookupNode *gElems;
  gElems=(lookupNode *)malloc(sizeof(lookupNode));
  gElems->lexeme="global";  
  gElems->token="TK_GLOBAL";
  gElems->next=NULL;
  lookUp->table[(int)('g'-'a')].head= gElems;

  //for i
  lookupNode *iElems;
  iElems=(lookupNode *)malloc(sizeof(lookupNode));
  iElems->lexeme="int";  
  iElems->token="TK_INT";
  iElems->next=(lookupNode *)malloc(sizeof(lookupNode));
  iElems->next->lexeme="input";  
  iElems->next->token="TK_INPUT";
  iElems->next->next=(lookupNode *)malloc(sizeof(lookupNode));
  iElems->next->next->lexeme="if";  
  iElems->next->next->token="TK_IF";
  iElems->next->next->next=NULL;
  lookUp->table[(int)('i'-'a')].head= iElems;

  //for l
  lookupNode *lElems;
  lElems=(lookupNode *)malloc(sizeof(lookupNode));
  lElems->lexeme="list";  
  lElems->token="TK_LIST";
  lElems->next=NULL;
  lookUp->table[(int)('l'-'a')].head= lElems;

  //for o
  lookupNode *oElems;
  oElems=(lookupNode *)malloc(sizeof(lookupNode));
  oElems->lexeme="output";  
  oElems->token="TK_OUTPUT";
  oElems->next=NULL;
  lookUp->table[(int)('o'-'a')].head= oElems;

  //for p
  lookupNode *pElems;
  pElems=(lookupNode *)malloc(sizeof(lookupNode));
  pElems->lexeme="parameters";  
  pElems->token="TK_PARAMETERS";
  pElems->next=(lookupNode *)malloc(sizeof(lookupNode));
  pElems->next->lexeme="parameter";  
  pElems->next->token="TK_PARAMETER";
  pElems->next->next=NULL;
  lookUp->table[(int)('p'-'a')].head= pElems;
 
  //for r
  lookupNode *rElems;
  rElems=(lookupNode *)malloc(sizeof(lookupNode));
  rElems->lexeme="real";  
  rElems->token="TK_REAL";
  rElems->next=(lookupNode *)malloc(sizeof(lookupNode));
  rElems->next->lexeme="read";  
  rElems->next->token="TK_READ";
  rElems->next->next=(lookupNode *)malloc(sizeof(lookupNode));
  rElems->next->next->lexeme="record";  
  rElems->next->next->token="TK_RECORD";
  rElems->next->next->next=(lookupNode *)malloc(sizeof(lookupNode));
  rElems->next->next->next->lexeme="return";  
  rElems->next->next->next->token="TK_RETURN";
  rElems->next->next->next->next=(lookupNode *)malloc(sizeof(lookupNode));
  rElems->next->next->next->next->lexeme="endrecord";  
  rElems->next->next->next->next->token="TK_ENDRECORD";
  rElems->next->next->next->next->next=NULL;
  lookUp->table[(int)('r'-'a')].head= rElems;

  //for t
  lookupNode *tElems;
  tElems=(lookupNode *)malloc(sizeof(lookupNode));
  tElems->lexeme="type";  
  tElems->token="TK_TYPE";
  tElems->next=(lookupNode *)malloc(sizeof(lookupNode));
  tElems->next->lexeme="then";  
  tElems->next->token="TK_THEN";
  tElems->next->next=NULL;
  lookUp->table[(int)('t'-'a')].head= tElems;

  //for w
  lookupNode *wElems;
  wElems=(lookupNode *)malloc(sizeof(lookupNode));
  wElems->lexeme="with";  
  wElems->token="TK_WITH";
  wElems->next=(lookupNode *)malloc(sizeof(lookupNode));
  wElems->next->lexeme="while";  
  wElems->next->token="TK_WHILE";
  wElems->next->next=(lookupNode *)malloc(sizeof(lookupNode));
  wElems->next->next->lexeme="write";  
  wElems->next->next->token="TK_WRITE";
  wElems->next->next->next=NULL;
  lookUp->table[(int)('w'-'a')].head= wElems;

  return lookUp; 
}

//function to print free code
void printCommentFreeCode(char *testcaseFile){
    FILE *fp=fopen(testcaseFile ,"r");
    int i=0;
	
    char c;
	while(1){ //read characters from file into buffer with limit of BUFFER_SIZE
		c=getc(fp);
		if(c=='%'){
		    while(c!='\n' && c!='\0'){
             c=getc(fp);
          }

		}
		else if(c==EOF){
			break;
		}
		
		printf("%c",c);
		
	}
	
	return; 

}


void lexer_main(char *testcaseFile){
  F=fopen(testcaseFile ,"r+"); //opens th code file
  lookUp=createLookUpTable(); //initialize the lookup table for keywords
  return;
}


void printTokens(char *testcaseFile){
   lexer_main(testcaseFile);
   tokenInfo *token;
   printf("\nThe list of tokens is:\n");
  do{ 
     token=getNextToken(F);
     if(strcmp(token->token,"EOF")==0)break;
     else if(strcmp(token->token,"LEN_ERROR")==0){
                printf("ERROR 1: Identifier(%s) at line <%d> is longer than the prescribed length of 20 characters.\n",token->lexeme,token->lineNo+1);

                continue;
            }else  if( strcmp(token->token,"LEN1_ERROR")==0){
                printf("ERROR 1: Function identifier(%s) at line <%d> is longer than the prescribed length of 30 characters.\n",token->lexeme,token->lineNo+1);

                continue;
            }else if(strcmp(token->token,"UN_PATT")==0){
                printf("ERROR 3: Unknown pattern <%s> at line number <%d>\n",token->lexeme,token->lineNo+1);
                    continue;
            }else if(strcmp(token->token,"UN_SYM")==0){
                printf("ERROR_2: Unknown Symbol <%s> at line<%d>\n",token->lexeme,token->lineNo+1);
                continue;
            }
     printf("%s %s %d\n",token->token,token->lexeme,token->lineNo+1);
      }while(1);
    printf("\n");
  return;
}
