#include <stdio.h>
#include <stdlib.h>
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

void tela_cadastrar_produto(void) {
    Produto produto;

    printf("\nNome do Produto: ");
    fgets(produto.nome, sizeof(produto.nome), stdin);
    produto.nome[strcspn(produto.nome, "\n")] = '\0'; // Remove o '\n'

    if (!validarNomeProdutoOuCliente(produto.nome)) { // Valida o nome do produto
        printf("Nome inválido! Deve conter apenas letras. Tente novamente.\n");
        return;
    }

    printf("Código do Produto: ");
    fgets(produto.codigo, sizeof(produto.codigo), stdin);
    produto.codigo[strcspn(produto.codigo, "\n")] = '\0'; // Remove o '\n'

    if (!validarCodigo(produto.codigo)) { // Valida o código do produto
        printf("Código inválido! Deve conter apenas números. Tente novamente.\n");
        return;
    }

    printf("Preço do Produto: ");
    scanf("%f", &produto.preco);
    getchar(); // Limpa o buffer do teclado

    if (produto.preco <= 0) { // Valida o preço do produto
        printf("Preço inválido! Deve ser maior que zero. Tente novamente.\n");
        return;
    }

    printf("Produto validado com sucesso! (Salvamento será implementado futuramente)\n");
}

void tela_pesquisar_produto(void) {
    printf("\n");
    printf("+============================================================================+\n");
    printf("|                    PESQUISAR PRODUTO - SIG CHAPEU                         |\n");
    printf("+============================================================================+\n");
    printf("| Informe o código do produto para pesquisar:                                |\n");
    printf("+----------------------------------------------------------------------------+\n");
    printf("| Código do Produto:                                                         |\n");
    printf("+============================================================================+\n");
    printf("Pressione ENTER para ir para a próxima tela...\n");
    getchar();
}

void tela_editar_produto(void) {
    printf("\n");
    printf("+============================================================================+\n");
    printf("|                      EDITAR PRODUTO - SIG CHAPEU                          |\n");
    printf("+============================================================================+\n");
    printf("| Informe o código do produto para editar:                                   |\n");
    printf("+----------------------------------------------------------------------------+\n");
    printf("| Código do Produto:                                                         |\n");
    printf("+============================================================================+\n");
    printf("Pressione ENTER para ir para a próxima tela...\n");
    getchar();
}

void tela_deletar_produto(void) {
    printf("\n");
    printf("+============================================================================+\n");
    printf("|                     DELETAR PRODUTO - SIG CHAPEU                          |\n");
    printf("+============================================================================+\n");
    printf("| Informe o código do produto para deletar:                                  |\n");
    printf("+----------------------------------------------------------------------------+\n");
    printf("| Código do Produto:                                                         |\n");
    printf("+============================================================================+\n");
    printf("Pressione ENTER para ir para a próxima tela...\n");
    getchar();
}