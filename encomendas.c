#include <stdio.h>
#include <stdlib.h>
#include "encomendas.h"

void tela_encomendas(void) {
    int opcao;
    do {
        printf("\n");
        printf("///////////////////////////////////////////////////////////////////////////////\n");
        printf("///                                                                         ///\n");
        printf("///                 = = = = = Gerenciar Encomendas = = = = =                ///\n");
        printf("///                                                                         ///\n");
        printf("///            1. Cadastrar Encomenda                                       ///\n");
        printf("///            2. Pesquisar Encomenda                                       ///\n");
        printf("///            3. Editar Encomenda                                          ///\n");
        printf("///            4. Deletar Encomenda                                         ///\n");
        printf("///            0. Sair                                                      ///\n");
        printf("///                                                                         ///\n");
        printf("///////////////////////////////////////////////////////////////////////////////\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        system("cls||clear"); // Limpa a tela

        switch (opcao) {
            case 1:
                tela_cadastrar_encomenda();
                break;
            case 2:
                tela_pesquisar_encomenda();
                break;
            case 3:
                tela_editar_encomenda();
                break;
            case 4:
                tela_deletar_encomenda();
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            printf("Pressione ENTER para voltar ao menu de encomendas...");
            getchar();
        }

        system("cls||clear");
    } while (opcao != 0);
}

void tela_cadastrar_encomenda(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Cadastrar Encomenda = = = = =                 ///\n");
    printf("///                                                                         ///\n");
    printf("///            Nome do Cliente:                                             ///\n");
    printf("///            Código da Encomenda:                                         ///\n");
    printf("///            Descrição do Produto:                                        ///\n");
    printf("///            Data de Entrega:                                             ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
}

void tela_pesquisar_encomenda(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Pesquisar Encomenda = = = = =                 ///\n");
    printf("///                                                                         ///\n");
    printf("///            Código da Encomenda:                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
}

void tela_editar_encomenda(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Editar Encomenda = = = = =                    ///\n");
    printf("///                                                                         ///\n");
    printf("///            Código da Encomenda:                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
}

void tela_deletar_encomenda(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Deletar Encomenda = = = = =                   ///\n");
    printf("///                                                                         ///\n");
    printf("///            Código da Encomenda:                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
}
