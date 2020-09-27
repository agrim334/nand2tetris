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
void compileVarDec();
void compileSubroutineHead();
void compileParameterlist();
void compileSubroutineBody();

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

string type(){
	string tp = keyword();
	string primtp[] = {"int","char","boolean"};
	for(int i = 0 ; i < 3;i++){
		if(tp == primtp[i])
			return primtp[i];
	}
	tp = identifier();
	return tp;
}

void compileSubroutine(){
	string nm = curtok;
	advance();
	string t = tokenType();
	char s;
	if(t == "SYMBOL"){
		s = symbol();
		if(s == '('){
			printf("<identifier> %s </identifier>\n", nm.c_str());
			printf("<symbol> %s </symbol>\n",curtok.c_str());
			compileExplist();
			t = tokenType();
			if( t == "SYMBOL"){
				s = symbol();
				if(s == ')'){
					printf("<symbol> %s </symbol>\n",curtok.c_str());
				}
			}
		}
		else if(s == '.'){
			printf("<identifier> %s </identifier>\n", nm.c_str());
			printf("<symbol> %s </symbol>\n",curtok.c_str());
			advance();
			t = tokenType();
			if(t == "IDENTIFIER"){
				nm = identifier();
				printf("<identifier> %s </identifier>\n", nm.c_str());
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
		printf("<identifier> %s </identifier>\n",curtok.c_str());
	}
}


void compileTerm(){
	advance();
	string t = tokenType();
	string x;
	int y;
	char s;
	printf("<term>\n");

	if(t == "INT_CONST"){
		y = intconstant();
		printf("<integerConstant> %d  </integerConstant>\n",y);		
	}
	else if( t == "STRING_CONST"){
		x = stringconstant();
		printf("<stringConstant> %s  </stringConstant>\n",x.c_str());
	}
	else if( t == "KEYWORD"){
		x = kwconst();
		printf("<keyword> %s </keyword>\n",x.c_str());
	}
	else if( t == "IDENTIFIER"){
		x = identifier();
		compileTerm_();
	}
	else if( t == "SYMBOL"){
		s = symbol();
		if(s == '('){
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
				printf("<symbol> %c </symbol>\n",s);
				compileTerm();
			}
		}

	}
	 printf("</term>\n");
}

void compileExp(){
	printf("<expression>\n");
	compileTerm();
	advance();
	string t = tokenType();

	if (t == "SYMBOL") {
		char s = op();
		while(s){
			compileTerm();
			advance();
			t = tokenType();
			if (t == "SYMBOL")
				s = op();
			else
				break;
		}
	}
	printf("</expression>\n");
}

void compileExplist(){
	char s = symbol();
	printf("<expressionList>\n");
	printf("<symbol> %c </symbol>\n",s);
	string t;
	s = peek();
	if(s == ')'){
		advance();
		printf("<symbol> %c </symbol>\n",s);
		printf("</expressionList>\n");
		return;
	}
	compileExp();
	s = symbol();
	while(s == ',') {
		compileExp();
//		advance();
		t = tokenType();
		if (t == "SYMBOL")
			s = symbol();
		else
			break;
	}
	printf("<symbol> %c </symbol>\n",s);
	printf("</expressionList>\n");
}

void compileIfStatement(){
	printf("<ifStatement>\n");
	advance();
	char s = symbol();
	printf("<symbol> %c </symbol>\n",s);	
	compileExp();
	s = symbol();
	if(s == ')'){
		advance();
		printf("<symbol> %c </symbol>\n",s);
		s = symbol();
		if(s == '{'){
			compileStatements();
			s = symbol();
			if(s == '}'){
				advance();
				printf("<symbol> %c </symbol>\n",s);
			}
		}
	}
	if(curtok == "else"){
		advance();
		s = symbol();
		printf("<symbol> %c </symbol>\n",s);
		compileStatements();
		s = symbol();
		if(s == '}'){
			advance();
			printf("<symbol> %c </symbol>\n",s);
		}

	}
	printf("</ifStatement>\n");
}

void compileWhileStatement(){
	printf("<whileStatement>\n");
	advance();
	char s = symbol();
	printf("<symbol> %c </symbol>\n",s);	
	compileExp();
	s = symbol();
	if(s == ')'){
		advance();
		printf("<symbol> %c </symbol>\n",s);
		s = symbol();
		if(s == '{'){
			compileStatements();
			s = symbol();
			if(s == '}'){
				advance();
				printf("<symbol> %c </symbol>\n",s);
			}
		}
	}
	printf("</whileStatement>\n");
}

void compileLetStatement(){
	printf("<letStatement>\n");
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
			printf("</letStatement>\n");
		}
	}
}

void compileDoStatement(){
	printf("<doStatement>\n");
	advance();
	compileSubroutine();
	char s = symbol();
	if(s == ';'){
		printf("<symbol> ; </symbol>\n");	
		printf("</doStatement>\n");
	}
}

void compileReturnStatement(){
	printf("<returnStatement>\n");
	advance();
	char s = peek();
	if(s != ';'){
		compileExp();
		s = symbol();
		if (s == ';')
			printf("<symbol> ; </symbol>\n");
	}
	else{
		printf("<symbol> ; </symbol>\n");
	}
	printf("</returnStatement>\n");
}

