#include<bits/stdc++.h>
using namespace std;

unordered_map<string, int> sym_tab;
int romaddr=0;
int ramaddr=16;

void ST(){
	sym_tab.clear();
	romaddr=0;
	ramaddr=16;
	sym_tab["SP"] = 0;
	sym_tab["LCL"] = 1;
	sym_tab["ARG"] = 2;
	sym_tab["THIS"] = 3;
	sym_tab["THAT"] = 4;
	sym_tab["R0"] = 0;
	sym_tab["R1"] = 1;
	sym_tab["R2"] = 2;
	sym_tab["R3"] = 3;	
	sym_tab["R4"] = 4;
	sym_tab["R5"] = 5;
	sym_tab["R6"] = 6;
	sym_tab["R7"] = 7;
	sym_tab["R8"] = 8;
	sym_tab["R9"] = 9;
	sym_tab["R10"] = 10;
	sym_tab["R11"] = 11;
	sym_tab["R12"] = 12;
	sym_tab["R13"] = 13;
	sym_tab["R14"] = 14;
	sym_tab["R15"] = 15;
	sym_tab["SCREEN"] = 16384;
	sym_tab["KBD"] = 24576;
}

void addEntry(string symb,int addr){
	sym_tab[symb] = addr;
}

bool contains(string symb){
	if(sym_tab.find(symb) == sym_tab.end())
		return false;
	return true;
}
int GetAddress(string symb){
	if(contains(symb))
		return sym_tab[symb];
	return -1;	
}

void whitespace(char ar[],int* ptr){
	while(ar[*ptr]==' '||ar[*ptr]=='\t'||ar[*ptr]=='\n'){
		*ptr = *ptr+1;
	}
}

void comments(char ar[],int* ptr){
	while(ar[*ptr]!='\n')
		*ptr = *ptr+1;
}

