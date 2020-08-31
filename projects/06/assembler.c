#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char instruct[17];
int destb[3];
int compb[7];
int jumpb[3];

int constant(char ar[],int* ptr){
	int i = 0;
	int value = 0;
	while(ar[*ptr]!='\n' && ar[*ptr] >= '0' && ar[*ptr] <= '9'){
		value=value*10+ar[*ptr]-'0';
		*ptr=*ptr+1;
	}

	return value;
}
void ST(char ar[]){
	;
}

int comp(char ar[]){
	if(ar[0] == '0'){
		compb[0]=0;
		compb[1]=1;
		compb[2]=0;
		compb[3]=1;
		compb[4]=0;
		compb[5]=1;
		compb[6]=0;
	}
	else if(ar[0] == '1'){
		compb[0]=0;
		compb[1]=1;
		compb[2]=1;
		compb[3]=1;
		compb[4]=1;
		compb[5]=1;
		compb[6]=1;
	}
	else if(ar[0] == '-' && ar[1] == '1'){
		compb[0]=0;
		compb[1]=1;
		compb[2]=1;
		compb[3]=1;
		compb[4]=0;
		compb[5]=1;
		compb[6]=0;
	}
	else if(ar[0] == '-' && ar[1] == '1'){
		compb[0]=0;
		compb[1]=1;
		compb[2]=1;
		compb[3]=1;
		compb[4]=0;
		compb[5]=1;
		compb[6]=0;
	}

}

int dest(char ar[]){
	if(ar[*ptr] == 'M' && ar[*ptr+1] != 'D'){
		destb[0]=0;
		destb[1]=0;
		destb[2]=1;
	}
	else if(ar[*ptr] == 'D'){
		destb[0]=0;
		destb[1]=1;
		destb[2]=0;
	}
	else if(ar[*ptr] == 'M' && ar[*ptr+1] == 'D'){
		destb[0]=0;
		destb[1]=1;
		destb[2]=1;
	}
	else if(ar[*ptr] == 'A' && ar[*ptr+1] == 'M' && ar[*ptr+2] == 'D'){
		destb[0]=1;
		destb[1]=1;
		destb[2]=1;
	}
	else if(ar[*ptr] == 'A' && ar[*ptr+1] == 'M'){
		destb[0]=1;
		destb[1]=0;
		destb[2]=1;
	}
	else if(ar[*ptr] == 'A' && ar[*ptr+1] == 'D'){
		destb[0]=1;
		destb[1]=1;
		destb[2]=0;
	}
	else if(ar[*ptr] == 'A'){
		destb[0]=1;
		destb[1]=0;
		destb[2]=0;
	}
}

void jump(char ar[],int* ptr){
	if(ar[*ptr]=='J'){
		if(ar[*ptr+1] == 'G' && ar[*ptr+2] == 'T'){
			jumpb[0]=0;
			jumpb[1]=0;
			jumpb[2]=1;
		}
		else if(ar[*ptr+1] == 'E' && ar[*ptr+2] == 'Q'){
			jumpb[0]=0;
			jumpb[1]=1;
			jumpb[2]=0;
		}
		else if(ar[*ptr+1] == 'G' && ar[*ptr+2] == 'E'){
			jumpb[0]=0;
			jumpb[1]=1;
			jumpb[2]=1;
		}
		else if(ar[*ptr+1] == 'L' && ar[*ptr+2] == 'T'){
			jumpb[0]=1;
			jumpb[1]=0;
			jumpb[2]=0;
		}
		else if(ar[*ptr+1] == 'N' && ar[*ptr+2] == 'E'){
			jumpb[0]=1;
			jumpb[1]=0;
			jumpb[2]=1;
		}
		else if(ar[*ptr+1] == 'L' && ar[*ptr+2] == 'E'){
			jumpb[0]=1;
			jumpb[1]=1;
			jumpb[2]=0;
		}
		else if(ar[*ptr+1] == 'M' && ar[*ptr+2] == 'P'){
			jumpb[0]=1;
			jumpb[1]=1;
			jumpb[2]=1;
		}
	}
}

void Ainstruct(char ar[],int* ptr){
	int i;
	instruct[0]='0';
	instruct[16]='\0';

	*ptr = *ptr+1;
	int value = constant(ar,ptr);
	for(i=15;i>0;i--){
		instruct[i]= (value & 1) + '0';
		value = value >> 1;
	}
}

void whitespace(char ar[],int* ptr){
	while(ar[*ptr]==' '||ar[*ptr]=='\t'||ar[*ptr]=='\n'){
		*ptr = *ptr+1;
	}
}

void comments(char ar[],int* ptr){
	while(ar[*ptr]!='\n')
		*ptr = *ptr+1;
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
	char temp[100];
	fgets(temp,100,asmf);
	int ptr=0;

	while(!feof(asmf)){
		whitespace(temp,&ptr);
		int x = strlen(temp);
		printf("%s",temp);
		if(ptr < x) {
			if(temp[ptr]=='/' && ptr+1 < x && temp[ptr+1]=='/'){
				comments(temp,&ptr);
			}
			if(ptr < x && temp[ptr]!='\0'&&temp[ptr]!='\n'){
				if(temp[ptr]=='@') {
					printf("%s\n",Ainstruct(temp,&ptr));
				}
				else if(temp[ptr]>='0' && temp[ptr]<='9')
					printf("%d\n",constant(temp,&ptr));
			}
		}
		ptr=0;
		fgets(temp,100,asmf);
	}
	fclose(hackf);
	fclose(asmf);
   return 0;
}