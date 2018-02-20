#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b);
int z(int a, int b);

//main function
void main() {

  int a,b;

  // BONUS: Both 'a' and 'b' are variables of type int.
  //        Signed ints can store up to 2^31 bits of information.
  //        If the provided number is too large to be stored
  //        it could cause our program to crash.
  printf("Enter the first number: ");
  scanf("%d", &a);

  printf("Enter the second number: ");
  scanf("%d", &b);
   
  printf("The least common multiple of %d and %d is %d.\n", a, b, z(a,b));

}

//helper function: gcd finder
int gcd(int a, int b) {

  // BONUS: When we use recursion, each recursive call is
  //        added to a stack. If very large numbers are involved
  //        our recursion has the potential to run very many times
  //        which could fill up our stack and cause stack overflow.
  if (b == 0) { //base case
    return a;
  } 
  else { //recursive call
    return gcd(b, a%b);
  }

}

//helper function: lcm finder
int z(int a, int b) {

  // BONUS: Here we are multiplying two ints, 'a' and 'b'.
  //        If we are using very large numbers, the two nums
  //        could multiply to be something too large for our
  //        program to handle, crashing our program.
  return (a*b) / gcd(a,b);

}
