#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int g(int p);

//main function
void main() {

  //'p' is a prime number
  int p;

  // BONUS: 'p' is a variable of type int, which means
  //        that it can only store 2^31 bits of information.
  //        If the provided number exceeds this storage space
  //        it could cause our program to crash.
  printf("Enter a prime number: ");
  scanf("%d", &p);  

  printf("%d is a generator of Z_%d.\n", g(p), p);
}

//helper function: find Generator 'g'
int g(int p) {

  for (int i = 2; i < p-1; i++) {
    // BONUS: Here we are using the power function.
    //        This poses a potential problem in the case
    //        where very large numbers are involved because
    //        the power function could potentially take
    //        two very large numbers and turn them into
    //        a number too large for our program to handle.
    if ( ((int)pow(i, p-1) % p) == 1 ) {
      return i;
    }
  }

}
