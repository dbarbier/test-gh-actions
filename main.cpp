#include <iostream>
#include <HYPRE_config.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
  MPI_Init(&argc, &argv);
#ifndef HYPRE_BIGINT
# error "HYPRE_BIGINT not defined"
#endif
  MPI_Finalize();
}
