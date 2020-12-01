#include"lexer.h"
#include"SymbolTable.h"
#include <algorithm>

void writePush(string seg,int ind){
	string xmlout = "push "+ seg + " " + to_string(ind) +"\n"; 
	fprintf(vmf,"%s",xmlout.c_str());
}

void writePop(string seg,int ind){
	string xmlout = "pop "+ seg + " " + to_string(ind) +"\n"; 
	fprintf(vmf,"%s",xmlout.c_str());
}

void writeArith(string com){
	fprintf(vmf,"%s\n",com.c_str());
}

void writeLabel(string label){
	fprintf(vmf,"label %s\n",label.c_str());
}

void writeGoto(string label){
	fprintf(vmf,"goto %s\n",label.c_str());
}

void writeIf(string label){
	fprintf(vmf,"if-goto %s\n",label.c_str());
}

void writeCall(string name,int argsc){
	string xmlout = "call "+ name + " " + to_string(argsc) +"\n"; 
	fprintf(vmf,"%s\n",xmlout.c_str());
}

void writeFunction(string name,int argsc){
	string xmlout = "function "+ name + " " + to_string(argsc) +"\n"; 
	fprintf(vmf,"%s\n",xmlout.c_str());
}

void writeReturn(){
	fprintf(vmf,"return\n");
}
