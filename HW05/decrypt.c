#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"


int main (int argc, char **argv) {

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h, x;
  unsigned int Nints;

  //get the secret key from the user
  printf("Enter the secret key (0 if unknown): "); fflush(stdout);
  char stat = scanf("%u",&x);

  printf("Reading file.\n");

  /* Q3 Complete this function. Read in the public key data from public_key.txt
    and the cyphertexts from messages.txt. */

  FILE * pkfile, * msgfile;
  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));
  char line[256];

  pkfile = fopen("public_key.txt", "r");
  msgfile = fopen("message.txt", "r");
 
  // parse through the public_key file and extract the information
  n = atoi(fgets(line, sizeof(line), pkfile));
  p = atoi(fgets(line, sizeof(line), pkfile));
  g = atoi(fgets(line, sizeof(line), pkfile));
  h = atoi(fgets(line, sizeof(line), pkfile));

  // close the public_key file
  fclose(pkfile);

  // status update
  printf("Retrieving cyphertext pairs.\n");

  // parse through the message file and extract the cyphertexts
  Nints = atoi(fgets(line, sizeof(line), msgfile));

  unsigned int charsPerInt = (n-1) / 8;
  unsigned int Nchars = charsPerInt * Nints;
  unsigned int *z = (unsigned int *) malloc(Nints*sizeof(unsigned int));
  unsigned int *a = (unsigned int *) malloc(Nints*sizeof(unsigned int));

  for (int i = 0; i < Nints; i++) {
    fgets(line, sizeof(line), msgfile);
    sscanf(line, "%u%u", &z[i], &a[i]);
    printf("Z[%d]: %u, A[%d]: %u\n", i, z[i], i, a[i]);
  }

  // close the message file
  fclose(msgfile);

  // find the secret key
  if (x==0 || modExp(g,x,p)!=h) {
    printf("Finding the secret key...\n");
    double startTime = clock();
    for (unsigned int i=0;i<p-1;i++) {
      if (modExp(g,i+1,p)==h) {
        printf("Secret key found! x = %u \n", i+1);
        x=i+1;
      } 
    }
    double endTime = clock();

    double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
    double work = (double) p;
    double throughput = work/totalTime;

    printf("Searching all keys took %g seconds, throughput was %g values tested per second.\n", totalTime, throughput);
  }

  /* Q3 After finding the secret key, decrypt the message */

  ElGamalDecrypt(z, a, Nints, p, x);
  convertZToString(z, Nints, message, Nchars);

  printf("Decrypted Message = \"%s\"\n", message);

  return 0;
}
