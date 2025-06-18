#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "util.h" 

typedef struct produto Produto;

void salvar_produto(Produto produto) {
    FILE* arquivo = fopen("produtos.bin", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar produto.\n");
        return;
    }
    fwrite(&produto, sizeof(Produto), 1, arquivo);
    fclose(arquivo);
}

void b_produto_por_codigo(char* codigo) {
    printf("\nDigite o código de barras do produto para pesquisar: ");
    fgets(codigo, 20, stdin); // Usa o parâmetro diretamente
    codigo[strcspn(codigo, "\n")] = '\0';
    pesquisar_produto(codigo);
    printf("Pressione ENTER para continuar...");
    getchar();
}

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
    FILE *arquivo = fopen("produtos.bin", "rb");
    int ultimo_codigo = 0;
    if (arquivo != NULL) {
        Produto produto;
        while (fread(&produto, sizeof(Produto), 1, arquivo)) {
            // O código do produto está nas posições 8 a 11 do código EAN-13
            char codigo_produto[5];
            strncpy(codigo_produto, produto.codigo + 8, 4);
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

    produto.status = 1; // Produto ativo ao cadastrar
    salvar_produto(produto);

    printf("Produto cadastrado e salvo com sucesso!\n");
}

void listar_produtos(void) {
    FILE* arquivo = fopen("produtos.bin", "rb");
    if (arquivo == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    Produto produto;
    printf("\nProdutos cadastrados:\n");
    printf("-----------------------------------------------------\n");
    printf("%-15s | %-30s | %s\n", "Código de Barras", "Nome", "Preço");
    printf("-----------------------------------------------------\n");
    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        if (produto.status == 1) { // Só mostra ativos
            printf("%-15s | %-30s | %.2f\n", produto.codigo, produto.nome, produto.preco);
        }
    }
    printf("-----------------------------------------------------\n");
    fclose(arquivo);
}

void tela_pesquisar_produto(void) {
    int opcao; // Declaração da variável opcao

    printf("\n");
    printf("+============================================================================+\n");
    printf("|                       PESQUISA DE PRODUTOS - SIG CHAPEU                    |\n");
    printf("+============================================================================+\n");
    printf("|  1. Pesquisar Produto por Código de Barras                                 |\n");
    printf("|  2. Listar Todos os Produtos Cadastrados                                   |\n");
    printf("|  0. Voltar ao Menu de Produtos                                              |\n");
    printf("+============================================================================+\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

    system("cls||clear");

    switch (opcao) {
        case 1:
            char codigo[20];
            b_produto_por_codigo(codigo);
            break;
        case 2:
            listar_produtos();
            break;
        case 0:
            printf("Voltando ao menu principal...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
    }

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
}// Função para pesquisar e exibir um produto pelo código de barras
void pesquisar_produto(const char* codigo) {
    FILE* arquivo = fopen("produtos.bin", "rb");
    if (arquivo == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    Produto produto;
    int encontrado = 0;
    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        if (strcmp(codigo, produto.codigo) == 0 && produto.status == 1) {
            printf("\nProduto encontrado:\n");
            printf("Código de Barras: %s\n", produto.codigo);
            printf("Nome: %s\n", produto.nome);
            printf("Preço: %.2f\n", produto.preco);
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
    FILE* arquivo = fopen("produtos.bin", "r+b");
    if (arquivo == NULL ) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Produto produto;
    int encontrado = 0;
    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        if (strcmp(codigo, produto.codigo) == 0 && produto.status == 1) {
            encontrado = 1;
            printf("Produto encontrado:\n");
            printf("Código de Barras: %s\n", produto.codigo);
            printf("Nome: %s\n", produto.nome);
            printf("Preço: %.2f\n", produto.preco);

            printf("\nDigite o novo nome do produto: ");
            fgets(produto.nome, sizeof(produto.nome), stdin);
            produto.nome[strcspn(produto.nome, "\n")] = '\0';

            if (!validarNomeProduto(produto.nome)) {
                printf("Nome inválido! Só pode conter letras, números e espaço. Tente novamente.\n");
                return;
            }

            printf("Digite o novo preço do produto: ");
            scanf("%f", &produto.preco);
            getchar();

            if (produto.preco <= 0) {
                printf("Preço inválido! Deve ser maior que zero. Tente novamente.\n");
                return;
            }

            fseek(arquivo, -1 * sizeof(Produto), SEEK_CUR);
            fwrite(&produto, sizeof(Produto), 1, arquivo);
            fflush(arquivo);
            break;
        }
    }
    fclose(arquivo);

    if (encontrado) {
        printf("Produto editado com sucesso.\n");
    } else {
        printf("Produto com código %s não encontrado.\n", codigo);
    }
}

// Função para deletar um produto pelo código de barras
void deletar_produto(const char* codigo) {
    FILE* arquivo = fopen("produtos.bin", "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Produto produto;
    int encontrado = 0;
    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        if (strcmp(codigo, produto.codigo) == 0 && produto.status == 1) {
            produto.status = 0; // Marca como inativo
            fseek(arquivo, -1 * sizeof(Produto), SEEK_CUR);
            fwrite(&produto, sizeof(Produto), 1, arquivo);
            encontrado = 1;
            break;
        }
    }
    fclose(arquivo);

    if (encontrado) {
        printf("Produto deletado com sucesso.\n");
    } else {
        printf("Produto com código %s não encontrado.\n", codigo);
    }
}