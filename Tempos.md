# Resultados de Avaliação de Tempo

### Speed-Up - Escalonamento Forte

Multiplicacao de matrizes com MPI (coordenador/trabalhador)
Dimensao: 2048 x 2048
Processos: 2
----------------------------------------
Tempo de execucao: 101.7241 segundos
----------------------------------------

Multiplicacao de matrizes com MPI (coordenador/trabalhador)
Dimensao: 2048 x 2048
Processos: 4
----------------------------------------
Tempo de execucao: 52.4436 segundos
----------------------------------------

Multiplicacao de matrizes com MPI (coordenador/trabalhador)
Dimensao: 2048 x 2048
Processos: 8
----------------------------------------
Tempo de execucao: 27.0152 segundos
----------------------------------------

Multiplicacao de matrizes com MPI (coordenador/trabalhador)
Dimensao: 2048 x 2048
Processos: 16
----------------------------------------
Tempo de execucao: 12.7195 segundos
----------------------------------------

Multiplicacao de matrizes com MPI (coordenador/trabalhador)
Dimensao: 2048 x 2048
Processos: 32
----------------------------------------
Tempo de execucao: 6.1325 segundos
----------------------------------------

### Tabela Resumo

Núcleos 	Tempo de Execução (s)	Speed-Up	Speed-Up Ideal	Eficiência
1	                101             	1,0	          1       	    1,0
3	                52              	1,9	          3       	    0,6
7	                27              	3,7	          7       	    0,5
15	                12              	8,4	          15      	    0,6
31	                6               	16,8	      31      	    0,5


---

### Speed-Up - Escalonamento Fraco

Multiplicacao de matrizes com MPI (coordenador/trabalhador)
Dimensao: 2048 x 2048
Processos: 2
----------------------------------------
Tempo de execucao: 101.6311 segundos
----------------------------------------

Multiplicacao de matrizes com MPI (coordenador/trabalhador)
Dimensao: 2555 x 2555
Processos: 4
----------------------------------------
Tempo de execucao: 103.1153 segundos
----------------------------------------

Multiplicacao de matrizes com MPI (coordenador/trabalhador)
Dimensao: 3317 x 3317
Processos: 8
----------------------------------------
Tempo de execucao: 101.9390 segundos
----------------------------------------

Multiplicacao de matrizes com MPI (coordenador/trabalhador)
Dimensao: 4226 x 4226
Processos: 16
----------------------------------------
Tempo de execucao: 110.0662 segundos
----------------------------------------

Multiplicacao de matrizes com MPI (coordenador/trabalhador)
Dimensao: 5286 x 5286
Processos: 32
----------------------------------------
Tempo de execucao: 102.6636 segundos
----------------------------------------

### Tabela Resumo

Núcleos 	Tempo de Execução (s)	Speed-Up	Speed-Up Ideal	Eficiência
1	                101	              1,0	            1	        1,0
3	                103	              1,0	            1	        0,3
7	                101	              1,0	            1	        0,1
15	                110	              0,9	            1	        0,1
31	                102	              1,0	            1	        0,0



---