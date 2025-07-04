# Nome do executável
TARGET = sig_chapeu

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

# Arquivos fonte
SRCS = src/main.c src/clientes.c src/produtos.c src/encomendas.c src/pedidos.c src/util.c

# Arquivos objeto
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Regra para compilar os arquivos .c em .o
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados

clean:
	rm -f src/*.o $(TARGET)

# Regra para compilar e executar o programa
run: $(TARGET)
	./$(TARGET)

#include "clientes.h"