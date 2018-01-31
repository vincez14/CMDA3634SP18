#include <stdio.h>
#include <stdlib.h>

int add(int a, int b); // declare the method 'add' before the main function

int main(int argc, char* argv[]){

	int a = 4;
	int b = 6;
	int c = add(a,b);

	printf("The sum is %d\n", c);

}

// helper function for the main method
int add(int a, int b){

	return a+b;

}
