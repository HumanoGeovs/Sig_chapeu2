#ifndef PRODUTOS_H
#define PRODUTOS_H

typedef struct produto Produto;
struct produto {
    char nome[50];
    char codigo[20];
    float preco;
    int status; // 1 = ativo, 0 = inativo
};

void tela_produtos(void);
void tela_cadastrar_produto(void);
void tela_pesquisar_produto(void);
void tela_editar_produto(void);
void tela_deletar_produto(void);

// NOVAS FUNÇÕES
void gerar_codigo_barras(char* codigo_gerado);
int calcula_digito_verificador(const char *codigo);

#endif