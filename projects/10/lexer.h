#include<iostream>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h>
using namespace std;

char curline[255];
FILE* vmf;
FILE* jackf;
DIR* dir;
struct dirent *ent;
string fname="";
string curtok = "";
int lookahead = 0;
int lineno = 0;


void whitespace(char ar[] ){
	while(ar[lookahead]==' ' || ar[lookahead]=='\t' || ar[lookahead]=='\r' || ar[lookahead]=='\v'){
		lookahead = lookahead+1;
	}
}

void comments(char ar[] ){
	if(ar[lookahead]=='/') {
		if(ar[lookahead+1] == '/'){
			while(ar[lookahead]!='\n')
				lookahead = lookahead+1;
		}
		else if(ar[lookahead+1] == '*'){
			while(ar[lookahead] != '*' || ar[lookahead+1]!='/'){
				lookahead = lookahead+1;
			}
			lookahead = lookahead+2;
		}
	}
}
bool hasMoreTokens(){
	return !feof(jackf)?true:false;
}

string tokenType(){
	int i = 0;

	if(curtok.at(i) >= '0' && curtok.at(i) <= '9')
		return "INT_CONST";

	else if((curtok.at(i) >= 'a' && curtok.at(i) <= 'z') || (curtok.at(i) >= 'A' && curtok.at(i) <= 'Z') || curtok.at(i) == '_'){
		string s = "";
		while((curtok.at(i) >= '0' && curtok.at(i) <= '9') || (curtok.at(i) >= 'a' && curtok.at(i) <= 'z') || (curtok.at(i) >= 'A' && curtok.at(i) <= 'Z') || curtok.at(i) == '_'){
			s += curtok.at(i);
			i++;
			if(i >= curtok.length())
				break;
		}
		if(i != curtok.length())
			return "BAD IDENTIFIER or class";

		string kwar[] = {"class" , "constructor" , "function"  , "method" , "field" , "static" , "var" , "int" , "char" , "boolean" , "void" , "true" , "let" , "this" , "null" , "false" , "while" , "else" , "do" , "if" , "return"};
		int n =  sizeof(kwar)/sizeof(kwar[0]);
		for(i = 0; i < n;i++){
			if(s == kwar[i])
				return "KEYWORD";
		}
		return "IDENTIFIER";
	}

	else if(curtok.at(i) == '\"')
		return "STRING_CONST";

	else{
		char symbols[] = {'{' , '}' , '(' , ')' , '[' , ']' , ';' , '.' , ',' , '-' , '+' , '=' , '/' , '*' , '&' , '|' , '~' , '<' , '>'};
		for(i = 0; i<19;i++){
			if(curtok.at(0) == symbols[i]){
				return "SYMBOL";
			}
		}
	}
	return "bad string";
}

void advance(){
	while(curline[lookahead] == '\n' || curline[lookahead] == '\0' || curline[lookahead] == '\r'){
		fgets(curline,255,jackf);
		lookahead = 0;
		if(!hasMoreTokens())
			return;

		whitespace(curline);
		comments(curline);

		lineno++;
	}

	curtok = "";
	whitespace(curline);
	comments(curline);

	while(curline[lookahead] != '\n' && curline[lookahead] != ' ' && curline[lookahead] != '\r' && curline[lookahead] != '\v' && curline[lookahead] != '\t'){
		curtok += curline[lookahead];
		lookahead++;
	}
}

string keyword(){
	string s = "";
	int i = 0;
	while((curtok.at(i) >= 'a' && curtok.at(i) <= 'z')){
		s += curtok.at(i) - 32;
		i++;
		if(i >= curtok.length())
			break;
	}
	string kwar[] = {"CLASS" , "CONSTRUCTOR" , "FUNCTION"  , "METHOD" , "FIELD" , "STATIC" , "VAR" , "INT" , "CHAR" , "BOOLEAN" , "VOID" , "TRUE" , "LET" , "THIS" , "NULL" , "FALSE" , "WHILE" , "ELSE" , "DO" , "IF" , "RETURN"};
	int n =  sizeof(kwar)/sizeof(kwar[0]);
	for(i = 0; i<n;i++){
		if(s == kwar[i])
			return s;
	}
	s = "";
	return s;
}

string identifier(){
	string s = "";
	int i = 0;
	if(curtok.at(i) >= '0' && curtok.at(i) <= '9' ){
		printf("ERROR invalid identifier name");
		return s;
	}
	while((curtok.at(i) >= '0' && curtok.at(i) <= '9') || (curtok.at(i) >= 'a' && curtok.at(i) <= 'z') || (curtok.at(i) >= 'A' && curtok.at(i) <= 'Z') || curtok.at(i) == '_'){
		s += curtok.at(i);
		i++;
		if(i >= curtok.length())
			break;
	}
	return s;
}

char symbol(){
	char symbols[] = {'{' , '}' , '(' , ')' , '[' , ']' , ';' , '.' , ',' , '-' , '+' , '=' , '/' , '*' , '&' , '|' , '~' , '<' , '>'};
	int i;
	for(i = 0; i<19;i++){
		if(curtok.at(0) == symbols[i]){
			i++;
			return symbols[i];
		}
	}
	i++;
	return '\0';
}

int intconstant(){
	int s = 0;
	int i = 0;
	while((curtok.at(i) >= '0' && curtok.at(i) <= '9')) {
		s = s*10 + curtok.at(i) - '0'; 
		i++;
		if(i >= curtok.length())
			break;
	}
	if(s >= 0 && s <= 327637)
		return s;
	return -1;
}
string stringconstant(){
	string s = "";
	int i = 1;
	while(curtok.at(i) != '\"' && curtok.at(i) != '\n' && curtok.at(i) != '\0' ) {
		s += curtok.at(i);
		i++;
		if(i >= curtok.length())
			break;
	}
	return s;
}
