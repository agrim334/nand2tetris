#include"Parser.h"

void readcom(char ar[]){
	vmf= fopen(ar,"r");
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
	fclose(vmf);
}
string to_ster(char* ar){
	string s(ar);
	return s;
}
int main(int argc, char* argv[]){
	argv++;
	argc--;
	int i = 0;
	int y = strlen(argv[0]);
	char a2[y];
	char ar[y+5];
	while(argv[0][i]!='.' && i < y )
		i++;

	if(argv[0][i]!='.') {
		strcpy(ar,argv[0]);		
		ar[y-1]='.';
		ar[y]='a';
		ar[y+1]='s';
		ar[y+2]='m';
		ar[y+3]='\0';
		strcpy(a2,argv[0]);
		asmf= fopen(strcat(a2,ar),"w+");
		int fno=0;
		if ((dir = opendir (argv[0])) != NULL) {
			while ((ent = readdir (dir)) != NULL) {
				int x = strlen(ent -> d_name);
				strcpy(a2,argv[0]);
				if(ent -> d_name[x-1] == 'm' && ent -> d_name[x-2] == 'v' && ent -> d_name[x-3] == '.'){
					fno++;
				}
			}
		}
		closedir(dir);
		string vmfil[fno];
		i = 0;
		if ((dir = opendir (argv[0])) != NULL) {
			while ((ent = readdir (dir)) != NULL) {
				int x = strlen(ent -> d_name);
				strcpy(a2,argv[0]);
				if(ent -> d_name[x-1] == 'm' && ent -> d_name[x-2] == 'v' && ent -> d_name[x-3] == '.'){
					vmfil[i] = to_ster(ent -> d_name);
					i++;
				}
			}
		}
		int j;
		i--;
		printinit();
		readcom(strcat(a2,vmfil[i].c_str()));
		for(j=0;j<fno;j++){
			strcpy(a2,argv[0]);
			if(j!=i)
				readcom(strcat(a2,vmfil[j].c_str()));
		}
		closedir(dir);
	}
	else {
		strcpy(ar,argv[0]);
		ar[y-2]='a';
		ar[y-1]='s';
		ar[y]='m';
		ar[y+1]='\0';
		asmf= fopen(ar,"w+");
		readcom(argv[0]);
	}
	
	fclose(asmf);
  	return 0;
}
