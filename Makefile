# Nome do executável
TARGET = sig_chapeu

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99

# Arquivos fonte
SRCS = main.c clientes.c produtos.c encomendas.c

# Arquivos objeto
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar os arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)

# Regra para compilar e executar o programa
run: $(TARGET)
	./$(TARGET)
