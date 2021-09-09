
#include "vetor.h"

int *alocarVetor(int n){
    int *v = malloc(n * sizeof (int));
    return v;
}

void gerarValores(int *v, int n_elementos){
    srand(time(NULL));
    int i;
    for(i = 0; i < n_elementos; i++){
        v[i] = rand() % 1000;
    }
}

void copiaVetor(int *vet_original, int *vet, int n_elementos){
    int i;
    for(i=0; i<n_elementos;i++){
        vet[i]=vet_original[i];
    }
}

void gravarDados(int *v, FILE* arquivo, int n_elementos){
    int i;
    for(i=0;i<n_elementos;i++){
        fprintf(arquivo,"%d ", v[i]);
    }
}

void leArquivo(FILE* arquivo, int n_elementos, int *vet){
    int i;
    for(i = 0; i < n_elementos; i++){
        fscanf (arquivo, "%d", &vet[i]);
    }
}

int verificaArquivos_seq_omp(int n_elementos){
    FILE *arq_seq, *arq_omp;
    char filename[100];

    sprintf (filename, "%d_vet_ordenado_sequencial.result", n_elementos);
    arq_seq = fopen(filename,"r");

    sprintf (filename, "%d_vet_ordenado_omp.result", n_elementos);
    arq_omp = fopen(filename,"r");

    int i, aux_seq, aux_omp;
    for(i=0;i<n_elementos;i++){
        fscanf (arq_seq, "%d", &aux_seq);
        fscanf (arq_omp, "%d", &aux_omp);
        if(aux_seq!=aux_omp){
            fclose(arq_seq);
            fclose(arq_omp);
            return 0;
        }
    }
    fclose(arq_seq);
    fclose(arq_omp);
    return 1;
}

int verificaArquivos_seq_cuda(int n_elementos){
    FILE *arq_seq, *arq_omp;
    char filename[100];

    sprintf (filename, "%d_vet_ordenado_sequencial.result", n_elementos);
    arq_seq = fopen(filename,"r");

    sprintf (filename, "%d_vet_ordenado_cuda.result", n_elementos);
    arq_omp = fopen(filename,"r");

    int i, aux_seq, aux_omp;
    for(i=0;i<n_elementos;i++){
        fscanf (arq_seq, "%d", &aux_seq);
        fscanf (arq_omp, "%d", &aux_omp);
        if(aux_seq!=aux_omp){
            fclose(arq_seq);
            fclose(arq_omp);
            return 0;
        }
    }
    fclose(arq_seq);
    fclose(arq_omp);
    return 1;
}
