#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main(int argc, char* argv[]){
	argv++;
	argc--;

	fstream infile;
	infile.open(argv[0],ios::in);
	if(infile.is_open()){
		string x;
		while(getline(infile,x))
			cout << x << "\n";
	}
	infile.close();
	return 0;

}