#include<iostream>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h>
using namespace std;

char curtok[255];
FILE* vmf;
FILE* jackf;
DIR* dir;
struct dirent *ent;
string fname="";

bool hasMoreTokens(){
	return !feof(jackf)?true:false;
}
void advance(){
	fgets(curtok,255,jackf);
}

string tokenType(char ar[] , int ptr){

	if(ar[ptr] >= '0' && ar[ptr] <= '9')
		return "INT_CONST";
	
	else if((ar[ptr] >= 'a' && ar[ptr] <= 'z') || (ar[ptr] >= 'A' && ar[ptr] <= 'Z') || ar[ptr] == '_'){
		string s = "";
		while((ar[ptr] >= '0' && ar[ptr] <= '9') || (ar[ptr] >= 'a' && ar[ptr] <= 'z') || (ar[ptr] >= 'A' && ar[ptr] <= 'Z') || ar[ptr] == '_'){
			s += ar[ptr];
			ptr = ptr+1;
		}
		string kwar[] = {"class" , "constructor" , "function"  , "method" , "field" , "static" , "var" , "int" , "char" , "boolean" , "void" , "true" , "let" , "this" , "null" , "false" , "while" , "else" , "do" , "if" , "return"};
		int i;
		int n =  sizeof(kwar)/sizeof(kwar[0]);
		for(i = 0; i<n;i++){
			if(s == kwar[i])
				return "KEYWORD";
		}
		return "IDENTIFIER";
	}

	else if(ar[ptr] == '\"')
		return "STRING_CONST";

	else
		return "SYMBOL";

}

string keyword(char ar[] , int* ptr){
	string s = "";
	while((ar[*ptr] >= 'a' && ar[*ptr] <= 'z')){
		s += ar[*ptr] - 32;
		*ptr = *ptr+1;
	}
	string kwar[] = {"CLASS" , "CONSTRUCTOR" , "FUNCTION"  , "METHOD" , "FIELD" , "STATIC" , "VAR" , "INT" , "CHAR" , "BOOLEAN" , "VOID" , "TRUE" , "LET" , "THIS" , "NULL" , "FALSE" , "WHILE" , "ELSE" , "DO" , "IF" , "RETURN"};
	int i;
	int n =  sizeof(kwar)/sizeof(kwar[0]);
	for(i = 0; i<n;i++){
		if(s == kwar[i])
			return s;
	}
	s = "";
	return s;
}

string identifier(char ar[] , int* ptr){
	string s = "";
	while((ar[*ptr] >= '0' && ar[*ptr] <= '9') || (ar[*ptr] >= 'a' && ar[*ptr] <= 'z') || (ar[*ptr] >= 'A' && ar[*ptr] <= 'Z') || ar[*ptr] == '_'){
		s += ar[*ptr];
		*ptr = *ptr+1;
	}
	return s;
}

char symbol(char ar[] , int* ptr){
	char symbols[] = {'{' , '}' , '(' , ')' , '[' , ']' , ';' , '.' , ',' , '-' , '+' , '=' , '/' , '*' , '&' , '|' , '~' , '<' , '>'};
	int i;
	for(i = 0; i<19;i++){
		if(ar[*ptr] == symbols[i]){
			*ptr = *ptr+1;
			return symbols[i];
		}
	}
	*ptr = *ptr+1;
	return '\0';
}

int intconstant(char ar[] , int* ptr){
	int s = 0;
	while((ar[*ptr] >= '0' && ar[*ptr] <= '9')) {
		s = s*10 + ar[*ptr] - '0'; 
		*ptr = *ptr+1;
	}
	if(s >= 0 && s <= 327637)
		return s;
	return -1;
}
string stringconstant(char ar[] , int* ptr){
	string s = "";
	*ptr = *ptr + 1;
	while(ar[*ptr] != '\"' && ar[*ptr] != '\n' && ar[*ptr] != '\0' ) {
		s += ar[*ptr];
		*ptr = *ptr+1;
	}
	*ptr = *ptr + 1;
	return s;
}

void whitespace(char ar[] , int* ptr){
	while(ar[*ptr]==' ' || ar[*ptr]=='\t' || ar[*ptr]=='\r' || ar[*ptr]=='\v'){
		*ptr = *ptr+1;
	}
}

void comments(char ar[] , int* ptr){
	if(ar[*ptr]=='/') {
		if(ar[*ptr+1] != '\n' && ar[*ptr+1] == '/'){
			while(ar[*ptr]!='\n')
				*ptr = *ptr+1;
		}
		else if(ar[*ptr+1] != '\n' && ar[*ptr+1] == '*'){
			while(ar[*ptr]!='*' || ar[*ptr+1]!='/')
				*ptr = *ptr+1;
			*ptr = *ptr+2;
		}
		else{
			return;
		}
	}
}