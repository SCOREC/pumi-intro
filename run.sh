#!/bin/bash -e
#SBATCH --job-name=pumiIntro
#SBATCH --partition=debug
#SBATCH -t 00:10:00

exe=$1;
p=$2; shift
args=("$@")
srun -n $p $exe ${args[@]}
