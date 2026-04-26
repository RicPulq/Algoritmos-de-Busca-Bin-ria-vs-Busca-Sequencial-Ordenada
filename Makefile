CC = gcc
CFLAGS = -O3 -Wall -Wextra

all: comparacao_busca

comparacao_busca: comparacao_busca.o busca_binaria.o busca_sequencial.o
	$(CC) $(CFLAGS) -o comparacao_busca comparacao_busca.o busca_binaria.o busca_sequencial.o

comparacao_busca.o: comparacao_busca.c busca_binaria.h busca_sequencial.h
	$(CC) $(CFLAGS) -c comparacao_busca.c

busca_binaria.o: busca_binaria.c busca_binaria.h
	$(CC) $(CFLAGS) -c busca_binaria.c

busca_sequencial.o: busca_sequencial.c busca_sequencial.h
	$(CC) $(CFLAGS) -c busca_sequencial.c

clean:
	rm -f *.o comparacao_busca
