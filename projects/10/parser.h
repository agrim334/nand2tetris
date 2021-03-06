#include"lexer.h"
#include <algorithm>
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
int f = 0;

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
    transform(cnst.begin(), cnst.end(), cnst.begin(), ::tolower);
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
    transform(tp.begin(), tp.end(), tp.begin(), ::tolower);
	string primtp[] = {"int","char","boolean"};
	for(int i = 0 ; i < 3;i++){
		if(tp == primtp[i])
			return primtp[i];
	}
	tp = identifier();
	return tp;
}

void compileSubroutine(){
	string xmlout = "";
	string nm = curtok;
	xmlout ="<identifier> "  + nm + " </identifier>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	advance();
	string t = tokenType();
	char s;
	if(t == "SYMBOL"){
		s = symbol();
		if(s == '('){
			compileExplist();
		}
		else if(s == '.'){
			xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
			fprintf(vmf,"%s",xmlout.c_str());
			advance();
			t = tokenType();
			if(t == "IDENTIFIER"){
				nm = identifier();
				xmlout ="<identifier> "  + nm + " </identifier>\n";
				fprintf(vmf,"%s",xmlout.c_str());
				advance();
				t = tokenType();
				if(t == "SYMBOL"){
					s = symbol();
					if(s == '(')
						compileExplist();
				}
			}
		}
	}
}

void compileTerm_(){
	string xmlout = "";
	string t;
	t = tokenType();
	char s = peek();
	int i;

	if(s == '(' || s == '.'){
		compileSubroutine();
		t = tokenType();
		if(t == "SYMBOL" ){
			s = symbol();
			if(s == ')'){
				return;
			}
		}
	}
	else if(s == '['){
		xmlout ="<identifier> "  + curtok + " </identifier>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		advance();
		xmlout ="<symbol> "  + curtok + " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		compileExp();
		t = tokenType();
		if(t == "SYMBOL" ){
			s = symbol();
			if(s == ']'){
				xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
				fprintf(vmf,"%s",xmlout.c_str());
				return;
			}
		}
	}
	else{
		xmlout ="<identifier> "  + curtok + " </identifier>\n";
		fprintf(vmf,"%s",xmlout.c_str());
	}
}


void compileTerm(){
	advance();
	string xmlout = "";
	string t = tokenType();
	string x;
	int y;
	char s;
	xmlout ="<term>\n";
	fprintf(vmf,"%s",xmlout.c_str());

	if(t == "INT_CONST"){
		y = intconstant();
		xmlout ="<integerConstant> ";
		xmlout += to_string(y);
		xmlout += "  </integerConstant>\n";
		fprintf(vmf,"%s",xmlout.c_str());
	}
	else if( t == "STRING_CONST"){
		x = stringconstant();
		xmlout ="<stringConstant>  " + x + " </stringConstant>\n";
		fprintf(vmf,"%s",xmlout.c_str());
	}
	else if( t == "KEYWORD"){
		x = kwconst();
		xmlout ="<keyword>  " + x + " </keyword>\n";
		fprintf(vmf,"%s",xmlout.c_str());
	}
	else if( t == "IDENTIFIER")
		compileTerm_();

	else if( t == "SYMBOL"){
		s = symbol();
		if(s == '('){
			xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
			fprintf(vmf,"%s",xmlout.c_str());
			compileExp();
	//		advance();
			t = tokenType();
			if (t == "SYMBOL"){
				s = symbol();
				if( s == ')'){
					xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
					fprintf(vmf,"%s",xmlout.c_str());
				}
			}
		}
		else{
			s = unaryop();
			if(s){
				xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
				fprintf(vmf,"%s",xmlout.c_str());
				compileTerm();
			}
		}

	}
	xmlout ="</term>\n";
	fprintf(vmf,"%s",xmlout.c_str());
}

void compileExp(){
	string xmlout = "";
	xmlout ="<expression>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	compileTerm();
	advance();
	string t = tokenType();

	if (t == "SYMBOL") {
		char s = op();
		while(s){
			if(s == '<')
				xmlout = "<symbol> &lt; </symbol>\n";
			else if(s == '>')
				xmlout = "<symbol> &gt; </symbol>\n";
			else if(s == '"')
				xmlout = "<symbol> &quot; </symbol>\n";
			else if(s == '&')
				xmlout = "<symbol> &amp; </symbol>\n";
			else{
				xmlout = "<symbol> "; xmlout += s; xmlout += " </symbol>\n";
			}
			fprintf(vmf,"%s",xmlout.c_str());
			compileTerm();
			advance();
			t = tokenType();
			if (t == "SYMBOL")
				s = op();
			else
				break;
		}
	}
	xmlout ="</expression>\n";
	fprintf(vmf,"%s",xmlout.c_str());
}

void compileExplist(){
	string xmlout = "";
	char s = symbol();
	xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	xmlout ="<expressionList>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	string t;
	s = peek();
	if(s == ')'){
		advance();
		xmlout ="</expressionList>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		return;
	}
	compileExp();
	s = symbol();
	while(s == ',') {
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		compileExp();
		t = tokenType();
		if (t == "SYMBOL")
			s = symbol();
		else
			break;
	}
	xmlout ="</expressionList>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
	fprintf(vmf,"%s",xmlout.c_str());
}

