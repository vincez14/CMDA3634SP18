#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {

  int rank;
  int size;

  // A. Initialize the MPI session
  MPI_Init(&argc, &argv);
  
  // B. Find the rank
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // C. Find the number(size) of MPI processes
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  //need running tallies
  long long int Ntotal;
  long long int Ncircle;

  //seed random number generator
  double seed = (double) rank; //cast rank to be a double
  srand48(seed); //set the random number seed to be the MPI process rank

  for (long long int n=0; n<1000000000;n++) {
    //generate two random numbers
    double rand1 = drand48(); //drand48 returns a number between 0 and 1
    double rand2 = drand48();
    
    double x = -1 + 2*rand1; //shift to [-1,1]
    double y = -1 + 2*rand2;

    //check if its in the circle
    if (sqrt(x*x+y*y)<=1) Ncircle++;
    Ntotal++;
  }

  // local calculation of pi
  double pi = 4.0*Ncircle/ (double) Ntotal; 
  double sum; // variable for the sum to be stored in

  // E. Perform an All Reduce function to sum the local estimates
  MPI_Allreduce(&pi,       // send buffer
                &sum,       // receive buffer
                1,          // count (num of entries)
                MPI_DOUBLE, // data type
                MPI_SUM,    // MPI operation
                MPI_COMM_WORLD);

  // F. Only Rank zero prints out the estimate for pi every 100 steps
  if(rank == 0 && Ntotal%100 == 0) {  //only when rank=0 and only every 100 steps
    // our calculated value of pi
    pi = ((double) sum/(double) Ntotal)*4.0; //divides by the number of processes

    // print the calculated value of pi
    printf("Our estimate of pi is %f \n", pi);   
  }

  // A. Initialize and finalize the MPI session
  MPI_Finalize();

  
  return 0; 
}
