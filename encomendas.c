#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "encomendas.h"
#include "util.h"
#include "pedidos.h" // já traz a struct Pedido
#include "clientes.h" // Adicione este include para acessar a struct Cliente
#define ENCOMENDAS_POR_PAGINA 3

void gerarCodigoEncomenda(char* codigo, size_t tamanho) {
    time_t agora = time(NULL);
    struct tm* tm_info = localtime(&agora);
    int aleatorio = rand() % 10000;
    snprintf(codigo, tamanho, "EC%04d%02d%02d%02d%02d%02d%04d",
        tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
        tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, aleatorio);
}

// Função auxiliar para buscar nome do cliente pelo CPF
char* buscar_nome_cliente_por_cpf(const char* cpf) {
    static char nome[50];
    FILE* arq = fopen("clientes.bin", "rb");
    if (!arq) {
        strcpy(nome, "Desconhecido");
        return nome;
    }
    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente), 1, arq)) {
        if (cliente.status == 1 && strcmp(cliente.cpf, cpf) == 0) {
            strncpy(nome, cliente.nome, sizeof(nome));
            nome[sizeof(nome)-1] = '\0';
            fclose(arq);
            return nome;
        }
    }
    fclose(arq);
    strcpy(nome, "Desconhecido");
    return nome;
}

// Função auxiliar para buscar nome do produto pelo código
char* buscar_nome_produto_por_codigo(const char* codigoProduto) {
    static char nomeProduto[50];
    FILE* arq = fopen("produtos.bin", "rb");
    if (!arq) {
        strcpy(nomeProduto, "Desconhecido");
        return nomeProduto;
    }
    struct produto {
        char nome[50];
        char codigo[20];
        float preco;
        int status;
    } produto;
    while (fread(&produto, sizeof(produto), 1, arq)) {
        // Remover a verificação de status
        if (strcmp(produto.codigo, codigoProduto) == 0) {
            strncpy(nomeProduto, produto.nome, sizeof(nomeProduto));
            nomeProduto[sizeof(nomeProduto)-1] = '\0';
            fclose(arq);
            return nomeProduto;
        }
    }
    fclose(arq);
    strcpy(nomeProduto, "Desconhecido");
    return nomeProduto;
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
        Pedido tempPedido;
        int prosseguir = 1;
        // Solicita código do produto e faz verificação antes de pedir outros dados
        do {
            printf("Código do Produto: ");
            fgets(tempPedido.codigoProduto, sizeof(tempPedido.codigoProduto), stdin);
            tempPedido.codigoProduto[strcspn(tempPedido.codigoProduto, "\n")] = '\0';

            char* nomeProduto = buscar_nome_produto_por_codigo(tempPedido.codigoProduto);
            if (strcmp(nomeProduto, "Desconhecido") == 0) {
                printf("ATENÇÃO: Produto não reconhecido!\n");
                printf("Deseja prosseguir mesmo assim? (1-Sim / 0-Não): ");
                scanf("%d", &prosseguir);
                getchar();
                if (!prosseguir) continue;
            } else {
                printf("Produto encontrado: %s\n", nomeProduto);
                printf("Deseja adicionar este produto? (1-Sim / 0-Não): ");
                scanf("%d", &prosseguir);
                getchar();
                if (!prosseguir) continue;
            }
            break;
        } while (1);

        // Agora pede os outros dados do pedido normalmente
        printf("Quantidade: ");
        scanf("%d", &tempPedido.quantidade);
        getchar();
        printf("Cor/Estampa: ");
        fgets(tempPedido.corEstampa, sizeof(tempPedido.corEstampa), stdin);
        tempPedido.corEstampa[strcspn(tempPedido.corEstampa, "\n")] = '\0';

        pedidos[numPedidos++] = tempPedido;

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
    encomenda.status = 1; // Encomenda ativa ao cadastrar

    // Antes de salvar:
    encomenda.numPedidos = numPedidos;
    for (int i = 0; i < numPedidos; i++) {
        encomenda.pedidos[i] = pedidos[i];
    }

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
        if (strcmp(encomendas[i].codigoEncomenda, codigoBusca) == 0 && encomendas[i].status == 1) {
            printf("Nova data de entrega (DDMMAAAA): ");
            fgets(encomendas[i].dataEntrega, sizeof(encomendas[i].dataEntrega), stdin);
            encomendas[i].dataEntrega[strcspn(encomendas[i].dataEntrega, "\n")] = '\0';
            encontrada = 1;
            break;
        }
    }

    if (!encontrada) {
        printf("Encomenda não encontrada ou está inativa.\n");
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

    FILE* arquivo = fopen("encomendas.bin", "r+b");
    if (!arquivo) {
        printf("Nenhuma encomenda cadastrada.\n");
        return;
    }

    Encomenda encomenda;
    int encontrada = 0;
    while (fread(&encomenda, sizeof(Encomenda), 1, arquivo)) {
        if (strcmp(encomenda.codigoEncomenda, codigoBusca) == 0 && encomenda.status == 1) {
            encomenda.status = 0; // Marca como inativa
            fseek(arquivo, -1 * (long)sizeof(Encomenda), SEEK_CUR);
            fwrite(&encomenda, sizeof(Encomenda), 1, arquivo);
            encontrada = 1;
            break;
        }
    }
    fclose(arquivo);

    if (encontrada) {
        printf("Encomenda deletada!\n");
    } else {
        printf("Encomenda não encontrada ou já está inativa.\n");
    }
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
        if (encomenda.status == 1) { // Só mostra ativas
            encontrou = 1;
            printf("\n----------------------------------------\n");
            printf("Código: %s\n", encomenda.codigoEncomenda);
            printf("Cliente: %s\n", buscar_nome_cliente_por_cpf(encomenda.cpfCliente)); // Exibe nome
            // Exibe data no formato dd/mm/aaaa
            if (strlen(encomenda.dataEntrega) == 8) {
                printf("Data Entrega: %.2s/%.2s/%.4s\n",
                    encomenda.dataEntrega,
                    encomenda.dataEntrega + 2,
                    encomenda.dataEntrega + 4
                );
            } else {
                printf("Data Entrega: %s\n", encomenda.dataEntrega);
            }
            for (int i = 0; i < encomenda.numPedidos; i++) {
                printf("  Pedido %d: Produto: %s | Qtd: %d | Cor/Estampa: %s\n",
                    i + 1,
                    buscar_nome_produto_por_codigo(encomenda.pedidos[i].codigoProduto),
                    encomenda.pedidos[i].quantidade,
                    encomenda.pedidos[i].corEstampa
                );
            }
        }
    }
    if (!encontrou) {
        printf("Nenhuma encomenda cadastrada.\n");
    }
    fclose(arquivo);
}
