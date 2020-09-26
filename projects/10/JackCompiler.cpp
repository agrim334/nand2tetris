#include"parser.h"

void readcom(string ar){
	jackf= fopen(ar.c_str(),"r");
	lineno = 0;
	lookahead = 0;
	lexeme = "";
	curtok = "";
//	while(1){
//		advance();
//		if(!hasMoreTokens())
//			break;
//	}
//	compileExp();
	compileStatements();
	fclose(jackf);
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
		ar += ".xml";

		if(a2.at(a2.length()-1)!='/')
			a2 += "/";
		else{
			ar.erase(y-1);
			ar += ".xml";
		}
		string temp = a2 + ar;
		string t2;
//		vmf= fopen(temp.c_str(),"w+");
		int fno=0;
		if ((dir = opendir (argv[0])) != NULL) {
			while ((ent = readdir (dir)) != NULL) {
				int x = strlen(ent -> d_name);
				if(ent -> d_name[x-5] == '.' && ent -> d_name[x-4] == 'j' && ent -> d_name[x-3] == 'a' && ent -> d_name[x-2] == 'c' && ent -> d_name[x-1] == 'k'){
					fno++;
				}
			}
		}
		closedir(dir);
		string jackfil[fno];
		i = 0;
		if ((dir = opendir (argv[0])) != NULL) {
			while ((ent = readdir (dir)) != NULL) {
				int x = strlen(ent -> d_name);
				if(ent -> d_name[x-5] == '.' && ent -> d_name[x-4] == 'j' && ent -> d_name[x-3] == 'a' && ent -> d_name[x-2] == 'c' && ent -> d_name[x-1] == 'k'){
					jackfil[i] = to_ster(ent -> d_name);
					i++;
				}
			}
		}
		int j;
		for(j=0;j<fno;j++){
			fname = jackfil[j];
			t2 = "";
			t2 = a2 + fname;
			readcom(t2.c_str());
		}
		closedir(dir);
	}
	else {
		string ar(argv[0]);
		ar.erase(y-3);
		ar += ".xml";
//		vmf= fopen(ar.c_str(),"w+");
		readcom(argv[0]);
	}
	
//	fclose(vmf);
  	return 0;
}
