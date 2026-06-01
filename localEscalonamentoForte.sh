mpirun -np 1 ./mult_mpi 2048
mpirun -np 2 ./mult_mpi 2048
mpirun -np 4 ./mult_mpi 2048
mpirun --oversubscribe -np 8 ./mult_mpi 2048