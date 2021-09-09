all: compile

compile:
	@gcc geraVetor.c vetor.c -o geraVetor
	@gcc vetor.c -fopenmp main.c ordena.c -o ordenaVetor
	@nvcc ordena_cuda.cu -o ordena_cuda -gencode arch=compute_35,code=sm_35 -Wno-deprecated-gpu-targets
	@echo
	@echo "Para gerar um arquivo com um vetor desordenado: ./geraVetor 'n_elementos'"
	@echo
	@echo "Para ordernar o vetor contido em um arquivo: ./ordenaVetor 'arquivo'"
	@echo
	@echo "Para executar um exemplo: make run"
	@echo
	@echo "Para limpar tudo: make clean"
	@echo
	@echo "Obs: Verifique se sua maquina possui gpu nvidia e leia o README"
	@echo

clean:
	@rm *.map *.result geraVetor ordenaVetor ordena_cuda

run:
	@./geraVetor 10000
	@./ordenaVetor 10000_vet_original.map
