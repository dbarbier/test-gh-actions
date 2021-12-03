#include <iostream>

#include <mpi.h>
#include <HYPRE_struct_ls.h>

#include "f.hpp"

void f()
{
    std::cout << "Hello world!\n";
    HYPRE_StructGrid grid;
    int ndim        = 2;
    int ilower[][2] = {{-3,1}, {0,1}};
    int iupper[][2] = {{-1,2}, {2,4}};

    /* Create the grid object */
    HYPRE_StructGridCreate(MPI_COMM_WORLD, ndim, &grid);

    /* Set grid extents for the first box */
    HYPRE_StructGridSetExtents(grid, ilower[0], iupper[0]);

    /* Set grid extents for the second box */
    HYPRE_StructGridSetExtents(grid, ilower[1], iupper[1]);

    /* Assemble the grid */
    HYPRE_StructGridAssemble(grid);
}
