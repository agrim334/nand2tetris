#include<unordered_map>

struct info{
	string vtype;
	string vkind;
	int runno;	
};
unordered_map<string, struct info> sym_tab;

void addEntry(string name,string vtype, string vkind,int runno){
	struct info* ob = new struct info;
	ob->vtype = vtype;
	ob->vkind = vkind;
	ob->runno = runno;
	sym_tab[name] = *ob;
}

bool contains(string symb,string vtype,string vkind,int runno){
	int i;
	string vnc,vtc,vkc;
	int r;
	struct info temp;
	for(auto i = sym_tab.begin(); i!= sym_tab.end();i++){
		vnc = i->first;
		temp = i -> second;
		r = temp.runno;
		vtc = temp.vtype;
		vkc = temp.vkind;
		if(symb.compare(vnc) == 0 && vkind.compare(vkc) == 0 && vtype.compare(vtc) == 0 && runno == r)
			return true;
	}
	return false;
}

