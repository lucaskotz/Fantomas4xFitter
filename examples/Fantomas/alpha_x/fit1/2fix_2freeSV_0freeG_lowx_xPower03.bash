#!/bin/bash
# A batch job on M# -- LK, 2023-07-05
#SBTATCH -A nadolsky_globalqcdanalysis_0001

#SBATCH -D /users/lkotz/mp4test/test/examples/Fantomas/final_examples/alpha_x_examples/2fix_2freeSV_0freeG_lowx_xPower03

#SBATCH -J 2fix_2freeSV_0freeG_lowx_xPower03    # job name to display in squeue
#SBATCH -o 2fix_2freeSV_0freeG_lowx_xPower03_%j.out
#SBATCH -e 2fix_2freeSV_0freeG_lowx_xPower03_%j.out

#SBATCH -p standard-s -N1 -c18
#SBATCH -t 600
#SBATCH --mem=25G   #use all available memory

#SBATCH --mail-user=lkotz@smu.edu
#SBATCH --mail-type=ALL,TIME_LIMIT_80

if [ -f lock ]; then
    echo "2fix_2freeSV_0freeG_lowx_xPower03 job has already been submitted. exiting."
    exit 1
fi
date > lock

nice ./xfitter

rm -f lock
