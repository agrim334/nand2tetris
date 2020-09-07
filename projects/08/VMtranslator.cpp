#include"Parser.h"

int main(int argc, char* argv[]){
	argv++;
	argc--;
	int i = 0;
	vmf= fopen(argv[0],"r");
	int l = strlen(argv[0]);
	char ar[l+2];
	while(argv[0][i]!='.'){
		ar[i]=argv[0][i];
		i++;
	}
	ar[i]='.';
	ar[i+1]='a';
	ar[i+2]='s';
	ar[i+3]='m';
	ar[i+4]='\0';
	asmf= fopen(ar,"w+");
	int ptr=0;
	int x = 0;
	while(1){
		ptr=0;
		advance();
		if(!hasMoreCommands())
			break;
		whitespace(curcom,&ptr);
		x = 0;
		while(curcom[x]!='\n')
			x++;
		if(ptr < x) {
			if(curcom[ptr]=='/' && ptr+1 < x && curcom[ptr+1]=='/')
				comments(curcom,&ptr);

			else if(ptr < x && curcom[ptr] != '\0' && curcom[ptr] != '\n' && curcom[ptr] != ' ' && curcom[ptr] != '\t'){
				arg1(curcom,&ptr);
			}
		}
	}
	fclose(asmf);
	fclose(vmf);
   return 0;
}