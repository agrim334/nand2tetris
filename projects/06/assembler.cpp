#include"parser.h"

char curcom[100];

int hasMoreCommands(FILE* fp){
	return !feof(fp)?true:false;
}
void advance(FILE** fp){
	fgets(curcom,100,*fp);
}
string commandType(char ar[],int* ptr){
	if(ar[*ptr] == '@')
		return "A_COMMAND";
	else if(ar[*ptr] == '(')
		return "L_COMMAND";
	else {
		switch(ar[*ptr]){
			case '0':
			case '1':
			case 'D':
			case 'A':
			case 'M':
			case '-':
			case '!':
				return "C_COMMAND";
		}
	}
	return "bad";
}

int main(int argc, char* argv[]){
	argv++;
	argc--;
	int i = 0;

	FILE* asmf= fopen(argv[0],"r");
	int l = strlen(argv[0]);
	char ar[l+2];
	while(argv[0][i]!='.'){
		ar[i]=argv[0][i];
		i++;
	}
	ar[i]='.';
	ar[i+1]='h';
	ar[i+2]='a';
	ar[i+3]='c';
	ar[i+4]='k';
	ar[i+5]='\0';
	FILE* hackf= fopen(ar,"w+");
	int ptr=0;
	int x = 0;
	while(1){
		ptr=0;
		advance(&asmf);
		if(!hasMoreCommands(asmf))
			break;
		whitespace(curcom,&ptr);
		x = 0;
		while(curcom[x]!='\n')
			x++;
		if(ptr < x) {
			if(curcom[ptr]=='/' && ptr+1 < x && curcom[ptr+1]=='/')
				;
			else if(ptr < x && curcom[ptr] != '\0' && curcom[ptr] != '\n' && curcom[ptr] != ' ' && curcom[ptr] != '\t'){
				string ctype = commandType(curcom,&ptr);
				if(ctype == "L_COMMAND")
					Linstruct(curcom,&ptr);
				else
					romaddr++;
			}
		}
	}
	fseek(asmf,0,SEEK_SET);
	while(1){
		ptr=0;
		advance(&asmf);
		if(!hasMoreCommands(asmf))
			break;
		whitespace(curcom,&ptr);
		x = 0;
		while(curcom[x]!='\n')
			x++;
		if(ptr < x) {
			if(curcom[ptr]=='/' && ptr+1 < x && curcom[ptr+1]=='/')
				comments(curcom,&ptr);

			else if(ptr < x && curcom[ptr] != '\0' && curcom[ptr] != '\n' && curcom[ptr] != ' ' && curcom[ptr] != '\t'){
				string ctype = commandType(curcom,&ptr);
				if (ctype == "A_COMMAND"){
					Ainstruct(curcom,&ptr);
					fprintf(hackf,"%s\n",instruct);
					printf("%s\n",instruct);
					for(int i=0;i<16;i++)
						instruct[i]='0';
					instruct[16]='\0';
				}

				else if(ctype == "C_COMMAND"){
					Cinstruct(curcom,&ptr);
					fprintf(hackf,"%s\n",instruct);
					printf("%s\n",instruct);
					for(int i=0;i<16;i++)
						instruct[i]='0';
					instruct[16]='\0';
				}

				else if(ctype == "L_COMMAND")
					Linstruct(curcom,&ptr);

			}
		}
	}
	fclose(hackf);
	fclose(asmf);
   return 0;
}