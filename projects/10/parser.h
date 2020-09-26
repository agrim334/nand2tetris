#include"lexer.h"
//expression
void compileTerm();
void compileSubroutine();
void compileExplist();
void compileExp();
//statements
void compileStatements();
void compileStatement();
void compileIfStatement();
void compileWhileStatement();
void compileDoStatement();
void compileReturnStatement();
void compileLetStatement();
void compileStatement();
//class
void compileClass();
void compileClassVarDec();
void compileIfstatement();
void compileWhilestatement();
void compileDoStatement();
void compileReturnStatement();
void compileLetStatement();
void compileStatement();

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


void compileLetStatement(){
	printf("<Let Statement>\n");
	advance();
	string nm = identifier();
	printf("<VarName > %s </VarName>\n", nm.c_str());
	advance();
	char s;
	if(curtok == "["){
		printf("<symbol> [ </symbol>\n");	
		compileExp();
		s = symbol();
		if(s == ']'){
			advance();
			printf("<symbol> %c </symbol>\n",s);
		}
	}
	if(curtok == "="){
		compileExp();
		s = symbol();
		if(s == ';'){
			printf("<symbol> ; </symbol>\n");	
			printf("</Let Statement>\n");
		}
	}
}

void compileDoStatement(){
	printf("<Do Statement>\n");
	advance();
	compileSubroutine();
	char s = symbol();
	if(s == ';'){
		printf("<symbol> ; </symbol>\n");	
		printf("</Do Statement>\n");
	}
}

void compileReturnStatement(){
	printf("<Return Statement>\n");
	char s = symbol();
	if(s != ';'){
		compileExp();
		s = symbol();
		if (s == ';')
			printf("<symbol> ; </symbol>\n");
	}
	else
		printf("<symbol> ; </symbol>\n");
	printf("</Return Statement>\n");
}

void compileStatement(){
	advance();
	if(curtok == "let"){
		compileLetStatement();
	}
	/*else if(curtok == "if"){
		compileIfStatement();
	}
	else if(curtok == "while"){
		compileWhileStatement();
	}*/
	else if(curtok == "do"){
		compileDoStatement();
	}
	else if(curtok == "return"){
		compileReturnStatement();
	}
}

void compileStatements(){
	compileStatement();
}

void compileSubroutine(){
	printf("<Subroutine>\n");
	string nm = curtok;
	advance();
	string t = tokenType();
	char s;
	if(t == "SYMBOL"){
		s = symbol();
		if(s == '('){
			printf("<subroutine identifier> %s </subroutine identifier>\n", nm.c_str());
			printf("<symbol> %s </symbol>\n",curtok.c_str());
			compileExplist();
			t = tokenType();
			if( t == "SYMBOL"){
				s = symbol();
				if(s == ')'){
					printf("<symbol> %s </symbol>\n",curtok.c_str());
					printf("</Subroutine>\n");
				}
			}
		}
		else if(s == '.'){
			printf("<class identifier> %s </class identifier>\n", nm.c_str());
			printf("<symbol> %s </symbol>\n",curtok.c_str());
			advance();
			t = tokenType();
			if(t == "IDENTIFIER"){
				nm = identifier();
				printf("<subroutine identifier> %s </subroutine identifier>\n", nm.c_str());
				advance();
				t = tokenType();
				if(t == "SYMBOL"){
					s = symbol();
					if(s == '('){
						printf("<symbol> %s </symbol>\n",curtok.c_str());
						compileExplist();
						t = tokenType();
						if( t == "SYMBOL"){
							s = symbol();
							if(s == ')'){
								printf("<symbol> %s </symbol>\n",curtok.c_str());
								printf("</Subroutine>\n");
							}
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
		compileSubroutine();
		t = tokenType();
		if(t == "SYMBOL" ){
			s = symbol();
			if(s == ']'){
				printf("<symbol> %c </symbol>\n",s);
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
		t = tokenType();
		if(t == "SYMBOL" ){
			s = symbol();
			if(s == ']'){
				printf("<symbol> %c </symbol>\n",s);
				return;
			}
		}
	}
	else{
		printf("</Term>\n");
		printf("<identifier> %s </identifier>\n",curtok.c_str());

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
	string t;
	char s = peek();
	if(s == ')')
		return;
	printf("<ExpressionList>\n");
	compileExp();
	s = symbol();
	if( s == ',') {
		while(s == ',') {
			printf("<symbol> %c </symbol>\n",s);
			compileExp();
//			advance();
			t = tokenType();
			if (t == "SYMBOL")
				s = symbol();
			else
				break;
		}
	}
	printf("</ExpressionList>\n");
}