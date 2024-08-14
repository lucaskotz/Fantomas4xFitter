#!/bin/bash
# A batch job on M# -- LK, 2023-07-05
#SBATCH -D /users/lkotz/mp4test/test/examples/Fantomas/Nm1_fixedmod

#SBATCH -J Nm1_fixedmod    # job name to display in squeue
#SBATCH -o Nm1_fixedmod_%j.out
#SBATCH -e Nm1_fixedmod_%j.out

#SBATCH -p standard-s -N1 -c18
#SBATCH --mem=25G   #use all available memory

#SBATCH --mail-user=lkotz@smu.edu
#SBATCH --mail-type=ALL,TIME_LIMIT_80

nice ./xfitter

