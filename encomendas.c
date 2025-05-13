#include <stdio.h>
#include <stdlib.h>
#include "encomendas.h"
#include "util.h" 

typedef struct  encomenda Encomenda;

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
        getchar(); 

        system("cls||clear"); 

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
    Encomenda encomenda;

    printf("\nNome do Cliente: ");
    fgets(encomenda.nomeCliente, sizeof(encomenda.nomeCliente), stdin);
    encomenda.nomeCliente[strcspn(encomenda.nomeCliente, "\n")] = '\0'; // Remove o '\n'

    if (!validarNomeProdutoOuCliente(encomenda.nomeCliente)) { // Valida o nome do cliente
        printf("Nome inválido! Deve conter apenas letras. Tente novamente.\n");
        return;
    }

    printf("Código da Encomenda: ");
    fgets(encomenda.codigoEncomenda, sizeof(encomenda.codigoEncomenda), stdin);
    encomenda.codigoEncomenda[strcspn(encomenda.codigoEncomenda, "\n")] = '\0'; // Remove o '\n'

    if (!validarCodigo(encomenda.codigoEncomenda)) { // Valida o código da encomenda
        printf("Código inválido! Deve conter apenas números. Tente novamente.\n");
        return;
    }

    printf("Data de Entrega (ddmmaaaa): ");
    fgets(encomenda.dataEntrega, sizeof(encomenda.dataEntrega), stdin);
    encomenda.dataEntrega[strcspn(encomenda.dataEntrega, "\n")] = '\0';

    if (!validarDataEntrega(encomenda.dataEntrega)) {
        printf("Data inválida! Deve estar no formato ddmmaaaa e ser uma data válida. Tente novamente.\n");
        return;
    }

    printf("Encomenda validada com sucesso! (Salvamento será implementado futuramente)\n");
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
