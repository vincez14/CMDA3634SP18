#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"

int main (int argc, char **argv) {

  //seed value for the randomizer 
  double seed = clock(); //this will make your program run differently everytime
  //double seed = 0; //uncomment this and your program will behave the same everytime it's run

  srand(seed);

  //declare storage for an ElGamal cryptosytem
  unsigned int p, g, h, x;

  //begin with getting user's input
  unsigned int n;

  printf("Enter a number of bits: "); fflush(stdout);
  char status = scanf("%u",&n);

  //make sure the input makes sense
  if ((n<9)||(n>31)) {//Updated bounds. 2 is no good, 31 is actually ok
    printf("Unsupported bit size.\n");
    return 0;   
  }
  printf("\n");

  //setup an ElGamal cryptosystem
  setupElGamal(n,&p,&g,&h,&x);


  printf("Writing to file.\n");
  printf("\n");

  /* Q1 Complete this function and write the public key data to the file public_key.txt */
 
  FILE * pkfile;

  pkfile = fopen("public_key.txt", "w");  

  // write each value (n, p, g, and h) to the public_key.txt file
  fprintf(pkfile, "%d\n", n);
  fprintf(pkfile, "%d\n", p);
  fprintf(pkfile, "%d\n", g);
  fprintf(pkfile, "%d\n", h);

  fclose(pkfile);

  printf("n = %d\n", n);
  printf("p = %d\n", p);
  printf("g = %d\n", g);
  printf("h = %d\n", h);
  printf("\n");

  printf("Setup successful.\n");

  return 0;
}
