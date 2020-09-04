#include<iostream>
#include<string.h>
#include<unordered_map>
using namespace std;

unordered_map<string, int> sym_tab;
int romaddr=0;
int ramaddr=16;
char instruct[17];
char destb[4];
char jumpb[4];
char compb[8];

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
	int i;
	for(auto i = sym_tab.begin(); i!= sym_tab.end();i++){
		string x = i->first;
		if(symb.compare(x) == 0){
			return true;
		}
	}
	return false;
}
int GetAddress(string symb){
	return sym_tab[symb];
}

void whitespace(char ar[],int* ptr){
	while(ar[*ptr]==' '||ar[*ptr]=='\t'||ar[*ptr]=='\n'||ar[*ptr]=='\r'||ar[*ptr]=='\v'){
		*ptr = *ptr+1;
	}
}

void comments(char ar[],int* ptr){
	while(ar[*ptr]!='\n')
		*ptr = *ptr+1;
}

int constant(char ar[],int* ptr){
	int i = 0;
	int value = 0;
	while(ar[*ptr]!='\n' && ar[*ptr] >= '0' && ar[*ptr] <= '9'){
		value=value*10+ar[*ptr]-'0';
		*ptr=*ptr+1;
	}

	return value;
}
char* comp(char ar[],int* ptr){
	switch(ar[*ptr]){
		case '0':
			compb[0]='0';
			compb[1]='1';
			compb[2]='0';
			compb[3]='1';
			compb[4]='0';
			compb[5]='1';
			compb[6]='0';
		break;
		case '1':
			compb[0]='0';
			compb[1]='1';
			compb[2]='1';
			compb[3]='1';
			compb[4]='1';
			compb[5]='1';
			compb[6]='1';
		break;
		case '-':
			switch(ar[*ptr+1]){
				case '1':
					compb[0]='0';
					compb[1]='1';
					compb[2]='1';
					compb[3]='1';
					compb[4]='0';
					compb[5]='1';
					compb[6]='0';
				break;
				case 'D':
					compb[0]='0';
					compb[1]='0';
					compb[2]='0';
					compb[3]='1';
					compb[4]='1';
					compb[5]='1';
					compb[6]='1';
				break;

				case 'A':
					compb[0]='0';
					compb[1]='1';
					compb[2]='1';
					compb[3]='0';
					compb[4]='0';
					compb[5]='1';
					compb[6]='1';
				break;
	
				case 'M':
					compb[0]='1';
					compb[1]='1';
					compb[2]='1';
					compb[3]='0';
					compb[4]='0';
					compb[5]='1';
					compb[6]='1';
				break;
			}
		break;
		case '!':
			switch(ar[*ptr+1]){
				case 'D':
					compb[0]='0';
					compb[1]='0';
					compb[2]='0';
					compb[3]='1';
					compb[4]='1';
					compb[5]='0';
					compb[6]='1';
				break;

				case 'A':
					compb[0]='0';
					compb[1]='1';
					compb[2]='1';
					compb[3]='0';
					compb[4]='0';
					compb[5]='0';
					compb[6]='1';
				break;
	
				case 'M':
					compb[0]='1';
					compb[1]='1';
					compb[2]='1';
					compb[3]='0';
					compb[4]='0';
					compb[5]='0';
					compb[6]='1';
				break;
			}
		break;
		case 'D':
			switch(ar[*ptr+1]){
				case '-':
					switch(ar[*ptr+2]){
					case '1':
						compb[0]='0';
						compb[1]='0';
						compb[2]='0';
						compb[3]='1';
						compb[4]='1';
						compb[5]='1';
						compb[6]='0';
					break;

					case 'A':
						compb[0]='0';
						compb[1]='0';
						compb[2]='1';
						compb[3]='0';
						compb[4]='0';
						compb[5]='1';
						compb[6]='1';
					break;
					case 'M':
						compb[0]='1';
						compb[1]='0';
						compb[2]='1';
						compb[3]='0';
						compb[4]='0';
						compb[5]='1';
						compb[6]='1';
					break;
					}
				break;
				case '+':
					switch(ar[*ptr+2]){
					case '1':
						compb[0]='0';
						compb[1]='0';
						compb[2]='1';
						compb[3]='1';
						compb[4]='1';
						compb[5]='1';
						compb[6]='1';
					break;

					case 'A':
						compb[0]='0';
						compb[1]='0';
						compb[2]='0';
						compb[3]='0';
						compb[4]='0';
						compb[5]='1';
						compb[6]='0';
					break;
					case 'M':
						compb[0]='1';
						compb[1]='0';
						compb[2]='0';
						compb[3]='0';
						compb[4]='0';
						compb[5]='1';
						compb[6]='0';
					break;
					}
				break;
				case '&':
					compb[1]='0';
					compb[2]='0';
					compb[3]='0';
					compb[4]='0';
					compb[5]='0';
					compb[6]='0';
					if(ar[*ptr+2] == 'A')
						compb[0]='0';
					else
						compb[0]='1';
					break;
	
				case '|':
					compb[1]='0';
					compb[2]='1';
					compb[3]='0';
					compb[4]='1';
					compb[5]='0';
					compb[6]='1';
					if(ar[*ptr+2] == 'A')
						compb[0]='0';
					else
						compb[0]='1';
					break;
	
				default:
					compb[0]='0';
					compb[1]='0';
					compb[2]='0';
					compb[3]='1';
					compb[4]='1';
					compb[5]='0';
					compb[6]='0';				
			}
		break;
		case 'A':
			switch(ar[*ptr+1]){
				case '+':
					compb[0]='0';
					compb[1]='1';
					compb[2]='1';
					compb[3]='0';
					compb[4]='1';
					compb[5]='1';
					compb[6]='1';
				break;

				case '-':
					switch(ar[*ptr+2]){
						case '1':
							compb[0]='0';
							compb[1]='1';
							compb[2]='1';
							compb[3]='0';
							compb[4]='0';
							compb[5]='1';
							compb[6]='0';
						break;

						case 'D':
							compb[0]='0';
							compb[1]='0';
							compb[2]='0';
							compb[3]='0';
							compb[4]='1';
							compb[5]='1';
							compb[6]='1';
						break;
					}
				break;
				default:
					compb[0]='0';
					compb[1]='1';
					compb[2]='1';
					compb[3]='0';
					compb[4]='0';
					compb[5]='0';
					compb[6]='0';
			}
		break;
		case 'M':
			switch(ar[*ptr+1]){
				case '+':
					compb[0]='1';
					compb[1]='1';
					compb[2]='1';
					compb[3]='0';
					compb[4]='1';
					compb[5]='1';
					compb[6]='1';
				break;

				case '-':
					switch(ar[*ptr+2]){
						case '1':
							compb[0]='1';
							compb[1]='1';
							compb[2]='1';
							compb[3]='0';
							compb[4]='0';
							compb[5]='1';
							compb[6]='0';
						break;

						case 'D':
							compb[0]='1';
							compb[1]='0';
							compb[2]='0';
							compb[3]='0';
							compb[4]='1';
							compb[5]='1';
							compb[6]='1';
						break;
					}
				break;
				default:
					compb[0]='1';
					compb[1]='1';
					compb[2]='1';
					compb[3]='0';
					compb[4]='0';
					compb[5]='0';
					compb[6]='0';
			}
		break;
	}
	return compb;
}

