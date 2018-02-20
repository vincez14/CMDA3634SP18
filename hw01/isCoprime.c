#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b);

//main function
void main() {

  int a,b;

  // BONUS: Both 'a' and 'b' are variables of type int.
  //        They can store up to 2^31 bits of information.
  //        If the provided numbers are too large, then it
  //        will cause our program to crash.
  printf("Enter the first number: ");
  scanf("%d", &a);

  printf("Enter the second number: ");
  scanf("%d", &b);
  
  if (gcd(a, b) == 1) {
    printf("%d and %d are coprime.\n", a, b);
  } else {
    printf("%d and %d are not coprime.\n", a, b);
  }

}


//helper function: gcd
int gcd(int a, int b) {
  
  // BONUS: Each recursive call adds an item to the memory stack.
  //        In the case where we use very large numbers, the
  //        recursive calls have a chance of encourntering stack
  //        overflow error (if too many recursive calls are added
  //        to the stack.
  if (b == 0) { //base case
    return a;
  } 
  else { //recursive call
    return gcd(b, a%b);
  } 

}

