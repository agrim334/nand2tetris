#include"CodeWriter.h"

string commandType(char ar[],int* ptr){
	int i = *ptr;
	string s = "";
	while(ar[i]!='\n'&&ar[i]!='\0'&&ar[i]!=' '&&ar[i]!='\t'&&ar[i]!='\r'){
		s.push_back(ar[i]);
		i++;
	}
	string vals[9] = {"add","sub","neg","eq","gt","lt","and","or","not"};
	for(i=0;i<9;i++){
		if(s == vals[i])
			return "C_ARITHMETIC";
	}
	if(s == "push")
		return "C_PUSH";

	else if(s == "pop")
		return "C_POP";

	else if(s == "goto")
		return "C_GOTO";

	else if(s == "label")
		return "C_LABEL";

	else if(s == "if-goto")
		return "C_IF";

	else if(s == "function")
		return "C_FUNCTION";

	else if(s == "call")
		return "C_CALL";

	else if(s == "return")
		return "C_RETURN";

	return "bad";
}

bool hasMoreCommands(){
	return !feof(vmf)?true:false;
}
void advance(){
	fgets(curcom,255,vmf);
}

int arg2(char ar[],int* ptr){
	int i = *ptr;
	int x = 0;
	while(ar[i]!='\n'&&ar[i]!='\0'&&ar[i]!=' '&&ar[i]!='\t'&&ar[i]!='\r'){
		x = (x*10) + ar[i] - '0';
		i++;
	}
	*ptr = i;
	return x;
}

void arg1(char ar[],int* ptr){
	string comtype = commandType(ar,ptr);
	int idx;
	string segcom = "";
	int i = *ptr;

	if(comtype == "C_ARITHMETIC" || comtype == "C_GOTO" || comtype == "C_LABEL" || comtype == "C_IF"){
		while(ar[i]!='\n'&&ar[i]!='\0'&&ar[i]!=' '&&ar[i]!='\t'&&ar[i]!='\r'){
			segcom.push_back(ar[i]);
			i++;
		}
		if(comtype == "C_ARITHMETIC")
			arithPrint(segcom);
		else if(comtype == "C_LABEL")
			printLabel(segcom,funcgl,0);
		else if(comtype == "C_GOTO")
			printGoto(segcom);
		else if(comtype == "C_IF")
			printIf(segcom);
	}
	else if(comtype == "C_PUSH" || comtype == "C_POP" || comtype == "C_FUNCTION" || comtype == "C_CALL"){
		while(ar[i]!='\n'&&ar[i]!='\0'&&ar[i]!=' '&&ar[i]!='\t'&&ar[i]!='\r'){
			i++;
		}
		i++;
		while(ar[i]!='\n'&&ar[i]!='\0'&&ar[i]!=' '&&ar[i]!='\t'&&ar[i]!='\r'){
			segcom.push_back(ar[i]);
			i++;
		}
		i++;
		*ptr = i;
		idx = arg2(ar,ptr);
		if(comtype == "C_POP" || comtype == "C_PUSH")
			pushpopPrint(comtype,segcom,idx);
		else if(comtype == "C_FUNCTION")
			printFunction(segcom,idx);
		else if(comtype == "C_CALL")
			printCall(segcom,idx);
	}
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