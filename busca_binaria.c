#include "busca_binaria.h"

// Função para Busca Binária
int buscaBinaria(int *vetor, int tamanho, int valor, unsigned long long *comparacoes) {
    int inicio = 0;
    int fim = tamanho - 1;
    int meio;
    *comparacoes = 0;

    while (inicio <= fim) {
        meio = inicio + (fim - inicio) / 2;
        
        (*comparacoes)++;
        if (vetor[meio] == valor) {
            return meio;
        }
        
        (*comparacoes)++;
        if (vetor[meio] < valor) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}