void compileStatement(){
	advance();
	if(curtok == "let"){
		compileLetStatement();
	}
	else if(curtok == "if"){
		compileIfStatement();
	}
	else if(curtok == "while"){
		compileWhileStatement();
	}
	else if(curtok == "do"){
		compileDoStatement();
	}
	else if(curtok == "return"){
		compileReturnStatement();
	}
}

void compileStatements(){
	printf("<statements>\n");
	while(curtok != "}")
		compileStatement();
	printf("</statements>\n");
}

void compileVarDec(){
	printf("<varDec>\n");
	advance();
	string t = type();
	string tokt = tokenType();
	if(tokt == "IDENTIFIER")
		printf("<identifier> %s </identifier>\n",t.c_str());
	else
		printf("<keyword> %s </keyword>\n",t.c_str());
	advance();
	string vn = identifier();
	printf("<identifier> %s </identifier>\n",vn.c_str());
	advance();
	char s = symbol();
	while(s == ',') {
		advance();
		vn = identifier();
		printf("<identifier> %s </identifier>\n",vn.c_str());
		advance();
		t = tokenType();
		if (t == "SYMBOL")
			s = symbol();
		else
			break;
	}
	if(s == ';'){
		printf("<symbol> ; </symbol>\n");
		printf("</varDec>\n");
	}
}

void compileSubroutineBody(){
	printf("<subroutineBody>\n");
	advance();
	char s = symbol();
	printf("<symbol> %c </symbol>\n",s);
	advance();
	while(curtok == "var"){
		compileVarDec();
		advance();
	}
	compileStatements();
	s = symbol();
	if(s == '}'){
		printf("<symbol> %c </symbol>\n",s);
		printf("</subroutineBody>\n");
	}
}

void compileParameterlist(){
	printf("<parameterList>\n");
	printf("<symbol> %s </symbol>\n",curtok.c_str());
	string t;
	char s = peek();
	if(s == ')'){
		advance();
		printf("</parameterList>\n");
		printf("<symbol> %c </symbol>\n",s);
		return;
	}
	advance();
	t = type();
	string tokt = tokenType();
	if(tokt == "IDENTIFIER")
		printf("<identifier> %s </identifier>\n",t.c_str());
	else
		printf("<keyword> %s </keyword>\n",t.c_str());
	advance();
	string vn = identifier();
	printf("<identifier> %s </identifier>\n",vn.c_str());
	advance();
	s = symbol();
	while(s == ',') {
		advance();
		t = type();
		tokt = tokenType();
		if(tokt == "IDENTIFIER")
			printf("<identifier> %s </identifier>\n",t.c_str());
		else
			printf("<keyword> %s </keyword>\n",t.c_str());
		advance();
		vn = identifier();
		printf("<identifier> %s </identifier>\n",vn.c_str());
		advance();
		t = tokenType();
		if (t == "SYMBOL")
			s = symbol();
		else
			break;
	}
	if(s == ')'){
		printf("<symbol> %c </symbol>\n",s);
		printf("</parameterList>\n");
	}
}

void compileSubroutineHead(){
	printf("<subroutineDec>\n");
	printf("<keyword> %s </keyword>\n",curtok.c_str());
	advance();
	string t;
	if(curtok == "void")
		t = curtok;
	else
		t = type();
	string tokt = tokenType();
	if(tokt == "IDENTIFIER")
		printf("<identifier> %s </identifier>\n",t.c_str());
	else
		printf("<keyword> %s </keyword>\n",t.c_str());
	advance();
	string sbn = identifier();
	printf("<identifier> %s </identifier>\n",sbn.c_str());	
	advance();
	char s = symbol();
	if(s == '('){
		compileParameterlist();
		compileSubroutineBody();
		printf("</subroutineDec>\n");
	}
}

void compileClassVarDec(){
	printf("<classVarDec>\n");
	printf("<keyword> %s </keyword>\n",curtok.c_str());
	advance();
	string t = type();
	string tokt = tokenType();
	if(tokt == "IDENTIFIER")
		printf("<identifier> %s </identifier>\n",t.c_str());
	else
		printf("<keyword> %s </keyword>\n",t.c_str());

	advance();
	string vn = identifier();
	printf("<identifier> %s </identifier>\n",vn.c_str());
	advance();
	char s = symbol();
	while(s == ',') {
		advance();
		vn = identifier();
		printf("<identifier> %s </identifier>\n",vn.c_str());
		advance();
		s = symbol();
	}
	if (s == ';'){
		printf("<symbol> ; </symbol>\n");
		printf("</classVarDec>\n");
	}
}

void compileClass(){
	printf("<class>\n");
	printf("<keyword> %s </keyword>\n",curtok.c_str());
	advance();
	string cn = identifier();
	string t;
	printf("<identifier> %s </identifier>\n",cn.c_str());
	advance();
	char s = symbol();
	if(s == '{'){
		printf("<symbol> %c </symbol>\n",s);
		advance();
		while(curtok == "static" || curtok == "field"){
			compileClassVarDec();
			advance();
		}
		while(curtok == "constructor" || curtok == "method" || curtok == "function"){
			compileSubroutineHead();
			advance();
		}
		s = symbol();
		if(s == '}'){
			printf("<symbol> %c </symbol>\n",s);
			printf("</class>\n");
		}
	}
}