#include <iostream>
#include <mpi.h>

#include "f.hpp"

int main(int argc, char* argv[])
{
  MPI_Init(&argc, &argv);
  f();
  MPI_Finalize();
}
