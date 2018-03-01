#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"

// -----------------------------------------------------------------
//compute a*b mod p safely
unsigned int modProd(unsigned int a, unsigned int b, unsigned int p) {
  /* Q1.2: Complete this function */

  unsigned int prod = 0;
  a = a % p;
  while (b > 0) {
    // add 'a' to the prod when b is odd
    if (b % 2 == 1) {
      prod = (prod + a) % p;
    }

    // multiply 'a' with 2
    a = (a * 2) % p;

    // divide b by 2
    b /= 2;
  } // end while loop
  
  // return the answer
  return prod % p;
} // end modProd


// -----------------------------------------------------------------
//compute a^b mod p safely
unsigned int modExp(unsigned int a, unsigned int b, unsigned int p) {
  /* Q1.3: Complete this function */
  
  unsigned int result = 1;
  
  // change the value of 'a'
  a = a % p;

  while (b > 0)
  {

    // if b is odd, then multiply a by result
    if (b & 1)
    {
      result = (result*a) % p;
    }

    // b should be even
    b = b >> 1;
    a = (a*a) % p; 
  } // end while

  return result;
} // end modExp


// -----------------------------------------------------------------
//returns either 0 or 1 randomly
unsigned int randomBit() {
  return rand()%2;
}

// -----------------------------------------------------------------
//returns a random integer which is between 2^{n-1} and 2^{n}
unsigned int randXbitInt(unsigned int n) {
  unsigned int r = 1;
  for (unsigned int i=0; i<n-1; i++) {
    r = r*2 + randomBit();
  }
  return r;
}


// -----------------------------------------------------------------
//tests for primality and return 1 if N is probably prime and 0 if N is composite
unsigned int isProbablyPrime(unsigned int N) {

  if (N%2==2) return 0; //not interested in even numbers (including 2)

  unsigned int NsmallPrimes = 168;
  unsigned int smallPrimeList[168] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 
                                37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 
                                79, 83, 89, 97, 101, 103, 107, 109, 113, 
                                127, 131, 137, 139, 149, 151, 157, 163, 
                                167, 173, 179, 181, 191, 193, 197, 199, 
                                211, 223, 227, 229, 233, 239, 241, 251, 
                                257, 263, 269, 271, 277, 281, 283, 293, 
                                307, 311, 313, 317, 331, 337, 347, 349, 
                                353, 359, 367, 373, 379, 383, 389, 397, 
                                401, 409, 419, 421, 431, 433, 439, 443, 
                                449, 457, 461, 463, 467, 479, 487, 491, 
                                499, 503, 509, 521, 523, 541, 547, 557, 
                                563, 569, 571, 577, 587, 593, 599, 601, 
                                607, 613, 617, 619, 631, 641, 643, 647, 
                                653, 659, 661, 673, 677, 683, 691, 701, 
                                709, 719, 727, 733, 739, 743, 751, 757, 
                                761, 769, 773, 787, 797, 809, 811, 821, 
                                823, 827, 829, 839, 853, 857, 859, 863, 
                                877, 881, 883, 887, 907, 911, 919, 929, 
                                937, 941, 947, 953, 967, 971, 977, 983, 
                                991, 997};

  //before using a probablistic primality check, check directly using the small primes list
  for (unsigned int n=1;n<NsmallPrimes;n++) {
    if (N==smallPrimeList[n])   return 1; //true
    if (N%smallPrimeList[n]==0) return 0; //false
  }

  //if we're testing a large number switch to Miller-Rabin primality test
  /* Q2.1: Complete this part of the isProbablyPrime function using the Miller-Rabin pseudo-code */
  unsigned int r,d;

  // initialize r and d with the appropriate values
  r = 1;
  d = (N-1)/2;

  // Find r and d such that N-1 = (2^r)*d where d is odd
  while(d%2 != 0) {
    d /= 2;
    r++;
  } // end while loop

  // Miller Rabin Test for all nums in small Prime List
  for (unsigned int n=0;n<NsmallPrimes;n++) {
    
    // storage variable for modExp
    unsigned int x;
    x = modExp(smallPrimeList[n], d, N);

    // if the value of x returns 1 or N-1, continue
    if (x == 1 || x == N-1) {
      continue;
    }
    
    // Check for primality
    for (int i = 1; i < r; i++) {
      x = modProd(x, x, N);

      if (x == 1) {
        return 0; // false
      }
      if (x == N-1) {
        continue;
      }
      return 0; // false
    } // end for loop

    return 1; // true
  } // end for loop

  return 1; //true
} // end isProbablyPrime()


// -----------------------------------------------------------------
//Finds a generator of Z_p using the assumption that p=2*q+1
unsigned int findGenerator(unsigned int p) {
  /* Q3.3: complete this function and use the fact that p=2*q+1 to quickly find a generator */
  
  // Use algebra to define q
  unsigned int q = (p-1)/2; 
  
  // loop through the possible generator values
  for (int i = 2; i < p-1; i++) {
    
    // if the given number, i, does not mod to 1 early then check last condition
    if ( (modExp(i,2,p) != 1) && (modExp(i,q,p) != 1) ) {
      
      // return the generator if it satisfies all conditions
      if(modExp(i,p-1,p) == 1) {
        return i;
      } // end if

    } // end if

  } // end for

} // end findGenerator()
