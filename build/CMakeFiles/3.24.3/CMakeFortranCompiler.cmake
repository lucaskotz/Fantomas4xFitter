set(CMAKE_Fortran_COMPILER "/usr/bin/gfortran")
set(CMAKE_Fortran_COMPILER_ARG1 "")
set(CMAKE_Fortran_COMPILER_ID "GNU")
set(CMAKE_Fortran_COMPILER_VERSION "11.4.0")
set(CMAKE_Fortran_COMPILER_WRAPPER "")
set(CMAKE_Fortran_PLATFORM_ID "")
set(CMAKE_Fortran_SIMULATE_ID "")
set(CMAKE_Fortran_COMPILER_FRONTEND_VARIANT "")
set(CMAKE_Fortran_SIMULATE_VERSION "")




set(CMAKE_AR "/usr/bin/ar")
set(CMAKE_Fortran_COMPILER_AR "/usr/bin/gcc-ar-11")
set(CMAKE_RANLIB "/usr/bin/ranlib")
set(CMAKE_Fortran_COMPILER_RANLIB "/usr/bin/gcc-ranlib-11")
set(CMAKE_COMPILER_IS_GNUG77 1)
set(CMAKE_Fortran_COMPILER_LOADED 1)
set(CMAKE_Fortran_COMPILER_WORKS TRUE)
set(CMAKE_Fortran_ABI_COMPILED TRUE)

set(CMAKE_Fortran_COMPILER_ENV_VAR "FC")

set(CMAKE_Fortran_COMPILER_SUPPORTS_F90 1)

set(CMAKE_Fortran_COMPILER_ID_RUN 1)
set(CMAKE_Fortran_SOURCE_FILE_EXTENSIONS f;F;fpp;FPP;f77;F77;f90;F90;for;For;FOR;f95;F95)
set(CMAKE_Fortran_IGNORE_EXTENSIONS h;H;o;O;obj;OBJ;def;DEF;rc;RC)
set(CMAKE_Fortran_LINKER_PREFERENCE 20)
if(UNIX)
  set(CMAKE_Fortran_OUTPUT_EXTENSION .o)
else()
  set(CMAKE_Fortran_OUTPUT_EXTENSION .obj)
endif()

# Save compiler ABI information.
set(CMAKE_Fortran_SIZEOF_DATA_PTR "8")
set(CMAKE_Fortran_COMPILER_ABI "")
set(CMAKE_Fortran_LIBRARY_ARCHITECTURE "x86_64-linux-gnu")

if(CMAKE_Fortran_SIZEOF_DATA_PTR AND NOT CMAKE_SIZEOF_VOID_P)
  set(CMAKE_SIZEOF_VOID_P "${CMAKE_Fortran_SIZEOF_DATA_PTR}")
endif()

if(CMAKE_Fortran_COMPILER_ABI)
  set(CMAKE_INTERNAL_PLATFORM_ABI "${CMAKE_Fortran_COMPILER_ABI}")
endif()

if(CMAKE_Fortran_LIBRARY_ARCHITECTURE)
  set(CMAKE_LIBRARY_ARCHITECTURE "x86_64-linux-gnu")
endif()





set(CMAKE_Fortran_IMPLICIT_INCLUDE_DIRECTORIES "/usr/lib/gcc/x86_64-linux-gnu/11/finclude;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/ghostscript-10.0.0-gq725g3xcgv5jyzlzkiq7ekprb654jvr/include;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/emacs-28.2-s37ufyttux53hfjxblyhka7elugwincc/include;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/root-6.26.06-wwe4ye5kg4r7nbrda4s6twna7vgbfsfb/include;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/zlib-1.2.13-u7kx7ln2tsm4sl4hvkfvseyu5mun42nf/include;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/yaml-cpp-0.7.0-d4xn3fpzt4acpqbsxh36f2lb56dzcv2c/include;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/openblas-0.3.21-s5husbksww3kl5y6tbbmodlkp2zbfzg4/include;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/netlib-lapack-3.10.1-uulcyxicqtnnqhdm7l4b5vzix2cktesm/include;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/libpng-1.6.37-2zu2qe3qhja36qygbwmdp6lqkz3v5weo/include;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/boost-1.80.0-l5cj6jush6plt566wflcrvpov4lfr2eb/include;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/gsl-2.7.1-oyt4rtps6akmwkeqqdnr7cku27ncfkbh/include;/usr/lib/gcc/x86_64-linux-gnu/11/include;/usr/local/include;/usr/include/x86_64-linux-gnu;/usr/include")
set(CMAKE_Fortran_IMPLICIT_LINK_LIBRARIES "gfortran;m;gcc_s;gcc;quadmath;m;gcc_s;gcc;c;gcc_s;gcc")
set(CMAKE_Fortran_IMPLICIT_LINK_DIRECTORIES "/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/ghostscript-10.0.0-gq725g3xcgv5jyzlzkiq7ekprb654jvr/lib;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/emacs-28.2-s37ufyttux53hfjxblyhka7elugwincc/lib;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/root-6.26.06-wwe4ye5kg4r7nbrda4s6twna7vgbfsfb/lib;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/zlib-1.2.13-u7kx7ln2tsm4sl4hvkfvseyu5mun42nf/lib;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/yaml-cpp-0.7.0-d4xn3fpzt4acpqbsxh36f2lb56dzcv2c/lib;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/openblas-0.3.21-s5husbksww3kl5y6tbbmodlkp2zbfzg4/lib;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/netlib-lapack-3.10.1-uulcyxicqtnnqhdm7l4b5vzix2cktesm/lib;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/libpng-1.6.37-2zu2qe3qhja36qygbwmdp6lqkz3v5weo/lib;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/boost-1.80.0-l5cj6jush6plt566wflcrvpov4lfr2eb/lib;/hpc/m3/spack/opt/spack/linux-ubuntu22.04-zen3/gcc-11.2.0/gsl-2.7.1-oyt4rtps6akmwkeqqdnr7cku27ncfkbh/lib;/usr/lib/gcc/x86_64-linux-gnu/11;/usr/lib/x86_64-linux-gnu;/usr/lib;/lib/x86_64-linux-gnu;/lib")
set(CMAKE_Fortran_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES "")
