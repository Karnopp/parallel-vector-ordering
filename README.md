# parallel-vector-ordering
Primeiro passo:
```
make
```

Caso queira gerar um arquivo com valores aleatorios:
```
./gerarVetor <numero_elementos>
```
obs: `<numero_elementos>` deve ser um valor inteiro, referindo-se ao tamanho do vetor desejado

Para rodar:
```
./ordenaVetor <arquivo>
```
obs: `<arquivo>` refere-se ao nome do arquivo que contenha os elementos, este arquivo possui formação = [numero_elementos]_vet_original.map
o código criará outros 3 arquivos com os vetores ordenados, um arquivo para cada tipo de ordenação (sequencial, omp e cuda)
ao final da execução, o programa apresenta o tempo de execução para cada tipo e compara os 3 arquivos para verificar se são indênticos = deu certo a ordenação

Para rodar um exemplo:
```
make run
```

Para limpar TUDO:
```
make clean
```

OBSERVAÇÃO: Código CUDA executa em uma máquina com Nvidia Geforce 920m, por isso os parametros "-gencode arch=compute_35,code=sm_35" na compilação, esta placa gráfica utiliza "power" de 3,5 conforme a nvidia < https://developer.nvidia.com/cuda-gpus >, e este parametro deve ser passado para o compilador cuda

Para utilizar com outra placa gráfica da Nvidia, favor verificar no site a cima o "power" correspondente e alterar o parametro arch e code, no meu caso está compute_35 e sm_35 devido ao "power" de 3,5, se fosse power de 6,0 seria compute_60 e sm_60

Se não possuir placa nvidia, faça alterações sugeridas no arquivo main.c para ordenar vetor apenas no modo sequencial e OpenMP
 
