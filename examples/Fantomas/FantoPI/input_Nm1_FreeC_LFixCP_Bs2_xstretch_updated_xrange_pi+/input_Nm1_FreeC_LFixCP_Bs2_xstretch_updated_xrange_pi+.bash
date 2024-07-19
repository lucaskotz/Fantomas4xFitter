#!/bin/bash
# A batch job on M# -- LK, 2023-07-05
#SBATCH -D /users/lkotz/hack/xfitter-2.2.0_AC_230630/m3jobs/input_Nm1_FreeC_LFixCP_Bs2_xstretch_updated_xrange_pi+

#SBATCH -J input_Nm1_FreeC_LFixCP_Bs2_xstretch_updated_xrange_pi+    # job name to display in squeue
#SBATCH -o input_Nm1_FreeC_LFixCP_Bs2_xstretch_updated_xrange_pi+_%j.out
#SBATCH -e input_Nm1_FreeC_LFixCP_Bs2_xstretch_updated_xrange_pi+_%j.out

#SBATCH -p standard-s -N1 -c18
#SBATCH --mem=25G   #use all available memory

#SBATCH --mail-user=lkotz@smu.edu
#SBATCH --mail-type=ALL,TIME_LIMIT_80

nice ./xfitter

