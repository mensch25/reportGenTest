#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <mpi.h>

int
main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int len = 10;
    int *buf = malloc(len * sizeof(int));

    if ((rank % 2) != 0) {
        /* odd */

        double t0 = MPI_Wtime();
        MPI_Recv(buf, len, MPI_INT, rank-1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double dt = MPI_Wtime() - t0;
        fprintf(stderr, "%d: Recv %.20f\n", rank, dt);

    } else {
        /* even */

        srand(time(NULL)+rank);
        for (size_t i = 0; i < len; i++) {
            buf[i] = i % 100;
        }

        double t0 = MPI_Wtime();
        MPI_Send(buf, len, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
        double dt = MPI_Wtime() - t0;
        fprintf(stderr, "%d: Send %.20f\n", rank, dt);
    }

    free(buf);

    MPI_Finalize();

    return 0;
}
