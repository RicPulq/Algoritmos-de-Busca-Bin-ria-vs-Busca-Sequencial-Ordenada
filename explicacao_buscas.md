# Análise e Implementação dos Algoritmos de Busca

Este documento explica detalhadamente o funcionamento teórico e a implementação prática dos algoritmos de **Busca Binária** e **Busca Sequencial Ordenada**, desenvolvidos em linguagem C para a análise de desempenho.

---

## 1. Busca Binária

### Como Funciona (Teoria)
A Busca Binária é um algoritmo altamente eficiente que utiliza o paradigma de **Divisão e Conquista**. Ela opera **exclusivamente em vetores ordenados**. 

O processo funciona da seguinte forma:
1. O algoritmo compara o valor buscado com o elemento central do vetor.
2. Se o valor buscado for igual ao elemento central, a busca é concluída com sucesso.
3. Se o valor buscado for menor que o elemento central, a busca continua apenas na metade inferior do vetor.
4. Se o valor buscado for maior, a busca continua na metade superior do vetor.
5. Esse processo de dividir o intervalo de busca pela metade se repete até que o valor seja encontrado ou o intervalo de busca se esgote (indicando que o elemento não existe no vetor).

**Complexidade:**
*   **Tempo:** O(log N) no pior e médio caso. O(1) no melhor caso (quando o valor está exatamente no meio na primeira tentativa). O crescimento do tempo é logarítmico, o que a torna extremamente veloz mesmo para vetores gigantescos.
*   **Espaço:** O(1), pois não necessita de alocação de memória extra (iterativa).

### Como Está Implementado (Prática)
A implementação está concentrada no módulo `busca_binaria.c`.
*   A função `buscaBinaria` utiliza três variáveis de controle: `inicio`, `fim` e `meio`.
*   Um laço `while (inicio <= fim)` controla as iterações. O `meio` é calculado para evitar *overflow* de inteiros em vetores imensos: `meio = inicio + (fim - inicio) / 2;`.
*   A cada iteração, os ponteiros `inicio` ou `fim` são atualizados para descartar metade do vetor analisado.
*   **Contagem de Comparações:** Através do ponteiro `*comparacoes`, contabilizamos cada teste lógico efetuado (o teste de igualdade `==` e o teste de desigualdade `<`). Em média, são feitas duas comparações por iteração no pior caso.

---

## 2. Busca Sequencial Ordenada

### Como Funciona (Teoria)
A Busca Sequencial (ou Linear) é o método mais simples de procurar um elemento: ele verifica cada posição do vetor, uma a uma, a partir do início. 

No entanto, a versão implementada aqui é a **Busca Sequencial Ordenada**. O fato de sabermos que o vetor está previamente ordenado nos permite adicionar uma otimização crucial: a **condição de parada antecipada** (*early exit*).
* Se estivermos procurando o número `10` e, durante a varredura, encontrarmos o número `12`, sabemos imediatamente que o `10` não está nas próximas posições (pois todos os próximos números serão maiores ou iguais a `12`). O algoritmo, então, pode abortar a busca prematuramente.

**Complexidade:**
*   **Tempo:** O(N) no pior caso (quando o elemento está no fim do vetor ou é maior que todos) e médio caso. O(1) no melhor caso (se for o primeiro elemento).
*   **Espaço:** O(1).

### Como Está Implementado (Prática)
A implementação está concentrada no módulo `busca_sequencial.c`.
*   A função `buscaSequencialOrdenada` utiliza um simples laço `for (int i = 0; i < tamanho; i++)`.
*   **Early Exit:** A cada iteração, é feito o teste `if (vetor[i] > valor)`. Se for verdadeiro, a função retorna `-1` (não encontrado), quebrando o laço imediatamente.
*   **Contagem de Comparações:** O contador `*comparacoes` rastreia cada vez que o valor alvo é confrontado com os itens do vetor, registrando 2 comparações por iteração (o `==` e o `>`).

---

## 3. Metodologia de Medição de Tempo (Microbenchmarking)

Ao medir algoritmos tão rápidos (especialmente a Busca Binária, que pode levar apenas de 10 a 20 nanosegundos), ferramentas comuns como a função `clock()` não possuem resolução suficiente, gerando o tempo ilusório de `0.000000` segundos.

Para resolver isso, a implementação no arquivo `comparacao_busca.c` utiliza uma técnica avançada de *microbenchmarking*:

1. **Uso de Relógio de Alta Precisão:** Utiliza-se `clock_gettime(CLOCK_MONOTONIC)`, nativo do Linux, que afere o tempo em **nanosegundos**.
2. **Execução em Lote (Batching):** As funções de medição (`medirTempoBinaria` e `medirTempoSequencial`) encapsulam as buscas em um laço temporal `do...while`.
3. **Mínimo de Execução:** O algoritmo é executado de forma repetida até que o somatório do tempo da execução alcance um limiar confiável de, no mínimo, **100 milissegundos** (`100.000.000` de nanosegundos).
4. **Cálculo da Média Pura:** Após acumular um tempo considerável e imune às falhas do processador de tarefas do SO (escalonador), dividimos o tempo total exato pelo número de repetições efetuadas para encontrar a média temporal exata de **uma única execução**.
5. **Prevenção de Otimização do Compilador (Volatile):** Como as execuções repetidas não utilizam os valores de retorno, compiladores modernos (com `-O3`) removeriam a chamada de busca das execuções ("*Dead Code Elimination*"). A variável `volatile int dummy` é usada para forçar o compilador a computar todas as buscas, pois uma variável `volatile` indica que o dado tem efeitos colaterais e não pode ser ignorado na compilação.
