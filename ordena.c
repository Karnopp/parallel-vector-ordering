#include "ordena.h"
#include <omp.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort_Seq(int *vet, int n){
    int i, j;
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-1; j++){
            if (vet[j] > vet[j+1]){
                swap(&vet[j], &vet[j+1]);
            }
        }
    }
}

void bubbleSort_OMP(int *vet, int n){
    int i, j;
    for (i = 0; i < n-1; i++){
        #pragma omp parallel for private(j)
        for (j = 0; j < n-1; j++){
            if (vet[j] > vet[j+1]){
                swap(&vet[j], &vet[j+1]);
            }
        }
    }
}

/*
temp = vet[j+1];
vet[j+1] = vet[j];
vet[j] = temp;
*/
