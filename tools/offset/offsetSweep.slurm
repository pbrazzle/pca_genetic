#!/bin/bash
#SBATCH --nodes=1
#SBATCH --time=0-12:00:00
#SBATCH --cluster=smp
#SBATCH --partition=smp
#SBATCH --mail-user=prb50@pitt.edu
#SBATCH --mail-type=ALL

python sweeper.py offset offset 1.0 50.0 1.0 100 100 
