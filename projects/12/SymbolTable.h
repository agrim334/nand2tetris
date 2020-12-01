#include<unordered_map>

struct info{
	string vtype;
	string vkind;
	int runno;
};

struct node{
	struct node* next;
	struct node* prev;
	unordered_map<string, struct info> sym_tab;
	string name;
};

struct node* head;
struct node* tail;

struct node* STExists(string STname){
	struct node* temp;
	temp = head;
	while(temp){
		if(temp -> name == STname)
			return temp;
		temp = temp -> next;
	}
	return 0;
}

string kindof(string classST,string STname,string vname){
	struct node* temp = STExists(STname);
	string kind = "";

	if(!temp){
		temp = STExists(classST);
		if(!temp)
			return kind;
	}
	for(auto i = (temp->sym_tab).begin(); i!= (temp->sym_tab).end();i++){
		if(i->first == vname){
			struct info t2 = i -> second;
			return t2.vkind;
		}
	}
	return kind;		
}

string typeoff(string classST,string STname,string vname){
	struct node* temp = STExists(STname);
	string type = "";

	if(!temp){
		temp = STExists(classST);
		if(!temp)
			return type;
	}
	for(auto i = (temp->sym_tab).begin(); i!= (temp->sym_tab).end();i++){
		if(i->first == vname){
			struct info t2 = i -> second;
			return t2.vtype;
		}
	}
	return type;
}

int indexof(string classST,string STname,string vname){
	struct node* temp = STExists(STname);

	if(!temp){
		temp = STExists(classST);
		if(!temp)
			return -1;
	}

	for(auto i = (temp->sym_tab).begin(); i!= (temp->sym_tab).end();i++){
		if(i->first == vname){
			struct info t2 = i -> second;
			return t2.runno;
		}
	}
	return -1;

}
void dispTable(){
	struct node* temp;
	temp = head;
	int i;
	string vnc,vtc,vkc;
	int r;
	struct info t2;

	while(temp){
		cout << "Table name   " << temp -> name << "\n";
		cout << "Name | " << "Type |" << "Kind |" << "#\n"; 
		for(auto i = (temp->sym_tab).begin(); i!= (temp->sym_tab).end();i++){
			vnc = i->first;
			t2 = i -> second;
			r = t2.runno;
			vtc = t2.vtype;
			vkc = t2.vkind;
			cout <<  vnc << " | " << vtc << " | " << vkc << " | " << r << "\n";
		}
		temp = temp -> next;
	}
}

struct node* createST(string STname){
	struct node* temp = STExists(STname);
	if(!temp){
		if(!head){
			head = new struct node;
			head -> name = STname;
			tail = head;
			return head;
		}
		else{
			temp = new struct node;
			temp -> name = STname;
			tail -> next = temp;
			temp -> prev = tail;
			tail = temp;
			return temp;
		}
	}
	return temp;
}

void addEntry(string STname, string name,string vtype, string vkind,int runno){
	struct node* temp = createST(STname);
	struct info* ob = new struct info;
	ob->vtype = vtype;
	ob->vkind = vkind;
	ob->runno = runno;
	(temp->sym_tab)[name] = *ob;
}

bool contains(string STname,string symb,string vtype,string vkind,int runno){
	struct node* temp = STExists(STname);
	if(!temp)
		return false;
	int i;
	string vnc,vtc,vkc;
	int r;
	struct info t2;
	for(auto i = (temp->sym_tab).begin(); i!= (temp->sym_tab).end();i++){
		vnc = i->first;
		t2 = i -> second;
		r = t2.runno;
		vtc = t2.vtype;
		vkc = t2.vkind;

		if(symb.compare(vnc) == 0 && vkind.compare(vkc) == 0 && vtype.compare(vtc) == 0 && runno == r)
			return true;
	}
	return false;
}