void compileElseStatement(){
	string xmlout = "";
	char s;
	xmlout = "<keyword> " + curtok + " </keyword>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	advance();
	s = symbol();
	xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	compileStatements();
	s = symbol();
	if(s == '}'){
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
	}
	xmlout ="</ifStatement>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	f = 0;
}

void compileIfStatement(){
	string xmlout = "";
	xmlout ="<ifStatement>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	xmlout = "<keyword> " + curtok + " </keyword>\n";
	fprintf(vmf,"%s",xmlout.c_str());

	advance();
	char s = symbol();
	xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";	
	fprintf(vmf,"%s",xmlout.c_str());
	compileExp();
	s = symbol();
	if(s == ')'){
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		advance();
		s = symbol();
		if(s == '{'){
			xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
			fprintf(vmf,"%s",xmlout.c_str());
			compileStatements();
			s = symbol();
			if(s == '}'){
				xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
				fprintf(vmf,"%s",xmlout.c_str());
			}
		}
	}
	f = 1;
}

void compileWhileStatement(){
	string xmlout = "";
	xmlout ="<whileStatement>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	xmlout = "<keyword> " + curtok + " </keyword>\n";
	fprintf(vmf,"%s",xmlout.c_str());

	advance();
	char s = symbol();
	xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";	
	fprintf(vmf,"%s",xmlout.c_str());
	compileExp();
	s = symbol();
	if(s == ')'){
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		advance();
		s = symbol();
		if(s == '{'){
			xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
			fprintf(vmf,"%s",xmlout.c_str());
			compileStatements();
			s = symbol();
			if(s == '}'){
				xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
				fprintf(vmf,"%s",xmlout.c_str());
			}
		}
	}
	xmlout ="</whileStatement>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	f = 0;
}

void compileLetStatement(){
	string xmlout = "";
	xmlout ="<letStatement>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	xmlout = "<keyword> " + curtok + " </keyword>\n";
	fprintf(vmf,"%s",xmlout.c_str());

	advance();
	string nm = identifier();
	xmlout = "<identifier> " + nm + " </identifier>\n";
	fprintf(vmf,"%s",xmlout.c_str());

	advance();
	char s;
	if(curtok == "["){
		s = symbol();
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		compileExp();
		s = symbol();
		if(s == ']'){
			advance();
			xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
			fprintf(vmf,"%s",xmlout.c_str());
		}
	}
	if(curtok == "="){
		s = symbol();
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		compileExp();
		s = symbol();
		if(s == ';'){
			xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
			fprintf(vmf,"%s",xmlout.c_str());
			xmlout ="</letStatement>\n";
			fprintf(vmf,"%s",xmlout.c_str());
		}
	}
	f = 0;
}

void compileDoStatement(){
	string xmlout = "";
	xmlout ="<doStatement>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	xmlout = "<keyword> " + curtok + " </keyword>\n";
	fprintf(vmf,"%s",xmlout.c_str());

	advance();
	compileSubroutine();
	advance();
	char s = symbol();
	if(s == ';'){
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		xmlout ="</doStatement>\n";
		fprintf(vmf,"%s",xmlout.c_str());
	}
	f = 0;
}

void compileReturnStatement(){
	string xmlout = "";
	xmlout ="<returnStatement>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	xmlout = "<keyword> " + curtok + " </keyword>\n";
	fprintf(vmf,"%s",xmlout.c_str());

	char s = peek();
	if(s != ';'){
		compileExp();
		s = symbol();
		if (s == ';'){
			xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
			fprintf(vmf,"%s",xmlout.c_str());
		}
	}	
	else{
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
	}
	xmlout ="</returnStatement>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	f = 0;
}

void compileStatement(){
	string xmlout = "";
	if(f && curtok != "else"){
		xmlout ="</ifStatement>\n";
		fprintf(vmf,"%s",xmlout.c_str());
	}
	f = 0;
	if(curtok == "let"){
		compileLetStatement();
	}
	else if(curtok == "if"){
		compileIfStatement();
	}
	else if(curtok == "else"){
		compileElseStatement();
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
	string xmlout = "";
	xmlout ="<statements>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	while(curtok != "}"){
		compileStatement();
		advance();
	}
	xmlout ="</statements>\n";
	fprintf(vmf,"%s",xmlout.c_str());
}

void compileVarDec(){
	string xmlout = "";
	xmlout ="<varDec>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	xmlout = "<keyword> " + curtok + " </keyword>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	advance();
	string t = type();
	string tokt = tokenType();
	if(tokt == "IDENTIFIER")
		xmlout ="<identifier> "  + t + " </identifier>\n";
	else
		xmlout = "<keyword> " + t + " </keyword>\n";

	fprintf(vmf,"%s",xmlout.c_str());
	advance();
	string vn = identifier();
	xmlout ="<identifier> "  + vn + " </identifier>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	advance();
	char s = symbol();
	while(s == ',') {
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		advance();
		vn = identifier();
		xmlout ="<identifier> "  + vn + " </identifier>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		advance();
		t = tokenType();
		if (t == "SYMBOL")
			s = symbol();
		else
			break;
	}
	if(s == ';'){
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		xmlout ="</varDec>\n";
		fprintf(vmf,"%s",xmlout.c_str());
	}
}

