#ifndef CLIENTES_H
#define CLIENTES_H

typedef struct cliente Cliente;
struct cliente {
    char nome[50];
    char cpf[15];
    char telefone[15];
    char endereco[100];
};

void tela_clientes(void);
void tela_cadastrar_cliente(void);
void tela_pesquisar_cliente(void);
void tela_editar_cliente(void);
void tela_deletar_cliente(void);

#endif