char* dest(char ar[],int* ptr){
	if(ar[*ptr] == 'M' && ar[*ptr+1] != 'D'){
		destb[0]='0';
		destb[1]='0';
		destb[2]='1';
	}
	else if(ar[*ptr] == 'D'){
		destb[0]='0';
		destb[1]='1';
		destb[2]='0';
	}
	else if(ar[*ptr] == 'M' && ar[*ptr+1] == 'D'){
		destb[0]='0';
		destb[1]='1';
		destb[2]='1';
	}
	else if(ar[*ptr] == 'A' && ar[*ptr+1] == 'M' && ar[*ptr+2] == 'D'){
		destb[0]='1';
		destb[1]='1';
		destb[2]='1';
	}
	else if(ar[*ptr] == 'A' && ar[*ptr+1] == 'M'){
		destb[0]='1';
		destb[1]='0';
		destb[2]='1';
	}
	else if(ar[*ptr] == 'A' && ar[*ptr+1] == 'D'){
		destb[0]='1';
		destb[1]='1';
		destb[2]='0';
	}
	else if(ar[*ptr] == 'A'){
		destb[0]='1';
		destb[1]='0';
		destb[2]='0';
	}
	return destb;
}

char* jump(char ar[],int* ptr){
	if(ar[*ptr]=='J'){
		if(ar[*ptr+1] == 'G' && ar[*ptr+2] == 'T'){
			jumpb[0]='0';
			jumpb[1]='0';
			jumpb[2]='1';
		}
		else if(ar[*ptr+1] == 'E' && ar[*ptr+2] == 'Q'){
			jumpb[0]='0';
			jumpb[1]='1';
			jumpb[2]='0';
		}
		else if(ar[*ptr+1] == 'G' && ar[*ptr+2] == 'E'){
			jumpb[0]='0';
			jumpb[1]='1';
			jumpb[2]='1';
		}
		else if(ar[*ptr+1] == 'L' && ar[*ptr+2] == 'T'){
			jumpb[0]='1';
			jumpb[1]='0';
			jumpb[2]='0';
		}
		else if(ar[*ptr+1] == 'N' && ar[*ptr+2] == 'E'){
			jumpb[0]='1';
			jumpb[1]='0';
			jumpb[2]='1';
		}
		else if(ar[*ptr+1] == 'L' && ar[*ptr+2] == 'E'){
			jumpb[0]='1';
			jumpb[1]='1';
			jumpb[2]='0';
		}
		else if(ar[*ptr+1] == 'M' && ar[*ptr+2] == 'P'){
			jumpb[0]='1';
			jumpb[1]='1';
			jumpb[2]='1';
		}
	}
	return jumpb;
}
string symbol(char ar[],int* ptr){
	int i = *ptr;
	string s = "";
	while(ar[i]!=')'&&ar[i]!='\n'&&ar[i]!='\0'&&ar[i]!=' '&&ar[i]!='\t'){
		s.push_back(ar[i]);
		i++;
	}
	return s;
}

