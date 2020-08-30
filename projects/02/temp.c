#include<stdio.h>

int main(){
	for(int i=1;i<16;i++){
		printf("FullAdder(a=a[%d],b=0,c=c%d,sum=out[%d],carry=c%d);\n",i,i,i,i+1);
	}
	return 0;
}