#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "util.h" 

typedef struct produto Produto;

void tela_produtos(void) {
    int opcao;
    do {
        printf("\n");
        printf("+============================================================================+\n");
        printf("|                       MENU DE PRODUTOS - SIG CHAPEU                       |\n");
        printf("+============================================================================+\n");
        printf("|  1. Cadastrar Produto   |  2. Pesquisar Produto   |  3. Editar Produto     |\n");
        printf("|-------------------------+-------------------------+------------------------|\n");
        printf("|  4. Deletar Produto     |  0. Voltar ao Menu Principal                     |\n");
        printf("+============================================================================+\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        system("cls||clear");

        switch (opcao) {
            case 1:
                tela_cadastrar_produto();
                break;
            case 2:
                tela_pesquisar_produto();
                break;
            case 3:
                tela_editar_produto();
                break;
            case 4:
                tela_deletar_produto();
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para voltar ao menu de produtos...");
            getchar();
        }

        system("cls||clear");
    } while (opcao != 0);
}

// Função para calcular o dígito verificador EAN-13
int calcula_digito_verificador(const char *codigo) {
    int soma = 0;
    for (int i = 0; i < 12; i++) {
        int digito = codigo[i] - '0';
        if ((i % 2) == 0) {
            soma += digito;
        } else {
            soma += digito * 3;
        }
    }
    int resto = soma % 10;
    return (resto == 0) ? 0 : 10 - resto;
}

// Função para obter o próximo código de produto (4 dígitos)
int obter_proximo_codigo_produto() {
    FILE *arquivo = fopen("produtos.txt", "r");
    int ultimo_codigo = 0;
    if (arquivo != NULL) {
        char linha[256];
        while (fgets(linha, sizeof(linha), arquivo)) {
            // O código do produto está nas posições 8 a 11 do código EAN-13
            char codigo_produto[5];
            strncpy(codigo_produto, linha + 8, 4);
            codigo_produto[4] = '\0';
            int codigo = atoi(codigo_produto);
            if (codigo > ultimo_codigo) {
                ultimo_codigo = codigo;
            }
        }
        fclose(arquivo);
    }
    return ultimo_codigo + 1;
}

// Função para gerar o código de barras EAN-13 automaticamente
void gerar_codigo_barras(char* codigo_gerado) {
    int numero_produto = obter_proximo_codigo_produto();
    if (numero_produto > 9999) numero_produto = 1; // reinicia se passar de 9999

    // Monta o código base: 78900000 + produto (4 dígitos) = 12 dígitos
    char codigo_base[13];
    snprintf(codigo_base, sizeof(codigo_base), "78900000%04d", numero_produto);

    // Calcula o dígito verificador
    int dv = calcula_digito_verificador(codigo_base);

    // Monta o código final com o dígito verificador (13 dígitos)
    snprintf(codigo_gerado, 14, "%s%c", codigo_base, dv + '0');
}

void tela_cadastrar_produto(void) {
    Produto produto;

    printf("\nNome do Produto: ");
    fgets(produto.nome, sizeof(produto.nome), stdin);
    produto.nome[strcspn(produto.nome, "\n")] = '\0'; // Remove o '\n'

    if (!validarNomeProduto(produto.nome)) {
        printf("Nome inválido! Só pode conter letras, números e espaço. Tente novamente.\n");
        return;
    }

    // Geração automática do código de barras
    gerar_codigo_barras(produto.codigo);
    printf("Código de Barras Gerado: %s\n", produto.codigo);

    printf("Preço do Produto: ");
    scanf("%f", &produto.preco);
    getchar(); // Limpa o buffer do teclado

    if (produto.preco <= 0) {
        printf("Preço inválido! Deve ser maior que zero. Tente novamente.\n");
        return;
    }

    salvar_produto(&produto);

    printf("Produto cadastrado e salvo com sucesso!\n");
}

void listar_produtos(void) {
    FILE* arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    char linha[256];
    printf("\nProdutos cadastrados:\n");
    printf("-----------------------------------------------------\n");
    printf("%-15s | %-30s | %s\n", "Código de Barras", "Nome", "Preço");
    printf("-----------------------------------------------------\n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        char cod[20], nome[50];
        float preco;
        sscanf(linha, "%19[^;];%49[^;];%f", cod, nome, &preco);
        printf("%-15s | %-30s | %.2f\n", cod, nome, preco);
    }
    printf("-----------------------------------------------------\n");
    fclose(arquivo);
}

void tela_pesquisar_produto(void) {
    listar_produtos();
    printf("Pressione ENTER para continuar...");
    getchar();
}

void tela_editar_produto(void) {
    char codigo[20];
    printf("\nDigite o código de barras do produto para editar: ");
    fgets(codigo, sizeof(codigo), stdin);
    codigo[strcspn(codigo, "\n")] = '\0';
    editar_produto(codigo);
    printf("Pressione ENTER para continuar...");
    getchar();
}

void tela_deletar_produto(void) {
    char codigo[20];
    printf("\nDigite o código de barras do produto para deletar: ");
    fgets(codigo, sizeof(codigo), stdin);
    codigo[strcspn(codigo, "\n")] = '\0';
    deletar_produto(codigo);
    printf("Pressione ENTER para continuar...");
    getchar();
}

void salvar_produto(const Produto* produto) {
    FILE* fp = fopen("produtos.txt", "a");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para salvar produto.\n");
        return;
    }
    fprintf(fp, "%s;%s;%.2f\n", produto->codigo, produto->nome, produto->preco);
    fclose(fp);
}

