#include "busca_sequencial.h"

// Função para Busca Sequencial Ordenada com Early Exit
int buscaSequencialOrdenada(int *vetor, int tamanho, int valor, unsigned long long *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < tamanho; i++) {
        (*comparacoes)++;
        if (vetor[i] == valor) {
            return i;
        }
        (*comparacoes)++;
        if (vetor[i] > valor) {
            return -1; // Condição de parada antecipada (early exit)
        }
    }
    return -1;
}
