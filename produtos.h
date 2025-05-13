#ifndef PRODUTOS_H
#define PRODUTOS_H

typedef struct produto Produto;
struct produto {
    char nome[50];
    char codigo[20];
    float preco;
};


void tela_produtos(void);
void tela_cadastrar_produto(void);
void tela_pesquisar_produto(void);
void tela_editar_produto(void);
void tela_deletar_produto(void);

#endif