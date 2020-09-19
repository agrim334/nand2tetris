#include"lexer.h"
void compileTerm();
void compileSubroutine();
void compileExplist();
void compileExp();

/*
void compileClass(){
	if(curtok == "class"){
		advance();
		string t = tokenType();

		if(t == "IDENTIFIER"){
			string classname = identifier();

			if(classname == "") {
				printf("ERROR invalid identifier at line no. %d\n",lineno);
				return;
			}

			advance();
			t = tokenType();
			if (t == "SYMBOL"){
			char c = symbol();
				if(c != '{') {
					printf("ERROR missing { at line no. %d\n",lineno);
					return;
				}		
			}
			advance();
			t = tokenType();
			string funcorvar;
			if( t == "KEYWORD") {
				funcorvar = keyword();
				while(funcorvar == "STATIC" || funcorvar == "FIELD"){
					compileClassVarDec();
					advance();
					t = tokenType();
					if( t == "KEYWORD") {
						advance();
						funcorvar = keyword();
					}
					else
						break;
				}
			}
			if( t == "KEYWORD") {
				funcorvar = keyword();
				while(funcorvar == "FUNCTION" || funcorvar == "METHOD" || funcorvar == "CONSTRUCTOR"){
					compileSubroutine();
					advance();
					t = tokenType();
					if( t == "KEYWORD") {
						advance();
						funcorvar = keyword();
					}
					else
						break;
				}
			}
			advance();
			t = tokenType();
			if(t == "SYMBOL"){
				char symb = symbol();
				if(symb == '}')
					return;
				printf("ERROR missing } at line no. %d\n",lineno);
			}
		}
	}
}

void compileClassVarDec(){
	string t = tokenType();
	if( t == "KEYWORD") { 
		string classvartype = keyword();
		if(classvartype == "STATIC" || classvartype == "FIELD" ){
			gettype();
			advance();
			t = tokenType();
			if( t == "IDENTIFIER") { 
				string varname = identifier();
				advance();
				t = tokenType();
				if(t == "SYMBOL"){
					char symb = symbol();
					while(symb == ','){
						advance();
						t = tokenType();
						if(t == "IDENTIFIER"){
							varname = identifier();
							advance();
							t = tokenType();
							if(t == "SYMBOL")
								symb = symbol();
							else{
								printf("ERROR invalid symbol at line no. %d\n",lineno);
								break;
							}
						}
						else{
							printf("ERROR missing identifier at line no. %d\n",lineno);
							break;
						}
					}
					if(symb == ';')
						return;
				}
			}
		}
	}
}

void compileVarDec(){
	string t = tokenType();
	if( t == "KEYWORD") { 
		string var = keyword();
		if(var == "VAR"){
			advance();
			t = tokenType();
			string retype;
			if(t == "KEYWORD") { 
				string retype = keyword();
				gettype();
				retype = curtok;
				}
				advance();
				t = tokenType();
				if(t == "IDENTIFIER"){
					string funcname = identifier();
					while(symb == ','){
						advance();
						t = tokenType();
						if(t == "IDENTIFIER"){
							varname = identifier();
							advance();
							t = tokenType();
							if(t == "SYMBOL")
								symb = symbol();
							else{
								printf("ERROR invalid symbol at line no. %d\n",lineno);
								break;
							}
						}
						else{
							printf("ERROR missing identifier at line no. %d\n",lineno);
							break;
						}
					}
					if(symb == ';')
						return;
				}
			}
		}
	}
}

void compilestate(){
	;
}

void compileDo(){
	;
}

void compileWhile(){
	;
}

void compileReturn(){
	;
}

void compileIf(){
	;
}
*/
void compileSubroutine(){
	printf("<Subroutine>\n");
	advance();
	string t = tokenType();
	string nm;
	char s;
	if(t == "IDENTIFIER") {
		nm = identifier();
		printf("<identifier> %s </identifier>\n",nm.c_str());
		advance();
		t = tokenType();
		if(t == "SYMBOL") {
			s = symbol();
			if(s == '(') {
				printf("<symbol> %c </symbol>\n",s);
				compileExplist();
				t = tokenType();
				if(t == "SYMBOL"){
					s = symbol();
					if(s == ')'){
						printf("<symbol> %c </symbol>\n",s);
						return;
					}
				}
				else{
					advance();
					if(t == "SYMBOL"){
						s = symbol();
						if(s == ')'){
							printf("<symbol> %c </symbol>\n",s);
							return;
						}
					}
				}
			}
			else if(s == '.'){
				printf("<symbol> %c </symbol>\n",s);
				advance();
				t = tokenType();
				if(t == "IDENTIFIER"){
					nm = identifier();
					printf("<identifier> %s </identifier>\n",nm.c_str());
					advance();
					t = tokenType();
					if(t == "SYMBOL") {
						s = symbol();
						if(s == '(') {
							compileExplist();
							t = tokenType();
							if(t == "SYMBOL"){
								s = symbol();
								if(s == ')')
									return;
							}
						}
						else{
							advance();
							if(t == "SYMBOL"){
								s = symbol();
								if(s == ')')
									return;
							}
						}
					}
				}
			}
		}
	}
}


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

void compileTerm(){
	printf("<Term>\n");
	advance();
	string t = tokenType();
	string x;
	int y;
	char s;

	if(t == "INT_CONST"){
		y = intconstant();
		printf("<integer> %d  </integer>\n",y);
	}
	else if( t == "STRING_CONST"){
		x = stringconstant();
		printf("<string> %s  </string>\n",x.c_str());
	}
	else if( t == "KEYWORD"){
		x = kwconst();
		printf("<keywordconst> %s </keywordconst>\n",x.c_str());
	}
	else if( t == "IDENTIFIER"){
		x = identifier();
		printf("<identifier> %s </identifier>\n",x.c_str());
		advance();
		t = tokenType();
		s = symbol();
		printf("%s %s",curtok.c_str(),t.c_str());

		if(t == "SYMBOL"){
			s = symbol();
			if(s == '['){
				printf("<symbol> %c </symbol>\n",s);
				compileExp();
				advance();
				t = tokenType();
				if (t == "SYMBOL"){
					s = symbol();
					if( s == ']'){
						printf("<symbol> %c </symbol>\n",s);
					}
				}
			}
			else if( s == '('){
				printf("<symbol> %c </symbol>\n",s);
				compileSubroutine();
				advance();
				t = tokenType();
				if (t == "SYMBOL"){
					s = symbol();
					if( s == ')'){
						printf("<symbol> %c </symbol>\n",s);
					}
				}
			}
		}
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
		else{
			s = unaryop();
			if(s){
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
	string t = tokenType();

	if( t != "SYMBOL")	
		advance();

	t = tokenType();

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