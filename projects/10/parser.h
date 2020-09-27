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
	if(s == ')'){
		advance();
		return;
	}
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

void compileIfStatement(){
	printf("<If Statement>\n");
	advance();
	printf("<symbol> ( </symbol>\n");	
	compileExp();
	char s = symbol();
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
	printf("</If Statement>\n");
}

void compileWhileStatement(){
	printf("<While Statement>\n");
	advance();
	printf("<symbol> ( </symbol>\n");	
	compileExp();
	char s = symbol();
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
	printf("</While Statement>\n");
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
	printf("<Statements>\n");
	while(curtok != "}")
		compileStatement();
	printf("</Statements>\n");
}

void compileVarDec(){
	printf("<VarDeclaration>\n");
	advance();
	string t = type();
	printf("<VarType> %s </VarType>\n",t.c_str());
	advance();
	string vn = identifier();
	printf("<VarNameDeclared> %s </VarNameDeclared>\n",vn.c_str());
	advance();
	char s = symbol();
	if( s == ',') {
		while(s == ',') {
			printf("<symbol> %c </symbol>\n",s);
			vn = identifier();
			printf("<VarNameDeclared> %s </VarNameDeclared>\n",vn.c_str());
//			advance();
			t = tokenType();
			if (t == "SYMBOL")
				s = symbol();
			else
				break;
		}
	}
	s = symbol();
	if (s == ';')
		printf("<symbol> ; </symbol>\n");
	printf("</VarDeclaration>\n");
}

void compileSubroutineBody(){
	printf("<SubroutineBody>\n");
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
		printf("</SubroutineBody>\n");
	}
}

void compileParameterlist(){
	string t;
	char s = peek();
	if(s == ')'){
		advance();
		return;
	}
	advance();
	printf("<ParameterList>\n");
	t = type();
	printf("<ParaVarType> %s </ParaVarType>\n",t.c_str());
	advance();
	string vn = identifier();
	printf("<ParaVarNameDeclared> %s </ParaVarNameDeclared>\n",vn.c_str());
	advance();
	s = symbol();
	if( s == ',') {
		while(s == ',') {
			printf("<symbol> %c </symbol>\n",s);
			advance();
			t = type();
			printf("<ParaVarType> %s </ParaVarType>\n",t.c_str());
			advance();
			string vn = identifier();
			printf("<ParaVarNameDeclared> %s </ParaVarNameDeclared>\n",vn.c_str());
			advance();
			t = tokenType();
			if (t == "SYMBOL")
				s = symbol();
			else
				break;
		}
	}
	if(s == ')'){
		printf("<symbol> %c </symbol>\n",s);
		printf("</ParameterList>\n");
	}
}

void compileSubroutineHead(){
	printf("<Subroutine Declaration>\n");
	printf("<SubroutineType> %s </SubroutineType>\n",curtok.c_str());
	advance();
	string t;
	if(curtok == "void")
		t = curtok;
	else
		t = type();
	printf("<SubroutineReturnType> %s </SubroutineReturnType>\n",t.c_str());
	advance();
	string sbn = identifier();
	printf("<SubroutineName> %s </SubroutineName>\n",sbn.c_str());	
	advance();
	char s = symbol();
	if(s == '('){
		printf("<symbol> %c </symbol>\n",s);
		compileParameterlist();
		t = tokenType();
		if( t == "SYMBOL"){
			s = symbol();
			if(s == ')'){
				printf("<symbol> %s </symbol>\n",curtok.c_str());
			}
		}
		compileSubroutineBody();
	printf("</Subroutine Declaration>\n");
	}
}

void compileClassVarDec(){
	printf("<ClassVarDeclaration>\n");
	printf("<ClassVarScope> %s </ClassVarScope>\n",curtok.c_str());
	advance();
	string t = type();
	printf("<ClassVarType> %s </ClassVarType>\n",t.c_str());
	advance();
	string vn = identifier();
	printf("<ClassVarNameDeclared> %s </ClassVarNameDeclared>\n",vn.c_str());
	advance();
	char s = symbol();
	while(s == ',') {
		printf("<symbol> %c </symbol>\n",s);
		advance();
		vn = identifier();
		printf("<ClassVarNameDeclared> %s </ClassVarNameDeclared>\n",vn.c_str());
		advance();
		s = symbol();
	}
	if (s == ';'){
		printf("<symbol> ; </symbol>\n");
		printf("</ClassVarDeclaration>\n");
	}
}

void compileClass(){
	advance();
	printf("<Class Declaration>\n");
	string cn = identifier();
	string t;
	printf("<ClassName> %s </ClassName>\n",cn.c_str());
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
			printf("</Class Declaration>\n");
		}
	}
}