#!/bin/bash
# A batch job on M# -- LK, 2023-07-05
#SBATCH -A nadolsky_globalqcdanalysis_0001

#SBATCH -D /users/lkotz/mp4test/Fantomas4xFitter/examples/Fantomas/add_CP/fit3_Cgonly

#SBATCH -J fit3_Cgonly    # job name to display in squeue
#SBATCH -o fit3_Cgonly_%j.out
#SBATCH -e fit3_Cgonly_%j.out

#SBATCH -p standard-s -N1 -c18
#SBATCH -t 600
#SBATCH --mem=25G   #use all available memory

#SBATCH --mail-user=lkotz@smu.edu
#SBATCH --mail-type=ALL,TIME_LIMIT_80

if [ -f lock ]; then
    echo "fit3_Cgonly job has already been submitted. exiting."
    exit 1
fi
date > lock

nice ./xfitter

rm -f lock
