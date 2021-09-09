#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"

int main(int argc, char *argv[]){
    if(argv[1]==NULL){
        printf("\nPor favor, passe um tamanho de vetor como parametro\n\n");
        return 0;
    }
    int n_elementos = atoi(argv[1]);
    int *vet = alocarVetor(n_elementos);
    gerarValores(vet, n_elementos);
    FILE* arquivo;
    char filename [100];
    sprintf (filename, "%d_vet_original.map", n_elementos);
    arquivo = fopen(filename,"w");
    gravarDados(vet,arquivo,n_elementos);
    fclose(arquivo);
    printf("Arquivo %s criado!\n",filename);

}