void compileSubroutineBody(){
	string xmlout = "";
	xmlout ="<subroutineBody>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	advance();
	char s = symbol();
	xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	advance();
	while(curtok == "var"){
		compileVarDec();
		advance();
	}
	compileStatements();
	s = symbol();
	if(s == '}'){
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		xmlout ="</subroutineBody>\n";
		fprintf(vmf,"%s",xmlout.c_str());
	}
}

void compileParameterlist(){
	string xmlout = "";
	xmlout ="<symbol> "  + curtok + " </symbol>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	xmlout ="<parameterList>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	string t;
	char s = peek();
	if(s == ')'){
		advance();
		xmlout ="</parameterList>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		return;
	}
	advance();
	t = type();
	string tokt = tokenType();
	if(tokt == "IDENTIFIER")
		xmlout ="<identifier> "  + t + " </identifier>\n";
	else
		xmlout = "<keyword> " + t + " </keyword>\n";

	fprintf(vmf,"%s",xmlout.c_str());
	advance();
	string vn = identifier();
	xmlout ="<identifier> "  + vn + " </identifier>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	advance();
	s = symbol();
	while(s == ',') {
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		advance();
		t = type();
		tokt = tokenType();
		if(tokt == "IDENTIFIER")
			xmlout ="<identifier> "  + t + " </identifier>\n";
		else
			xmlout = "<keyword> " + t + " </keyword>\n";

		fprintf(vmf,"%s",xmlout.c_str());
		advance();
		vn = identifier();
		xmlout ="<identifier> "  + vn + " </identifier>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		advance();
		t = tokenType();
		if (t == "SYMBOL")
			s = symbol();
		else
			break;
	}
	if(s == ')'){
		xmlout ="</parameterList>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
	}
}

void compileSubroutineHead(){
	string xmlout = "";
	xmlout ="<subroutineDec>\n";
	fprintf(vmf,"%s",xmlout.c_str());

	xmlout = "<keyword> " + curtok + " </keyword>\n";
	fprintf(vmf,"%s",xmlout.c_str());

	advance();
	string t;
	if(curtok == "void")
		t = curtok;
	else
		t = type();

	string tokt = tokenType();
	if(tokt == "IDENTIFIER")
		xmlout ="<identifier> "  + t + " </identifier>\n";
	else
		xmlout = "<keyword> " + t + " </keyword>\n";

	fprintf(vmf,"%s",xmlout.c_str());
	advance();
	string sbn = identifier();
	xmlout ="<identifier> "  + sbn + " </identifier>\n";	
	fprintf(vmf,"%s",xmlout.c_str());
	advance();
	char s = symbol();
	if(s == '('){
		compileParameterlist();
		compileSubroutineBody();
		xmlout ="</subroutineDec>\n";
		fprintf(vmf,"%s",xmlout.c_str());
	}
}

void compileClassVarDec(){
	string xmlout = "";
	xmlout ="<classVarDec>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	xmlout = "<keyword> " + curtok + " </keyword>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	advance();
	string t = type();
	string tokt = tokenType();
	if(tokt == "IDENTIFIER")
		xmlout ="<identifier> "  + t + " </identifier>\n";
	else
		xmlout = "<keyword> " + t + " </keyword>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	advance();
	string vn = identifier();
	xmlout ="<identifier> "  + vn + " </identifier>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	advance();
	char s = symbol();
	while(s == ',') {
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		advance();
		vn = identifier();
		xmlout ="<identifier> "  + vn + " </identifier>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		advance();
		s = symbol();
	}
	if (s == ';'){
		xmlout ="<symbol> "; xmlout += s; xmlout += " </symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());
		xmlout ="</classVarDec>\n";
		fprintf(vmf,"%s",xmlout.c_str());
	}
}

void compileClass(){
	f = 0;
	string xmlout = "";
	xmlout ="<class>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	xmlout = "<keyword> " + curtok + " </keyword>\n";
	fprintf(vmf,"%s",xmlout.c_str());
	advance();
	string cn = identifier();
	string t;
	xmlout ="<identifier> " + cn + " </identifier>\n";
	fprintf(vmf,"%s",xmlout.c_str());

	advance();
	char s = symbol();
	if(s == '{'){
		xmlout ="<symbol>";
		xmlout += s;
		xmlout += "</symbol>\n";
		fprintf(vmf,"%s",xmlout.c_str());

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
			xmlout ="<symbol> ";
			xmlout += s;
			xmlout += " </symbol>\n";
			fprintf(vmf,"%s",xmlout.c_str());
			xmlout ="</class>\n";
			fprintf(vmf,"%s",xmlout.c_str());
		}
	}
}