// Função para pesquisar e exibir um produto pelo código de barras
void pesquisar_produto(const char* codigo) {
    FILE* arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    char linha[256];
    int encontrado = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        char cod[20], nome[50];
        float preco;
        sscanf(linha, "%19[^;];%49[^;];%f", cod, nome, &preco);
        if (strcmp(codigo, cod) == 0) {
            printf("\nProduto encontrado:\n");
            printf("Código de Barras: %s\n", cod);
            printf("Nome: %s\n", nome);
            printf("Preço: %.2f\n", preco);
            printf("----------------------------------------\n");
            encontrado = 1;
            break;
        }
    }
    fclose(arquivo);
    if (!encontrado) {
        printf("Produto com código %s não encontrado.\n", codigo);
    }
}

// Função para editar um produto pelo código de barras
void editar_produto(const char* codigo) {
    FILE* arquivo = fopen("produtos.txt", "r");
    FILE* temp = fopen("temp_produtos.txt", "w");
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];
    int encontrado = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        char cod[20], nome[50];
        float preco;
        sscanf(linha, "%19[^;];%49[^;];%f", cod, nome, &preco);
        if (strcmp(codigo, cod) == 0) {
            encontrado = 1;
            char novo_nome[50];
            float novo_preco;
            printf("Novo nome: ");
            getchar(); // Limpa buffer
            fgets(novo_nome, sizeof(novo_nome), stdin);
            novo_nome[strcspn(novo_nome, "\n")] = '\0';

            printf("Novo preço: ");
            scanf("%f", &novo_preco);

            fprintf(temp, "%s;%s;%.2f\n", cod, novo_nome, novo_preco);
        } else {
            fputs(linha, temp);
        }
    }
    fclose(arquivo);
    fclose(temp);

    remove("produtos.txt");
    rename("temp_produtos.txt", "produtos.txt");

    if (encontrado) {
        printf("Produto editado com sucesso.\n");
    } else {
        printf("Produto com código %s não encontrado.\n", codigo);
    }
}

// Função para deletar um produto pelo código de barras
void deletar_produto(const char* codigo) {
    FILE* arquivo = fopen("produtos.txt", "r");
    FILE* temp = fopen("temp_produtos.txt", "w");
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];
    int encontrado = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        char cod[20];
        sscanf(linha, "%19[^;]", cod);
        if (strcmp(codigo, cod) != 0) {
            fputs(linha, temp);
        } else {
            encontrado = 1;
        }
    }
    fclose(arquivo);
    fclose(temp);

    remove("produtos.txt");
    rename("temp_produtos.txt", "produtos.txt");

    if (encontrado) {
        printf("Produto deletado com sucesso.\n");
    } else {
        printf("Produto com código %s não encontrado.\n", codigo);
    }
}