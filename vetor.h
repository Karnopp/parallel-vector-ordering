#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int *alocarVetor(int n);

void gerarValores(int *v, int n_elementos);

void gravarDados(int *v, FILE* arquivo, int n_elementos);

void leArquivo(FILE* arquivo, int n_elementos, int *vet);

void copiaVetor(int *vet_original, int *vet, int n_elementos);

int verificaArquivos_seq_omp(int n_elementos);

int verificaArquivos_seq_cuda(int n_elementos);
