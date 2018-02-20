#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isPrime(unsigned int num);

//main function
void main() {

  unsigned int num;

  // BONUS: The variable num is an unsigned int.
  //        It can store up to 2^32 bits of information.
  //        If the provided number is larger than 2^32
  //        then it will cause problems for our program.
  printf("Enter a number: ");
  scanf("%d", &num);

  if (isPrime(num) == 0) {
    printf("%d is not prime.\n", num);
  } else {
    printf("%d is prime.\n", num);
  }

}

//helper function: isPrime
int isPrime(unsigned int num) {

  if (num <= 1) {
    return 0; //zero and one are not prime
  }

  unsigned int i;

  for (i = 2; i*i <= num; i++) {
    if (num % i == 0) {
      return 0;
    }
  }

  return 1;

}
