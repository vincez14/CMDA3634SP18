#include <stdio.h>

void add(a,b,c);

int main(){

	int a,b = 8;
	int c = 8;
	add(a,b,c);
	
	printf("%d",c);

}

void add(a,b,c){

	c = b+a;
	b = 0;

}
