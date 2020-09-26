#include"lexer.h"
void compileTerm();
void compileSubroutine();
void compileExplist();
void compileExp();


char op(){
	char oper = symbol();
	char opsym[] = {'+','-','*','/','&','|','>','<','='};
	for(int i = 0 ; i < 9;i++){
		if(oper == opsym[i])
			return opsym[i];
	}
	return '\0';
}

char unaryop(){
	char unoper = symbol();
	char unopsym[] = {'~','-'};
	for(int i = 0 ; i < 2;i++){
			if(unoper == unopsym[i])
				return unopsym[i];
		}
	return '\0';
}

string kwconst(){
	string cnst = keyword();
	string cnstsym[] = {"true","false","null","this"};
	for(int i = 0 ; i < 4;i++){
		if(cnst == cnstsym[i])
			return cnstsym[i];
	}
	cnst = "";
	return cnst;
}

void compileSubroutine(){
	printf("<Subroutine>\n");
	printf("<subroutine identifier> %s </subroutine identifier>\n", curtok.c_str());
	advance();
	string t = tokenType();
	string nm;
	char s;
	if(t == "SYMBOL"){
		s = symbol();
		if(s == '('){
			compileExplist();
			advance();
			t = tokenType();
			if( t == "SYMBOL"){
				s = symbol();
				if(s == ')'){
					printf("</Subroutine>\n");
				}
			}
		}
		else if(s == '.'){
			advance();
			nm = identifier();
			printf("<subroutine identifier> %s </subroutine identifier>\n", nm.c_str());
			advance();
			t = tokenType();

			if(t == "SYMBOL"){
				s = symbol();
				if(s == '('){
					compileExplist();
					advance();
					t = tokenType();
					if( t == "SYMBOL"){
						s = symbol();
						if(s == ')'){
							printf("</Subroutine>\n");
						}
					}
				}
			}
		}
	}
}


void compileTerm_(){
	string t;
	t = tokenType();
	char s = peek();
	int i;
	if(s == '(' || s == '.' ){
		printf("<Term>\n");
		printf("<function call identifier> %s </ function call identifier>\n",curtok.c_str());
		compileSubroutine();
		advance();
		t = tokenType();
		if(t == "SYMBOL" ){
			if(curtok == ")"){
				return;
			}
		}
	}
	else if(s == '['){
		printf("<Term>\n");
		printf("<identifier> %s </identifier>\n",curtok.c_str());
		advance();
		printf("<symbol> %s </symbol>\n",curtok.c_str());
		compileExp();
		advance();
		t = tokenType();
		if(t == "SYMBOL" ){
			if(curtok == "]"){
				return;
			}
		}
	}
}


void compileTerm(){
	advance();
	string t = tokenType();
	string x;
	int y;
	char s;
	if(t == "INT_CONST"){
		y = intconstant();
		printf("<Term>\n");
		printf("<integer> %d  </integer>\n",y);
		
	}
	else if( t == "STRING_CONST"){
		x = stringconstant();
		printf("<Term>\n");
		printf("<string> %s  </string>\n",x.c_str());
	}
	else if( t == "KEYWORD"){
		x = kwconst();
		printf("<Term>\n");
		printf("<keywordconst> %s </keywordconst>\n",x.c_str());
	}
	else if( t == "IDENTIFIER"){
		x = identifier();
		compileTerm_();
	}
	else if( t == "SYMBOL"){
		s = symbol();
		if(s == '('){
			printf("<Term>\n");
			printf("<symbol> %c </symbol>\n",s);
			compileExp();
			advance();
			t = tokenType();
			if (t == "SYMBOL"){
				s = symbol();
				if( s == ')'){
					printf("<symbol> %c </symbol>\n",s);
				}
			
		}
		else{
			s = unaryop();
			if(s){
				printf("<Term>\n");
				printf("<symbol> %c </symbol>\n",s);
				compileTerm();
				}
			}
			
		}
	}
	printf("</Term>\n");
}

void compileExp(){
	printf("<Expression>\n");
	compileTerm();
	advance();
	string t = tokenType();

	if (t == "SYMBOL") {
		char s = op();
		if(s){
			while(s){
				printf("<symbol> %c </symbol>\n",s);
				compileTerm();
				advance();
				t = tokenType();
				if (t == "SYMBOL")
					s = op();
				else
					break;
			}
		}
	}
	printf("</Expression>\n");
}

void compileExplist(){
	advance();
	string t = tokenType();
	char s;
	if (t == "SYMBOL") {
		s = symbol();
		if( s == ')'){
			printf("<symbol> %c </symbol>\n",s);
			return;
		}
		else {
			printf("<ExpressionList>\n");
			compileExp();
			advance();
			t = tokenType();
			if (t == "SYMBOL") {
				char s = symbol();
				if( s == ',') {
					while(s == ',') {
						printf("<symbol> %c </symbol>\n",s);
						compileExp();
						advance();
						t = tokenType();
						if (t == "SYMBOL")
							s = symbol();
						else
							break;
					}
				}
			}
			printf("</ExpressionList>\n");
		}
	}
	else {
		printf("<ExpressionList>\n");
		compileExp();
		advance();
		t = tokenType();
		if (t == "SYMBOL") {
			char s = symbol();
			if( s == ',') {
				while(s == ',') {
					printf("<symbol> %c </symbol>\n",s);
					compileExp();
					advance();
					t = tokenType();
					if (t == "SYMBOL")
						s = symbol();
					else
						break;
				}
			}
		}
		printf("</ExpressionList>\n");
	}
}