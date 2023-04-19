#!/bin/bash
#SBATCH --nodes=1
#SBATCH --time=0-12:00:00
#SBATCH --cluster=smp
#SBATCH --partition=smp
#SBATCH --mail-user=prb50@pitt.edu
#SBATCH --mail-type=ALL

python sweeper.py mutSize mutSize 0.01 0.5 0.01 100 100 
