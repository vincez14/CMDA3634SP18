#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "functions.h"
#include "functions.c"

int main (int argc, char **argv) {

	//seed value for the randomizer 
  double seed;
  
  seed = clock(); //this will make your program run differently everytime
  //seed = 0; //uncomment this and you program will behave the same everytime it's run
  
  srand48(seed);


  //begin by getting user's input
	unsigned int n;

  printf("Enter a number of bits: ");
  scanf("%u",&n);

  //make sure the input makes sense
  if ((n<2)||(n>30)) {
  	printf("Unsupported bit size.\n");
		return 0;  	
  }

  unsigned int p;

  /* Q2.2: Use isProbablyPrime and randomXbitInt to find a random n-bit prime number */

  // store the random n-bit int in variable p
  p = randXbitInt(n);
  
  // while the random int is not prime, try again
  while (isProbablyPrime(p) == 0) {
    p = randXbitInt(n);
  } // end while loop

  printf("p = %u is probably prime.\n", p);

  /* Q3.2: Use isProbablyPrime and randomXbitInt to find a new random n-bit prime number 
     which satisfies p=2*q+1 where q is also prime */
  unsigned int q;

  // initialize q as a random n-bit int and p as an arbitrary integer
  q = randXbitInt(n-1);
  p = 4;

  // while not prime, keep trying new rand values
  while (isProbablyPrime(p) == 0) {
    q = randXbitInt(n-1);
    while (isProbablyPrime(q) == 0) {
      q = randXbitInt(n-1);
    } // end while
    p = 2*q + 1;
  } // end while

	printf("p = %u is probably prime and equals 2*q + 1. q= %u and is also probably prime.\n", p, q);  

	/* Q3.3: use the fact that p=2*q+1 to quickly find a generator */
	unsigned int g = findGenerator(p);

	printf("g = %u is a generator of Z_%u \n", g, p);  

  return 0;
}
