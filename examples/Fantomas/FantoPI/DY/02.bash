#!/bin/bash
# A batch job on M# -- LK, 2023-07-05
#SBATCH -D /users/lkotz/hack/xfitter-2.2.0_AC_230630/m3jobs/02

#SBATCH -J 02    # job name to display in squeue
#SBATCH -o 02_%j.out
#SBATCH -e 02_%j.out

#SBATCH -p standard-s -N1 -c18
#SBATCH --mem=25G   #use all available memory

#SBATCH --mail-user=lkotz@smu.edu
#SBATCH --mail-type=ALL,TIME_LIMIT_80

nice ./xfitter

