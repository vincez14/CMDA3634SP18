#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "cuda.h"
#include "functions.c"

// safely compute a*b mod p
__device__ unsigned int modProdCuda(unsigned int a, unsigned int b, unsigned int p) {

  unsigned int za = a;
  unsigned int ab = 0;

  while (b > 0) {
    if (b%2 == 1) ab = (ab + za) % p;
    za = (2 * za) % p;
    b /= 2;
  }

  return ab;
}

// safely compute a^b mod p
__device__ unsigned int modExpCuda(unsigned int a, unsigned int b, unsigned int p) {
  unsigned int z = a;
  unsigned int aExpb = 1;

  while (b > 0) {
    if (b%2 == 1) aExpb = modProdCuda(aExpb, z, p);
    z = modProdCuda(z, z, p);
    b /= 2;
  }

  return aExpb;
}

// device function
__global__ void kernelDecrypt(unsigned int p, unsigned int g, unsigned int h, unsigned int x, unsigned int *d_r) {
  int threadid = threadIdx.x; // thread number
  int blockid = blockIdx.x; // block number
  int Nblock = blockDim.x; // number of threads in a block
  
  int id = threadid + blockid * Nblock;

  // find the secret key in parallel
  if (modExpCuda(g, id, p) == h) {
    *d_r = id;
  }

} // end kernelDecrypt()

int main (int argc, char **argv) {

  /* Part 2. Start this program by first copying the contents of the main function from 
     your completed decrypt.c main function. */

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

  pkfile = fopen("bonus_public_key.txt", "r");
  msgfile = fopen("bonus_message.txt", "r");
 
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
  }

  // close the message file
  fclose(msgfile);

  // find the secret key
  if (x==0 || modExp(g,x,p)!=h) {
    printf("Finding the secret key...\n");
    double startTime = clock();

    unsigned int numProc = p - 1;
    unsigned int *d_r; // storage for the device result

    // allocate memory on the device
    cudaMalloc(&d_r, sizeof(unsigned int));

    int Nthreads = 32;
    int Nblocks = (numProc + Nthreads - 1) / Nthreads;

    // execute the kernel on the Device
    kernelDecrypt <<< Nblocks, Nthreads >>> (p, g, h, x, d_r);
    cudaDeviceSynchronize();
    
    // copy the result over to the host
    cudaMemcpy(&x, d_r, sizeof(unsigned int), cudaMemcpyDeviceToHost);
    
    // FREE THE MEMORY
    cudaFree(d_r);

    double endTime = clock();

    double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
    double work = (double) p;
    double throughput = work/totalTime;

    printf("Searching all keys took %g seconds, throughput was %g values tested per second.\n", totalTime, throughput);
  } // end finding the secret key

  /* Q3 After finding the secret key, decrypt the message */

  ElGamalDecrypt(z, a, Nints, p, x);
  convertZToString(z, Nints, message, Nchars);

  printf("Decrypted Message = \"%s\"\n", message);

  return 0;
}
