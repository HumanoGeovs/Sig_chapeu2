#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "encomendas.h"
#include "util.h"
#include "pedidos.h" // já traz a struct Pedido
#define ENCOMENDAS_POR_PAGINA 3

void gerarCodigoEncomenda(char* codigo, size_t tamanho) {
    time_t agora = time(NULL);
    struct tm* tm_info = localtime(&agora);
    int aleatorio = rand() % 10000;
    snprintf(codigo, tamanho, "EC%04d%02d%02d%02d%02d%02d%04d",
        tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
        tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, aleatorio);
}

void tela_encomendas(void) {
    int opcao;
    do {
        printf("\n");
        printf("+============================================================================+\n");
        printf("|                     MENU DE ENCOMENDAS - SIG CHAPEU                       |\n");
        printf("+============================================================================+\n");
        printf("|  1. Cadastrar Encomenda                                                    |\n");
        printf("|  2. Ver Encomendas                                                         |\n");
        printf("|  3. Editar Encomenda                                                       |\n");
        printf("|  4. Deletar Encomenda                                                      |\n");
        printf("|  0. Voltar ao Menu Principal                                               |\n");
        printf("+============================================================================+\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        system("cls||clear");

        switch (opcao) {
            case 1:
                tela_cadastrar_encomenda();
                break;
            case 2:
                tela_ver_encomendas();
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
            printf("\nPressione ENTER para voltar ao menu de encomendas...");
            getchar();
        }

        system("cls||clear");
    } while (opcao != 0);
}

void tela_cadastrar_encomenda(void) {
    Encomenda encomenda;
    Pedido pedidos[20];
    int numPedidos = 0;
    int adicionarMais = 1;
    FILE* arquivo;

    printf("\nCPF do Cliente: ");
    fgets(encomenda.cpfCliente, sizeof(encomenda.cpfCliente), stdin);
    encomenda.cpfCliente[strcspn(encomenda.cpfCliente, "\n")] = '\0';

    if (!validarCPF(encomenda.cpfCliente)) {
        printf("CPF inválido! Tente novamente.\n");
        return;
    }

    while (adicionarMais && numPedidos < 20) {
        if (tela_cadastrar_pedido(&pedidos[numPedidos])) {
            numPedidos++;
        } else {
            printf("Erro ao cadastrar pedido.\n");
            return;
        }
        printf("Adicionar mais um pedido à sua encomenda? (1-Sim / 0-Não): ");
        scanf("%d", &adicionarMais);
        getchar();
    }

    printf("Data de Entrega (ddmmaaaa): ");
    fgets(encomenda.dataEntrega, sizeof(encomenda.dataEntrega), stdin);
    encomenda.dataEntrega[strcspn(encomenda.dataEntrega, "\n")] = '\0';

    if (!validarDataEntrega(encomenda.dataEntrega)) {
        printf("Data inválida! Deve estar no formato ddmmaaaa e ser uma data válida. Tente novamente.\n");
        return;
    }

    gerarCodigoEncomenda(encomenda.codigoEncomenda, sizeof(encomenda.codigoEncomenda));

    // Salva no arquivo
    arquivo = fopen("encomendas.bin", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar encomenda.\n");
        return;
    }
    fwrite(&encomenda, sizeof(Encomenda), 1, arquivo);
    fclose(arquivo);

    printf("Encomenda cadastrada com sucesso!\nCódigo gerado: %s\n", encomenda.codigoEncomenda);
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
    char codigoBusca[25];
    printf("Digite o código da encomenda que deseja editar: ");
    fgets(codigoBusca, sizeof(codigoBusca), stdin);
    codigoBusca[strcspn(codigoBusca, "\n")] = '\0';

    FILE* arquivo = fopen("encomendas.bin", "rb");
    if (!arquivo) {
        printf("Nenhuma encomenda cadastrada.\n");
        return;
    }

    Encomenda encomendas[100];
    int total = 0, encontrada = 0;
    while (fread(&encomendas[total], sizeof(Encomenda), 1, arquivo)) {
        total++;
    }
    fclose(arquivo);

    for (int i = 0; i < total; i++) {
        if (strcmp(encomendas[i].codigoEncomenda, codigoBusca) == 0) {
            printf("Nova data de entrega (DDMMAAAA): ");
            fgets(encomendas[i].dataEntrega, sizeof(encomendas[i].dataEntrega), stdin);
            encomendas[i].dataEntrega[strcspn(encomendas[i].dataEntrega, "\n")] = '\0';
            encontrada = 1;
            break;
        }
    }

    if (!encontrada) {
        printf("Encomenda não encontrada.\n");
        return;
    }

    arquivo = fopen("encomendas.bin", "wb");
    if (!arquivo) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    fwrite(encomendas, sizeof(Encomenda), total, arquivo);
    fclose(arquivo);
    printf("Data de entrega atualizada!\n");
}

void tela_deletar_encomenda(void) {
    char codigoBusca[25];
    printf("Digite o código da encomenda que deseja deletar: ");
    fgets(codigoBusca, sizeof(codigoBusca), stdin);
    codigoBusca[strcspn(codigoBusca, "\n")] = '\0';

    FILE* arquivo = fopen("encomendas.bin", "rb");
    if (!arquivo) {
        printf("Nenhuma encomenda cadastrada.\n");
        return;
    }

    Encomenda encomendas[100];
    int total = 0, encontrada = 0;
    while (fread(&encomendas[total], sizeof(Encomenda), 1, arquivo)) {
        total++;
    }
    fclose(arquivo);

    int novoTotal = 0;
    for (int i = 0; i < total; i++) {
        if (strcmp(encomendas[i].codigoEncomenda, codigoBusca) != 0) {
            encomendas[novoTotal++] = encomendas[i];
        } else {
            encontrada = 1;
        }
    }

    if (!encontrada) {
        printf("Encomenda não encontrada.\n");
        return;
    }

    arquivo = fopen("encomendas.bin", "wb");
    if (!arquivo) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    fwrite(encomendas, sizeof(Encomenda), novoTotal, arquivo);
    fclose(arquivo);
    printf("Encomenda deletada!\n");
}

void tela_ver_encomendas(void) {
    FILE* arquivo = fopen("encomendas.bin", "rb");
    if (!arquivo) {
        printf("Nenhuma encomenda cadastrada.\n");
        return;
    }
    Encomenda encomenda;
    int encontrou = 0;
    while (fread(&encomenda, sizeof(Encomenda), 1, arquivo)) {
        encontrou = 1;
        printf("\n----------------------------------------\n");
        printf("Código: %s\n", encomenda.codigoEncomenda);
        printf("CPF Cliente: %s\n", encomenda.cpfCliente);
        printf("Data Entrega: %s\n", encomenda.dataEntrega);
        for (int i = 0; i < encomenda.numPedidos; i++) {
            printf("  Pedido %d: Produto: %s | Qtd: %d | Cor/Estampa: %s\n",
                i + 1,
                encomenda.pedidos[i].codigoProduto,
                encomenda.pedidos[i].quantidade,
                encomenda.pedidos[i].corEstampa
            );
        }
    }
    if (!encontrou) {
        printf("Nenhuma encomenda cadastrada.\n");
    }
    fclose(arquivo);
}