void Linstruct(char ar[],int* ptr){
	*ptr=*ptr+1;
	string s = symbol(ar,ptr);
	if(!contains(s))
		addEntry(s,romaddr);
}


void Ainstruct(char ar[],int* ptr){
	int i;
	instruct[0]='0';
	instruct[16]='\0';
	*ptr = *ptr+1;
	if(ar[*ptr]>='0'&& ar[*ptr]<='9') {
		int value = constant(ar,ptr);
		for(i=15;i>0;i--){
			instruct[i]= (value & 1) + '0';
			value = value >> 1;
		}
	}
	else{
		string s = symbol(ar,ptr);
		if(s.at(s.size() - 1) == '\r' || s.at(s.size() - 1) == '\n' || s.at(s.size() - 1) == ' ' || s.at(s.size() - 1) == '\t' || s.at(s.size() - 1) == '\0' || s.at(s.size() - 1) == '\v' || s.at(s.size() - 1) == ')')
			s.resize(s.size() - 1);
		
		if(!contains(s)){
			addEntry(s,ramaddr);
			ramaddr++;
		}
		int addr = GetAddress(s);
		for(i=15;i>0;i--){
			instruct[i]= (addr & 1) + '0';
			addr = addr >> 1;
		}
	}
}

void Cinstruct(char ar[],int* ptr){
	compb[7]='\0';
	jumpb[3]='\0';
	destb[3]='\0';

	int i=*ptr;
	int f1,f2;

	while(ar[i]!= '=' && ar[i]!='\n')
		i++;

	if(ar[i] == '=')
		f1 = 1;

	else
		f1 = 0;
	i=*ptr;

	while(ar[i]!= ';' && ar[i]!='\n')
		i++;
	if(ar[i] == ';')
		f2 = 1;
	else
		f2 = 0;
	if(f1 && f2){
		i=*ptr;
		dest(ar,&i);
		while(ar[i] != '=')
			i++;
		i++;

		comp(ar,&i);
		while(ar[i] != ';')
			i++;
		i++;
		jump(ar,&i);
		*ptr=*ptr+i+2;
	}
	else if(f1 && !f2){
		i=*ptr;
		dest(ar,&i);
		while(ar[i] != '=')
			i++;
		i++;

		comp(ar,&i);
		while(ar[i] != '\n')
			i++;
		i++;
		*ptr=*ptr+i;
		jumpb[0]=jumpb[1]=jumpb[2]='0';
	}
	else if(!f1 && f2){
		i=*ptr;
		comp(ar,&i);
		while(ar[i] != ';')
			i++;
		i++;
		jump(ar,&i);
		*ptr=*ptr+i+2;

		destb[0]=destb[1]=destb[2]='0';
	}
	instruct[0]=instruct[1]=instruct[2]='1';
	instruct[16]='\0';
	for(i=3;i<10;i++)
		instruct[i]=compb[i-3];

	for(;i<13;i++)
		instruct[i]=destb[i-10];

	for(;i<16;i++)
		instruct[i]=jumpb[i-13];
}