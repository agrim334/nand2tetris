#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"lexer.h"
char curcom[100];

int hasMoreCommands(FILE* fp){
	return !feof(fp)?1:0;
}
void advance(FILE** fp){
	fgets(curcom,100,*fp);
}
void commandType(){
;
}
void symbol(){
;
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
	while(hasMoreCommands(asmf)){
		ptr=0;
		advance(&asmf);
		whitespace(curcom,&ptr);
		x = 0;
		while(curcom[x]!='\n')
			x++;
		printf("%s",curcom);
		if(ptr < x) {
			if(curcom[ptr]=='/' && ptr+1 < x && curcom[ptr+1]=='/'){
				comments(curcom,&ptr);
			}
			else if(ptr < x && curcom[ptr] != '\0' && curcom[ptr] != '\n' && curcom[ptr] != ' ' && curcom[ptr] != '\t'){
				if(curcom[ptr]=='@') {
					Ainstruct(curcom,&ptr);
				}
				else if (curcom[ptr]!='@'){
					Cinstruct(curcom,&ptr);
				}
				printf("%s\n",instruct);
				for(int i=0;i<16;i++)
					instruct[i]='0';
				instruct[16]='\0';

			}
		}
	}
	fclose(hackf);
	fclose(asmf);
   return 0;
}