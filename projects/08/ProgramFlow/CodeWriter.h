#include<iostream>
#include<string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
using namespace std;

char curcom[255];
FILE* vmf;
FILE* asmf;
string fname;
int k = 0;
string funcgl="";
DIR* dir;
struct dirent *ent;
int flag = 1;
int id = -1;

void pushpopPrint(string typecom, string seg,int idx){
	string segR;
	string ind; 
	string cmd;

	if(typecom == "C_PUSH") {
		if(seg == "local"){
			segR = "R1";
			ind = to_string(idx);
			cmd = "@" + segR + "\nD=M\n@"+ind+"\nD=D+A\nA=D\nD=M\n@R0\nA=M\nM=D\n@R0\nM=M+1\n";
		}
		else if(seg == "argument"){
			segR="R2";
			ind = to_string(idx);
			cmd = "@" + segR + "\nD=M\n@"+ind+"\nD=D+A\nA=D\nD=M\n@R0\nA=M\nM=D\n@R0\nM=M+1\n";
		}
		else if(seg == "this"){
			segR = "R3";
			ind = to_string(idx);
			cmd = "@" + segR + "\nD=M\n@"+ind+"\nD=D+A\nA=D\nD=M\n@R0\nA=M\nM=D\n@R0\nM=M+1\n";
		}
		else if(seg == "that"){
			segR="R4";
			ind = to_string(idx);
			cmd = "@" + segR + "\nD=M\n@"+ind+"\nD=D+A\nA=D\nD=M\n@R0\nA=M\nM=D\n@R0\nM=M+1\n";
		}
		else if(seg == "pointer"){
			ind = to_string(idx+3);
			segR="R"+ind;
			cmd = "@"+segR+"\nD=M\n@R0\nA=M\nM=D\n@R0\nM=M+1\n";
		}
		else if(seg == "temp"){
			ind = to_string(idx+5);
			segR="R"+ind;
			cmd = "@"+segR+"\nD=M\n@R0\nA=M\nM=D\n@R0\nM=M+1\n";
		}
		else if(seg == "constant"){
			ind = to_string(idx);
			cmd = "@"+ind+"\nD=A\n@R0\nA=M\nM=D\n@R0\nM=M+1\n";
		}
		else if(seg == "static"){
			ind = to_string(idx);
			segR=fname+"."+ind;
			cmd = "@"+segR+"\nD=M\n@R0\nA=M\nM=D\n@R0\nM=M+1\n";
		}
	}
	else if(typecom == "C_POP"){
		if(seg == "local"){
			segR = "R1";
			ind = to_string(idx);
			cmd = "@R0\nM=M-1\n@" + segR + "\nD=M\n@"+ind+"\nD=D+A\n@R13\nM=D\n@R0\nA=M\nD=M\n@R13\nA=M\nM=D\n";
		}
		else if(seg == "argument"){
			segR="R2";
			ind = to_string(idx);
			cmd = "@R0\nM=M-1\n@" + segR + "\nD=M\n@"+ind+"\nD=D+A\n@R13\nM=D\n@R0\nA=M\nD=M\n@R13\nA=M\nM=D\n";
		}
		else if(seg == "this"){
			segR = "R3";
			ind = to_string(idx);
			cmd = "@R0\nM=M-1\n@" + segR + "\nD=M\n@"+ind+"\nD=D+A\n@R13\nM=D\n@R0\nA=M\nD=M\n@R13\nA=M\nM=D\n";
		}
		else if(seg == "that"){
			segR="R4";
			ind = to_string(idx);
			cmd = "@R0\nM=M-1\n@" + segR + "\nD=M\n@"+ind+"\nD=D+A\n@R13\nM=D\n@R0\nA=M\nD=M\n@R13\nA=M\nM=D\n";
		}
		else if(seg == "pointer"){
			ind = to_string(idx+3);
			segR="R"+ind;
			cmd = "@R0\nAM=M-1\nD=M\n@" + segR + "\nM=D\n";
		}
		else if(seg == "temp"){
			ind = to_string(idx+5);
			segR="R"+ind;
			cmd = "@R0\nAM=M-1\nD=M\n@" + segR + "\nM=D\n";
		}
		else if(seg == "static"){
			ind = to_string(idx);
			segR=fname+"."+ind;
			cmd = "@R0\nAM=M-1\nD=M\n@" + segR + "\nM=D\n";
		}
	}
	fprintf(asmf,"%s",cmd.c_str());
}


void printLabel(string label,string funname,int ra){
	string cmd;
	if(ra)
		cmd = "("+label+")\n";
	else
		cmd = "("+funname+"$"+label+")\n";
	fprintf(asmf,"%s\n",cmd.c_str());
}

void printGoto(string label,string funname,int ra){
	string cmd;
	if(ra)
		cmd = "@"+label+"\nD;JMP\n";
	else
		cmd = "@"+funname+"$"+label+"\nD;JMP\n";

	fprintf(asmf,"%s\n",cmd.c_str());
}

