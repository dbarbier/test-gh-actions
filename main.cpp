#include <iostream>
#include <mpi.h>

#include "f.hpp"

#ifdef __GNUC__
# ifdef SIZE_T_UNALIASED
#  warning "SIZE_T_UNALIASED is defined"
# else
#  warning "SIZE_T_UNALIASED is not defined"
# endif
#else
# ifdef SIZE_T_UNALIASED
#  pragma message("SIZE_T_UNALIASED is defined")
# else
#  pragma message("SIZE_T_UNALIASED is not defined")
# endif
#endif


int main(int argc, char* argv[])
{
  MPI_Init(&argc, &argv);
  f();
  MPI_Finalize();
}
