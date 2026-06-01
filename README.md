# Sequencial

## Compilar

```g++ -O2 -std=c++17 -o mult mult.cpp```

## Executar

```./mult <tamanhoDaMatriz>```

---

# Paralelo

## Compilar

```mpic++ -O2 -o mult_mpi mult_mpi.cpp```

## Executar (não distribuido)

```mpirun -np <numeroDeProcessos> ./matmul_mpi <tamanhoDaMatriz>```

## Executar (distribuido)

```mpirun -np <numeroDeProcessos> -ppn <processosPorNo> ./matmul_mpi <tamanhoDaMatriz>```

Sendo:
-np:	Número total de processos em toda a execução
-ppn:	Processos por nó (máquina individual)

# Máquina Remota (LAD)

**Compilação:**
```bash
ladcomp -env mpicc file.c -o file_exec
```

**Execução:**
```bash
srun -N 2 -n 2 ./file_exec
```
> onde `N` é o número de nodos e `n` o número total de processos que serão criados

---