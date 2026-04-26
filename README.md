# Algoritmos de Busca: Comparativo de Desempenho

Este diretório contém a implementação em linguagem C dos algoritmos **Busca Binária** e **Busca Sequencial Ordenada** desenvolvidos para fins de análise acadêmica. O objetivo principal do programa é gerar um *benchmark* rigoroso, aferindo o tempo de execução (em nanosegundos) e contabilizando com exatidão o número de comparações executadas por cada método.

## 📂 Estrutura do Diretório

- `busca_binaria.c` e `.h`: Implementação modular da Busca Binária com cálculo de meio seguro (`inicio + (fim - inicio) / 2`).
- `busca_sequencial.c` e `.h`: Implementação modular da Busca Sequencial Ordenada, otimizada com parada antecipada (*Early Exit*).
- `comparacao_busca.c`: Ponto de entrada (`main`) que aloca os vetores ordenados em três dimensões (50k, 100k e 1M) e aciona as rotinas avançadas de *microbenchmarking* em lotes.
- `explicacao_buscas.md`: Documentação técnica com a lógica interna e a metodologia de aferição de tempo.
- `Makefile`: Script autônomo para facilitar a montagem da compilação.

---

## 🚀 Como Compilar e Executar (Linux)

Graças ao uso de Módulos e do `Makefile`, compilar o projeto é um processo automatizado. O compilador (GCC) está pré-configurado com a flag de otimização de performance avançada `-O3`.

### 1. Acesse o diretório local
Abra o seu terminal integrado e garanta que você está operando dentro da pasta correspondente:
```bash
cd Busca
```

### 2. Compile o código-fonte
Utilize o utilitário `make` para compilar, montar os objetos e gerar o binário da aplicação:
```bash
make
```
> **Nota de Manutenção:** Caso necessite forçar a exclusão dos binários antigos para obrigar uma compilação 100% limpa, basta rodar `make clean` antes de efetuar o `make`.

### 3. Inicie os testes (Benchmarking)
Um arquivo executável chamado `comparacao_busca` será gerado pelo compilador. Para ativá-lo, utilize o comando:
```bash
./comparacao_busca
```

---

## 📊 Compreendendo a Saída

Para favorecer a extração das métricas, a saída gerada no console é tabelada metodicamente:

- **Tamanho**: A quantidade preestabelecida de elementos no vetor.
- **Posição**: O endereço exato do valor que está sendo testado (Início, Fim, Meio e 1/3 do vetor).
- **Algoritmo**: O nome técnico da abordagem submetida ao teste.
- **Tempo Médio (ns)**: A métrica em Nanosegundos estabilizada de execução após milhares de testes silenciando as variações do SO.
- **Comparações**: A exata quantidade de checagens lógicas (ex: `<`, `>`, `==`) acionadas pelo método para concluir a busca.

Essa grade gerada se torna excelente para capturas de tela (*Print Screens*) em relatórios técnicos ou para cópia direta em softwares de planilha (ex: Excel) para a elaboração de Gráficos de dispersão.
