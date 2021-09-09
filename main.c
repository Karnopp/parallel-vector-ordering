#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#include "ordena.h"
#include <omp.h>
#include <sys/time.h>
#include <sys/resource.h>

double wtime() {
  struct timespec t;
  clock_gettime(CLOCK_REALTIME, &t);
  return t.tv_sec + (double) t.tv_nsec / 1000000000;
}

int main(int argc, char *argv[]){
    if(argv[1]==NULL){
        printf("\nPor favor, passe um arquivo como parametro\n\n");
        return 0;
    }
    char *filename = argv[1];
    int i;
    char aux[100];
    double start_time, end_time;

    //pega o numero de elementos do nome do arquivo/////
    for(i=0;i<100;i++){
        if(filename[i]!='_'){
            aux[i]=filename[i];
        }
        else
            break;
    }
    int n_elementos = atoi(aux);
    /////////////////////////
    char teste[100];
    sprintf (teste, "%d_vet_original.map", n_elementos);
    if(strcmp(filename,teste)){
        printf("\nOpa! Nao aceitamos esse tipo de arquivo por aqui amigo\n\n");
        return 0;
    }

    int *vet_original = alocarVetor(n_elementos); //cria vetor original
    int *vet = alocarVetor(n_elementos); //cria vetor para operacoes

    FILE* arquivo;
    arquivo = fopen(filename,"r");
    if(!arquivo){
        printf("\nErro ao abrir arquivo, provavelmente arquivo inexistente\n\n");
        return 0;
    }
    leArquivo(arquivo, n_elementos, vet_original); //preenche vetor com dados do arquivo
    fclose(arquivo);

    copiaVetor(vet_original, vet, n_elementos);

    printf("\nBubble sort\n\n");


    //ordenacao sequencial
    start_time=wtime();
    bubbleSort_Seq(vet, n_elementos);
    end_time=wtime();

    printf("\nTempo de ordenacao sequencial: %f\n", (end_time-start_time));

    //grava vetor ordenado em um novo arquivo
    sprintf (filename, "%d_vet_ordenado_sequencial.result", n_elementos);
    arquivo = fopen(filename,"w");
    gravarDados(vet,arquivo,n_elementos);
    fclose(arquivo);

    copiaVetor(vet_original, vet, n_elementos);

    //ordenacao OpenMP

    start_time=wtime();
    bubbleSort_OMP(vet, n_elementos);
    end_time=wtime();

    printf("\nTempo de ordenacao OpenMP: %f\n", (end_time-start_time));

    //grava vetor ordenado em um novo arquivo
    sprintf (filename, "%d_vet_ordenado_omp.result", n_elementos);
    arquivo = fopen(filename,"w");
    gravarDados(vet,arquivo,n_elementos);
    fclose(arquivo);

    char cuda[100];
    sprintf (cuda, "./ordena_cuda %d_vet_original.map", n_elementos);

    //SE SUA MAQUINA NAO POSSUIR NVIDIA, COMENTE A LINHA ABAIXO
    system(cuda);



    //SE SUA MAQUINA NAO POSSUIR NVIDIA, TROQUE O && POR ||
    if(verificaArquivos_seq_omp(n_elementos) && verificaArquivos_seq_cuda(n_elementos))
        printf("\nArquivos de resultado semelhantes! \n(vetores resultantes iguais e ordenados)\n\n");
    else {
        printf("\nAlgo deu errado na ordenaocao... verificando separadamente...\n\n");
        if(verificaArquivos_seq_omp(n_elementos))
            printf("\nResultado sequencial igual OpenMP\n\n");
        else
            printf("\nResultado sequencial diferente de OpenMP\n\n");
        if(verificaArquivos_seq_cuda(n_elementos))
            printf("\nResultado sequencial igual CUDA\n\n");
        else
            printf("\nResultado sequencial diferente de CUDA\n\n");
    }
    free(vet);
    free(vet_original);


}
