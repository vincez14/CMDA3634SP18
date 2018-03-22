#! /bin/bash

#PBS -l walltime=00:05:00
#PBS -l nodes=1:ppn=28
#PBS -W group_list=newriver
#PBS -q dev_q
#PBS -A CMDA3634SP18
#PBS -j oe

cd $PBS_O_WORKDIR

module purge
module load make

make

./main 1
./main 2
./main 4
./main 8
./main 12
./main 16
./main 20
./main 24
./main 28