void printIf(string label,string funname,int ra){
	string cmd;
	if(ra)
		cmd = "@R0\nAM=M-1\nD=M\n@"+label+"\nD;JNE\n";
	else
		cmd = "@R0\nAM=M-1\nD=M\n@"+funname+"$"+label+"\nD;JNE\n";

	fprintf(asmf,"%s\n",cmd.c_str());	
}

void printCall(string func,int args){
	string cmd = "@RET"+func+"\nD=A\n@R0\nA=M\nM=D\n@R0\nM=M+1\n";
	string n = to_string(args);
	fprintf(asmf,"%s\n",cmd.c_str());	
	pushpopPrint("C_PUSH","local",0);
	pushpopPrint("C_PUSH","argument",0);
	pushpopPrint("C_PUSH","this",0);
	pushpopPrint("C_PUSH","that",0);
	cmd = "@R0\nD=A\n@"+n+"\nD=D-A\n@5\nD=D-A\n@R2\nM=D\n@R0\nD=A\n@R1\nM=D";
	printGoto(func,func,1);
	funcgl = func;
	printLabel("RET"+func,func,1);
}

void printinit(){
	string cmd = "@256\nD=A\n@R0\nM=D\n";
	funcgl="Sys.init";
	fprintf(asmf,"%s\n",cmd.c_str());	
	printCall("Sys.init",0);
}


void printReturn(){
	string cmd = "@R1\nD=A\n@FRAME\nM=D\nA=M\nD=M\n@5\nD=D-A\n@RET"+funcgl+"\nM=D\n";
	fprintf(asmf,"%s\n",cmd.c_str());
	cmd = "@R0\nAM=M-1\nD=M\n@R2\nA=M\nM=D\n";
	fprintf(asmf,"%s\n",cmd.c_str());
	cmd = "@R2\nD=A+1\n@R0\nM=D\n@FRAME\nA=M\nD=A-1\n@R13\nAM=D\nD=M\n@R3\nM=D\n@R13\nAM=M-1\nD=M\n@R4\nM=D\n@R13\nAM=M-1\nD=M\n@R2\nM=D\n@R13\nAM=M-1\nD=M\n@R1\nM=D\n@RET"+funcgl+"\nD;JMP\n";
	fprintf(asmf,"%s\n",cmd.c_str());
}

void printFunction(string func,int locals){
	string cmd = "("+func+")\n";
	fprintf(asmf,"%s\n",cmd.c_str());
	int i;
	for(i=0;i<locals;i++){
		pushpopPrint("C_PUSH","constant",0);
	}
}

void arithPrint(string command){
	string cmd;
	string c = to_string(k);
	if(command == "add"){
		cmd = "@R0\nM=M-1\nA=M\nD=M\n@R0\nM=M-1\nA=M\nM=D+M\n@R0\nM=M+1";
	}
	else if(command == "sub"){
		cmd = "@R0\nM=M-1\nA=M\nD=M\n@R0\nM=M-1\nA=M\nM=M-D\n@R0\nM=M+1";
	}
	else if(command == "neg"){
		cmd = "@R0\nM=M-1\nA=M\nM=-M\n@R0\nM=M+1";
	}
	else if(command == "eq"){
		cmd = "@R0\nM=M-1\nA=M\nD=M\n@R0\nM=M-1\nA=M\nD=M-D\n@TRUE"+c+"\nD;JEQ\nD=0\n@S"+c+"\nD;JMP\n(TRUE"+c+")\nD=-1\n(S"+c+")\n@R0\nA=M\nM=D\n@R0\nM=M+1\n";
		k++;
	}
	else if(command == "gt"){
		cmd = "@R0\nM=M-1\nA=M\nD=M\n@R0\nM=M-1\nA=M\nD=M-D\n@TRUE"+c+"\nD;JGT\nD=0\n@S"+c+"\nD;JMP\n(TRUE"+c+")\nD=-1\n(S"+c+")\n@R0\nA=M\nM=D\n@R0\nM=M+1\n";
		k++;
	}
	else if(command == "lt"){
		cmd = "@R0\nM=M-1\nA=M\nD=M\n@R0\nM=M-1\nA=M\nD=M-D\n@TRUE"+c+"\nD;JLT\nD=0\n@S"+c+"\nD;JMP\n(TRUE"+c+")\nD=-1\n(S"+c+")\n@R0\nA=M\nM=D\n@R0\nM=M+1\n";
		k++;
	}
	else if(command == "and"){
		cmd = "@R0\nM=M-1\nA=M\nD=M\n@R0\nM=M-1\nA=M\nM=D&M\n@R0\nM=M+1\n";
	}
	else if(command == "or"){
		cmd = "@R0\nM=M-1\nA=M\nD=M\n@R0\nM=M-1\nA=M\nM=D|M\n@R0\nM=M+1\n";
	}
	else if(command == "not"){
		cmd = "@R0\nM=M-1\nA=M\nM=!M\n@R0\nM=M+1\n";
	}
	fprintf(asmf,"%s\n",cmd.c_str());
}
