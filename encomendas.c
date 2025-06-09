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
    arquivo = fopen("encomendas.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para salvar encomenda.\n");
        return;
    }
    fprintf(arquivo, "Código: %s\nCPF Cliente: %s\nData Entrega: %s\n", encomenda.codigoEncomenda, encomenda.cpfCliente, encomenda.dataEntrega);
    for (int i = 0; i < numPedidos; i++) {
        fprintf(arquivo, "Pedido %d: Código Produto: %s | Quantidade: %d | Cor/Estampa: %s\n", i+1, pedidos[i].codigoProduto, pedidos[i].quantidade, pedidos[i].corEstampa);
    }
    fprintf(arquivo, "-----------------------------\n");
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

    FILE* arquivo = fopen("encomendas.txt", "r");
    if (!arquivo) {
        printf("Nenhuma encomenda cadastrada.\nPressione ENTER para voltar...");
        getchar();
        return;
    }

    char linha[256];
    char encomendas[100][15][256];
    int totalEncomendas = 0, linhaAtual = 0;
    int encontrada = 0;

    // Lê todas as encomendas
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "-----------------------------")) {
            encomendas[totalEncomendas][linhaAtual][0] = '\0';
            totalEncomendas++;
            linhaAtual = 0;
        } else {
            strcpy(encomendas[totalEncomendas][linhaAtual], linha);
            linhaAtual++;
        }
    }
    fclose(arquivo);

    // Procura a encomenda pelo código
    for (int i = 0; i < totalEncomendas; i++) {
        char codigoLido[25] = {0};
        // Extrai o código da linha, assumindo que está no formato "Código: <codigo>\n"
        sscanf(encomendas[i][0], "Código: %24s", codigoLido);
        if (strcmp(codigoLido, codigoBusca) == 0) {
            // Encontrou exatamente o código
            encontrada = 1;
            printf("Encomenda encontrada:\n");
            for (int j = 0; encomendas[i][j][0] != '\0'; j++) {
                printf("%s", encomendas[i][j]);
            }
            printf("\nDigite a nova data de entrega (ddmmaaaa): ");
            char novaData[9];
            fgets(novaData, sizeof(novaData), stdin);
            novaData[strcspn(novaData, "\n")] = '\0';

            if (!validarDataEntrega(novaData)) {
                printf("Data inválida! Edição cancelada.\n");
                return;
            }

            // Atualiza a linha da data de entrega
            for (int j = 0; encomendas[i][j][0] != '\0'; j++) {
                if (strstr(encomendas[i][j], "Data Entrega:")) {
                    snprintf(encomendas[i][j], sizeof(encomendas[i][j]), "Data Entrega: %s\n", novaData);
                    break;
                }
            }
            printf("Data de entrega atualizada!\n");
            break;
        }
    }

    if (!encontrada) {
        printf("Encomenda não encontrada.\n");
        printf("Pressione ENTER para voltar...");
        getchar();
        return;
    }

    // Salva todas as encomendas de volta no arquivo
    arquivo = fopen("encomendas.txt", "w");
    for (int i = 0; i < totalEncomendas; i++) {
        for (int j = 0; encomendas[i][j][0] != '\0'; j++) {
            fputs(encomendas[i][j], arquivo);
        }
        fputs("-----------------------------\n", arquivo);
    }
    fclose(arquivo);
    printf("Pressione ENTER para voltar...");
    getchar();
}

