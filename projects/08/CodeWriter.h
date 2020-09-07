#include<iostream>
#include<string.h>
#include<unordered_map>
using namespace std;
char curcom[255];
FILE* vmf;
FILE* asmf;
string fname;
int k = 0;

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
