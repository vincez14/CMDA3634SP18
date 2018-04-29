#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"

int main (int argc, char **argv) {

	//seed value for the randomizer 
  //double seed = clock(); //this will make your program run differently everytime
  double seed = 0; //uncomment this and your program will behave the same everytime it's run

  srand(seed);

  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));

  printf("Enter a message to encrypt: ");
  int stat = scanf (" %[^\n]%*c", message); //reads in a full line from terminal, including spaces

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h;

  printf("Reading file.\n");

  /* Q2 Complete this function. Read in the public key data from public_key.txt,
    convert the string to elements of Z_p, encrypt them, and write the cyphertexts to 
    message.txt */
  
  FILE * pkfile;
  char line[256];

  // open the file to be read
  pkfile = fopen("public_key.txt", "r");

  // parse through the file one line at a time
  n = atoi(fgets(line, sizeof(line), pkfile));
  p = atoi(fgets(line, sizeof(line), pkfile));
  g = atoi(fgets(line, sizeof(line), pkfile));
  h = atoi(fgets(line, sizeof(line), pkfile));  

  // close the file
  fclose(pkfile);

  // convert the input string to elements of Z_p
  unsigned int charsPerInt = (n-1) / 8;  
  padString(message, charsPerInt);

  unsigned int Nchars = strlen(message);
  unsigned int Nints = strlen(message) / charsPerInt;
  unsigned int *z = (unsigned int *) malloc(Nints*sizeof(unsigned int));
  unsigned int *a = (unsigned int *) malloc(Nints*sizeof(unsigned int));

  convertStringToZ(message, Nchars, z, Nints);

  // encrypt the message
  ElGamalEncrypt(z, a, Nints, p, g, h);

  // write the cyphertexts to message.txt
  FILE * msgfile = fopen("message.txt", "w");  

  int i;

  fprintf(msgfile, "%u\n", Nints);

  for (i = 0; i < Nints; i++) {
    fprintf(msgfile, "%u %u\n", z[i], a[i]);
  }

  // close the message file
  fclose(msgfile);

  printf("Encryption successful.\n");

  return 0;
}
