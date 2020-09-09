#include"Parser.h"

void readcom(string ar){
	vmf= fopen(ar.c_str(),"r");
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
	while(argv[0][i]!='.' && i < y )
		i++;

	if(argv[0][i]!='.') {
		string a2(argv[0]);
		string ar(argv[0]);
		ar += ".asm";

		if(a2.at(a2.length()-1)!='/')
			a2 += "/";
		else{
			ar.erase(y-1);
			ar += ".asm";
		}
		string temp = a2 + ar;
		string t2;
		asmf= fopen(temp.c_str(),"w+");
		int fno=0;
		if ((dir = opendir (argv[0])) != NULL) {
			while ((ent = readdir (dir)) != NULL) {
				int x = strlen(ent -> d_name);
				if(ent -> d_name[x-1] == 'm' && ent -> d_name[x-2] == 'v' && ent -> d_name[x-3] == '.'){
					fno++;
				}
			}
		}
		closedir(dir);
		string vmfil[fno];
		i = 0;
		int flag = 0,ind = -1;
		if ((dir = opendir (argv[0])) != NULL) {
			while ((ent = readdir (dir)) != NULL) {
				int x = strlen(ent -> d_name);
				if(ent -> d_name[x-1] == 'm' && ent -> d_name[x-2] == 'v' && ent -> d_name[x-3] == '.'){
					vmfil[i] = to_ster(ent -> d_name);
					if(vmfil[i] == "Sys.vm"){
						flag = 1;
						ind = i;
					}
					i++;
				}
			}
		}
		int j;
		if(flag) {
			printinit();
			fname = vmfil[ind];
			t2 = "";
			t2 = a2+vmfil[ind];
			readcom(t2.c_str());
			for(j=0;j<fno;j++){
				if(j!=ind) {
					fname = vmfil[j];
					t2 = "";
					t2 = a2 + fname;
					readcom(t2.c_str());
				}
			}
		}
		else{
			for(j=0;j<fno;j++){
				fname = vmfil[j];
				t2 = "";
				t2 = a2 + fname;
				readcom(t2.c_str());
				}
			}
		closedir(dir);
	}
	else {
		string ar(argv[0]);
		ar.erase(y-3);
		ar += ".asm";
		asmf= fopen(ar.c_str(),"w+");
		readcom(argv[0]);
	}
	
	fclose(asmf);
  	return 0;
}
