#include <stdio.h>
#include <stdlib.h>
#include "produtos.h"
#include "util.h" // Adicionado para usar as funções de validação

void tela_produtos(void) {
    int opcao;
    do {
        printf("\n");
        printf("///////////////////////////////////////////////////////////////////////////////\n");
        printf("///                                                                         ///\n");
        printf("///               Departamento de Computa??o e Tecnologia                   ///\n");
        printf("///                  Disciplina DCT1106 -- Programa??o                      ///\n");
        printf("///                          Projeto Sig-Chap?u                             ///\n");
        printf("///             Developed by @name.is.marco -- since Mar, 2023              ///\n");
        printf("///               Projeto Sistema de Gest?o de Chapelaria                   ///\n");
        printf("///                  Developed by @HumanoGeovs- 2025.1                      ///\n");
        printf("///                                                                         ///\n");
        printf("///////////////////////////////////////////////////////////////////////////////\n");
        printf("///                                                                         ///\n");
        printf("///                 = = = = = Gerenciar Produtos = = = = =                  ///\n");
        printf("///                                                                         ///\n");
        printf("///            1. Cadastrar produto                                         ///\n");
        printf("///            2. Pesquisar produto                                         ///\n");
        printf("///            3. Editar Produto                                            ///\n");
        printf("///            4. Deletar produto                                           ///\n");
        printf("///            0. Sair                                                      ///\n");
        printf("///                                                                         ///\n");
        printf("///////////////////////////////////////////////////////////////////////////////\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        system("cls||clear"); // Limpa a tela

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
            printf("Pressione ENTER para voltar ao menu de produtos...");
            getchar();
        }

        system("cls||clear");
    } while (opcao != 0);
}

void tela_cadastrar_produto(void) {
    char nome[50], codigo[20];

    printf("\nNome do Produto: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0'; // Remove o '\n'

    if (!validarNomeProdutoOuCliente(nome)) { // Valida o nome do produto
        printf("Nome inválido! Deve conter apenas letras. Tente novamente.\n");
        return;
    }

    printf("Código do Produto: ");
    fgets(codigo, sizeof(codigo), stdin);
    codigo[strcspn(codigo, "\n")] = '\0'; // Remove o '\n'

    if (!validarCodigo(codigo)) { // Valida o código do produto
        printf("Código inválido! Deve conter apenas números. Tente novamente.\n");
        return;
    }

    printf("Produto validado com sucesso! (Salvamento será implementado futuramente)\n");
}

void tela_pesquisar_produto(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Pesquisar Produto = = = = =                   ///\n");
    printf("///                                                                         ///\n");
    printf("///            C?digo do Produto:                                           ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
}

void tela_editar_produto(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Editar Produto = = = = =                      ///\n");
    printf("///                                                                         ///\n");
    printf("///            C?digo do Produto:                                           ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
}

void tela_deletar_produto(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Deletar Produto = = = = =                     ///\n");
    printf("///                                                                         ///\n");
    printf("///            C?digo do Produto:                                           ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
}