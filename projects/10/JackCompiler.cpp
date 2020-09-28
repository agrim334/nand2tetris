#include"parser.h"

void readcom(string ar){
	jackf= fopen(ar.c_str(),"r");
	std::fill_n(curline, 255, 0);
	lineno = 0;
	lookahead = 0;
	lexeme = "";
	curtok = "";
	advance();
	compileClass();
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
		string ar(argv[0]);
		if(ar.at(ar.length() - 1) != '/')
			ar += '/';
		string temp,t2,t3;
		if ((dir = opendir (argv[0])) != NULL) {
			while ((ent = readdir (dir)) != NULL) {
				int x = strlen(ent -> d_name);
				if(ent -> d_name[x-5] == '.' && ent -> d_name[x-4] == 'j' && ent -> d_name[x-3] == 'a' && ent -> d_name[x-2] == 'c' && ent -> d_name[x-1] == 'k'){
					temp = to_ster(ent -> d_name);
					t2 = "";
					t3 = "";
					t2 = ar + temp;
					t3 = t2;
					t3 = t3.erase(t3.length() - 5) + ".xml";
					vmf= fopen(t3.c_str(),"w+");
					readcom(t2.c_str());
					fclose(vmf);
				}
			}
		}
	}
	else {
		string ar(argv[0]);
		ar.erase(y-5);
		ar += ".xml";
		vmf= fopen(ar.c_str(),"w+");
		readcom(argv[0]);
		fclose(vmf);
	}
	
  	return 0;
}
