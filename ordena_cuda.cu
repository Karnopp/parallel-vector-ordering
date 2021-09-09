
#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>

#define T 1024 // numero max de threads por bloco

//GPU
__global__ void bubbleSort_cuda(int *vet, int temp, int n){
    int j =  2*(blockIdx.x * blockDim.x + threadIdx.x);

        if (vet[j] > vet[j+1] && j<n-1){
            //swap(&vet[j],&vet[j+1]);
            temp=vet[j];
            vet[j]=vet[j+1];
            vet[j+1]=temp;
        }

}
//GPU
__global__ void bubbleSort_cuda2(int *vet, int temp, int n){
    int j =  2*(blockIdx.x * blockDim.x + threadIdx.x)+1;

        if (vet[j] > vet[j+1] && j<n-2){
            //swap(&vet[j],&vet[j+1]);
            temp=vet[j];
            vet[j]=vet[j+1];
            vet[j+1]=temp;
        }

}

double wtime() {
  struct timespec t;
  clock_gettime(CLOCK_REALTIME, &t);
  return t.tv_sec + (double) t.tv_nsec / 1000000000;
}

// CPU: função principal
int main(int argc, char const *argv[]) {

    char filename[100];

    int i;
    char aux[100];

    sprintf (filename, "%s", argv[1]); //escreve o nome do arquivo passado

    //pega o numero de elementos do nome do arquivo/////
    for(i=0;i<100;i++){
        if(filename[i]!='_'){
            aux[i]=filename[i];
        }
        else
            break;
    }
    int n_elementos = atoi(aux);


    int *vet_original; //cria vetor original
    int *vet_result; //cria vetor para operacoes
    int size = sizeof(int)*n_elementos;

    cudaMallocHost((void **) &vet_original, size);
    cudaMallocHost((void **) &vet_result, size);

    FILE* arquivo;
    arquivo = fopen(filename,"r");

    for(i = 0; i < n_elementos; i++){
        fscanf (arquivo, "%d", &vet_original[i]); //pega os valores do arquivo e salva no vetor na cpu
    }
    fclose(arquivo);


    int *vet_cuda;
    cudaMalloc((void **) &vet_cuda, size);

    int temp;
    cudaMalloc((void **) &temp, sizeof(int));


    cudaMemcpy(vet_cuda, vet_original, size, cudaMemcpyHostToDevice); //copia o vetor da cpu para o vetor da gpu

    double start_time, end_time;
    start_time=wtime();
    for(i=0;i<n_elementos;i++){
        bubbleSort_cuda<<<(int)ceil(n_elementos/T),T>>>(vet_cuda, temp, n_elementos);
        bubbleSort_cuda2<<<(int)ceil(n_elementos/T),T>>>(vet_cuda, temp, n_elementos);
    }
    end_time=wtime();

    printf("\nTempo de ordenacao CUDA: %f\n", (end_time-start_time));

    cudaMemcpy(vet_result, vet_cuda, size, cudaMemcpyDeviceToHost); //copia o vetor da gpu para o vetor da cpu


    sprintf (filename, "%d_vet_ordenado_cuda.result", n_elementos);
    arquivo = fopen(filename,"w");
    for(i=0;i<n_elementos;i++){
        fprintf(arquivo,"%d ", vet_result[i]); //grava o resultado no arquivo de saida
    }
    fclose(arquivo);


    // Libera a Memória Global (GPU)
    cudaFree(vet_cuda);

    // Libera a Memória Global (CPU)
    cudaFreeHost(vet_result);
    cudaFreeHost(vet_original);


  return 0;
}
