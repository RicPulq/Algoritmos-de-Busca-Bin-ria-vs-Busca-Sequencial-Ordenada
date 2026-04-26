#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "busca_binaria.h"
#include "busca_sequencial.h"

// Função para medir o tempo médio da Busca Binária com alta precisão
long long medirTempoBinaria(int *vetor, int n, int valor_buscado, unsigned long long *comparacoes_out) {
    struct timespec start, end;
    long long tempo_total_ns = 0;
    int repeticoes = 0;
    unsigned long long comps = 0;
    volatile int dummy = 0; // Previne o compilador de otimizar a chamada da função
    
    clock_gettime(CLOCK_MONOTONIC, &start);
    do {
        // Lote de repetições para diluir o custo do clock_gettime
        for(int r = 0; r < 1000; r++) {
            dummy += buscaBinaria(vetor, n, valor_buscado, &comps);
        }
        repeticoes += 1000;
        clock_gettime(CLOCK_MONOTONIC, &end);
        tempo_total_ns = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
    } while (tempo_total_ns < 100000000LL); // Garante a execução por pelo menos 100ms
    
    *comparacoes_out = comps;
    return tempo_total_ns / repeticoes;
}

// Função para medir o tempo médio da Busca Sequencial Ordenada com alta precisão
long long medirTempoSequencial(int *vetor, int n, int valor_buscado, unsigned long long *comparacoes_out) {
    struct timespec start, end;
    long long tempo_total_ns = 0;
    int repeticoes = 0;
    unsigned long long comps = 0;
    volatile int dummy = 0; // Previne o compilador de otimizar a chamada da função
    
    clock_gettime(CLOCK_MONOTONIC, &start);
    do {
        // Lote menor devido à possibilidade de complexidade O(N) no pior caso
        for(int r = 0; r < 10; r++) {
            dummy += buscaSequencialOrdenada(vetor, n, valor_buscado, &comps);
        }
        repeticoes += 10;
        clock_gettime(CLOCK_MONOTONIC, &end);
        tempo_total_ns = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
    } while (tempo_total_ns < 100000000LL); // Garante a execução por pelo menos 100ms
    
    *comparacoes_out = comps;
    return tempo_total_ns / repeticoes;
}

int main() {
    int tamanhos[] = {50000, 100000, 1000000};
    int num_tamanhos = 3;
    
    printf("\n");
    printf("======================================================================================================\n");
    printf("                           ANALISE DE DESEMPENHO: BUSCA BINARIA VS SEQUENCIAL                         \n");
    printf("======================================================================================================\n");
    printf("%-10s | %-12s | %-21s | %-20s | %-15s\n", "Tamanho", "Posicao", "Algoritmo", "Tempo Medio (ns)", "Comparacoes");
    printf("======================================================================================================\n");

    for (int t = 0; t < num_tamanhos; t++) {
        int n = tamanhos[t];
        int *vetor = (int *)malloc(n * sizeof(int));
        if (!vetor) {
            printf("Erro de alocacao de memoria para o tamanho %d\n", n);
            return 1;
        }
        
        // Populando o vetor já ordenado (vetor[i] = i * 2)
        for (int i = 0; i < n; i++) {
            vetor[i] = i * 2;
        }
        
        // Posições: início (0), fim (n-1), meio (n/2), 1/3 (n/3)
        int posicoes[4] = {0, n - 1, n / 2, n / 3};
        char *nomes_pos[4] = {"Inicio (0)", "Fim (n-1)", "Meio (n/2)", "1/3 (n/3)"};
        
        for (int p = 0; p < 4; p++) {
            int pos_buscada = posicoes[p];
            int valor_buscado = vetor[pos_buscada];
            unsigned long long comparacoes_bin, comparacoes_seq;
            long long tempo_bin, tempo_seq;
            
            // Medindo tempos
            tempo_bin = medirTempoBinaria(vetor, n, valor_buscado, &comparacoes_bin);
            tempo_seq = medirTempoSequencial(vetor, n, valor_buscado, &comparacoes_seq);
            
            // Exibindo resultados
            printf("%-10d | %-12s | %-21s | %-20lld | %-15llu\n", n, nomes_pos[p], "Binaria", tempo_bin, comparacoes_bin);
            printf("%-10d | %-12s | %-21s | %-20lld | %-15llu\n", n, nomes_pos[p], "Sequencial Ordenada", tempo_seq, comparacoes_seq);
            
            if (p < 3) {
                printf("------------------------------------------------------------------------------------------------------\n");
            }
        }
        
        free(vetor);
        printf("======================================================================================================\n");
    }

    return 0;
}
