#include <mpi.h>

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

constexpr int TAG_PEDIDO = 1;
constexpr int TAG_TRABALHO = 2;
constexpr int TAG_RESULTADO = 3;
constexpr int TAG_TERMINO = 4;

static void PreencherAleatorio(std::vector<double>& matriz, int n, unsigned int semente) {
    std::mt19937 gerador(semente);
    std::uniform_real_distribution<double> distribuicao(0.0, 1.0);

    for (int i = 0; i < n * n; ++i) {
        matriz[i] = distribuicao(gerador);
    }
}

static void MultiplicarSequencial(const std::vector<double>& A,
                                  const std::vector<double>& B,
                                  std::vector<double>& C,
                                  int n) {
    std::fill(C.begin(), C.end(), 0.0);

    for (int i = 0; i < n; ++i) {
        int baseA = i * n;
        int baseC = i * n;
        for (int k = 0; k < n; ++k) {
            double a = A[baseA + k];
            int baseB = k * n;
            for (int j = 0; j < n; ++j) {
                C[baseC + j] += a * B[baseB + j];
            }
        }
    }
}

static void MultiplicarLinha(const std::vector<double>& linhaA,
                             const std::vector<double>& B,
                             std::vector<double>& linhaC,
                             int n) {
    std::fill(linhaC.begin(), linhaC.end(), 0.0);

    for (int k = 0; k < n; ++k) {
        double a = linhaA[k];
        int baseB = k * n;
        for (int j = 0; j < n; ++j) {
            linhaC[j] += a * B[baseB + j];
        }
    }
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank = 0;
    int tamanhoMundo = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &tamanhoMundo);

    int n = 0;
    if (rank == 0) {
        if (argc < 2) {
            std::cerr << "Uso: mpirun -np <processos> ./matmul_mpi <tamanho>\n";
            std::cerr << "Exemplo: mpirun -np 4 ./matmul_mpi 1024\n";
            n = 0;
        } else {
            n = std::atoi(argv[1]);
        }
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (n <= 0) {
        MPI_Finalize();
        return 1;
    }

    std::vector<double> B(static_cast<size_t>(n) * n);
    std::vector<double> A;
    std::vector<double> C;

    if (rank == 0) {
        A.resize(static_cast<size_t>(n) * n);
        C.resize(static_cast<size_t>(n) * n);
        PreencherAleatorio(A, n, 42);
        PreencherAleatorio(B, n, 99);
    }

    double inicio = 0.0;
    if (rank == 0) {
        inicio = MPI_Wtime();
    }

    MPI_Bcast(B.data(), n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (tamanhoMundo == 1) {
        if (rank == 0) {
            MultiplicarSequencial(A, B, C, n);
            double tempoTotal = MPI_Wtime() - inicio;

            std::cout << "Multiplicacao de matrizes sequencial (MPI com 1 processo)\n";
            std::cout << "Dimensao: " << n << " x " << n << "\n\n";
            std::cout << "----------------------------------------\n";
            std::cout << "Tempo de execucao: " << std::fixed << std::setprecision(4)
                      << tempoTotal << " segundos\n";
            std::cout << "----------------------------------------\n";
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        std::cout << "Multiplicacao de matrizes com MPI (coordenador/trabalhador)\n";
        std::cout << "Dimensao: " << n << " x " << n << "\n";
        std::cout << "Processos: " << tamanhoMundo << "\n\n";

        int proximaLinha = 0;
        int trabalhadoresEncerrados = 0;
        int totalTrabalhadores = tamanhoMundo - 1;
        int dummy = 0;

        while (trabalhadoresEncerrados < totalTrabalhadores) {
            MPI_Status status;
            MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            int fonte = status.MPI_SOURCE;

            if (status.MPI_TAG == TAG_PEDIDO) {
                MPI_Recv(&dummy, 1, MPI_INT, fonte, TAG_PEDIDO, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                if (proximaLinha < n) {
                    MPI_Send(&proximaLinha, 1, MPI_INT, fonte, TAG_TRABALHO, MPI_COMM_WORLD);
                    MPI_Send(&A[static_cast<size_t>(proximaLinha) * n], n, MPI_DOUBLE,
                             fonte, TAG_TRABALHO, MPI_COMM_WORLD);
                    ++proximaLinha;
                } else {
                    MPI_Send(&dummy, 1, MPI_INT, fonte, TAG_TERMINO, MPI_COMM_WORLD);
                    ++trabalhadoresEncerrados;
                }
            } else if (status.MPI_TAG == TAG_RESULTADO) {
                int indiceLinha = -1;
                MPI_Recv(&indiceLinha, 1, MPI_INT, fonte, TAG_RESULTADO, MPI_COMM_WORLD,
                         MPI_STATUS_IGNORE);
                MPI_Recv(&C[static_cast<size_t>(indiceLinha) * n], n, MPI_DOUBLE,
                         fonte, TAG_RESULTADO, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }

        double tempoTotal = MPI_Wtime() - inicio;

        std::cout << "----------------------------------------\n";
        std::cout << "Tempo de execucao: " << std::fixed << std::setprecision(4)
                  << tempoTotal << " segundos\n";
        std::cout << "----------------------------------------\n";
    } else {
        std::vector<double> linhaA(n);
        std::vector<double> linhaC(n);
        int dummy = 0;

        while (true) {
            MPI_Send(&dummy, 1, MPI_INT, 0, TAG_PEDIDO, MPI_COMM_WORLD);

            MPI_Status status;
            int indiceLinha = -1;
            MPI_Recv(&indiceLinha, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            if (status.MPI_TAG == TAG_TERMINO) {
                break;
            }

            MPI_Recv(linhaA.data(), n, MPI_DOUBLE, 0, TAG_TRABALHO, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MultiplicarLinha(linhaA, B, linhaC, n);
            MPI_Send(&indiceLinha, 1, MPI_INT, 0, TAG_RESULTADO, MPI_COMM_WORLD);
            MPI_Send(linhaC.data(), n, MPI_DOUBLE, 0, TAG_RESULTADO, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