void tela_deletar_encomenda(void) {
    char codigoBusca[25];
    printf("Digite o código da encomenda que deseja deletar: ");
    fgets(codigoBusca, sizeof(codigoBusca), stdin);
    codigoBusca[strcspn(codigoBusca, "\n")] = '\0';

    FILE* arquivo = fopen("encomendas.txt", "r");
    if (!arquivo) {
        printf("Nenhuma encomenda cadastrada.\nPressione ENTER para voltar...");
        getchar();
        return;
    }

    char linha[256];
    char encomendas[100][15][256];
    int totalEncomendas = 0, linhaAtual = 0;
    int encontrada = 0;

    // Lê todas as encomendas
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "-----------------------------")) {
            encomendas[totalEncomendas][linhaAtual][0] = '\0';
            totalEncomendas++;
            linhaAtual = 0;
        } else {
            strcpy(encomendas[totalEncomendas][linhaAtual], linha);
            linhaAtual++;
        }
    }
    fclose(arquivo);

    // Procura e remove a encomenda pelo código (comparação exata)
    for (int i = 0; i < totalEncomendas; i++) {
        char codigoLido[25] = {0};
        sscanf(encomendas[i][0], "Código: %24s", codigoLido);
        if (strcmp(codigoLido, codigoBusca) == 0) {
            encontrada = 1;
            encomendas[i][0][0] = '\0'; // marca como removida
            printf("Encomenda deletada!\n");
            break;
        }
    }

    if (!encontrada) {
        printf("Encomenda não encontrada.\n");
        printf("Pressione ENTER para voltar...");
        getchar();
        return;
    }

    // Salva todas as encomendas restantes no arquivo
    arquivo = fopen("encomendas.txt", "w");
    for (int i = 0; i < totalEncomendas; i++) {
        if (encomendas[i][0][0] == '\0') continue; // pula encomendas deletadas
        for (int j = 0; encomendas[i][j][0] != '\0'; j++) {
            fputs(encomendas[i][j], arquivo);
        }
        fputs("-----------------------------\n", arquivo);
    }
    fclose(arquivo);
    printf("Pressione ENTER para voltar...");
    getchar();
}

void tela_ver_encomendas(void) {
    FILE* arquivo = fopen("encomendas.txt", "r");
    if (!arquivo) {
        printf("Nenhuma encomenda cadastrada ainda.\n");
        printf("Pressione ENTER para voltar...");
        getchar();
        return;
    }

    char linha[256];
    char encomendas[100][15][256]; // até 100 encomendas, até 15 linhas por encomenda
    int totalEncomendas = 0, linhaAtual = 0;

    // Lê todas as encomendas do arquivo
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "-----------------------------")) {
            encomendas[totalEncomendas][linhaAtual][0] = '\0';
            totalEncomendas++;
            linhaAtual = 0;
        } else {
            strcpy(encomendas[totalEncomendas][linhaAtual], linha);
            linhaAtual++;
        }
    }
    fclose(arquivo);

    if (totalEncomendas == 0) {
        printf("Nenhuma encomenda cadastrada ainda.\n");
        printf("Pressione ENTER para voltar...");
        getchar();
        return;
    }

    int pagina = 0;
    int totalPaginas = (totalEncomendas + ENCOMENDAS_POR_PAGINA - 1) / ENCOMENDAS_POR_PAGINA;
    int opcao;

    do {
        system("cls||clear");
        printf("/////////////////////// LISTA DE ENCOMENDAS ///////////////////////\n");
        int inicio = pagina * ENCOMENDAS_POR_PAGINA;
        int fim = inicio + ENCOMENDAS_POR_PAGINA;
        if (fim > totalEncomendas) fim = totalEncomendas;

        for (int i = inicio; i < fim; i++) {
            printf("---------------------------------------------------------------\n");
            for (int j = 0; encomendas[i][j][0] != '\0'; j++) {
                printf("%s", encomendas[i][j]);
            }
        }
        printf("---------------------------------------------------------------\n");
        printf("Página %d de %d\n", pagina + 1, totalPaginas);
        printf("1 - Próxima página\n");
        printf("2 - Página anterior\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // consome o ENTER

        if (opcao == 1 && pagina < totalPaginas - 1) {
            pagina++;
        } else if (opcao == 2 && pagina > 0) {
            pagina--;
        } else if (opcao == 0) {
            break;
        }
    } while (1);
}
