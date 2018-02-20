#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//'z' is the greatest common denominator
int z(int a, int b);

//main function
void main() {

  int a, b;

  printf("Enter the first number: ");
  scanf("%d", &a); //store the first number as 'a'

  printf("Enter the second number: ");
  scanf("%d", &b); //store the second number as 'b' 

  //print the output
  printf("The greatest common divisor of %d and %d is %d.\n", a, b, z(a, b));

}

//helper function: gcd finder
int z(int a, int b) {
  
  // BONUS: When using recursion, each recursive call
  //        adds another item to a stack. In the case
  //        where we use very large numbers, our recursive
  //        calls could eventually cause a stack overflow error. 
  if (b == 0) { //base case
    return a;
  }
  else { //recursive call
    return z(b, a%b);
  } 

}
