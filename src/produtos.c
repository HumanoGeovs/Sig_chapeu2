#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produtos.h"
#include "util.h"

// ==================== DEFINIÇÕES E ESTRUTURAS ====================

typedef struct produto Produto;

// Estrutura para lista ligada de produtos
typedef struct produto_no {
    Produto produto;
    struct produto_no* prox;
} ProdutoNo;

// ==================== DEFINIÇÕES DE ARQUIVOS ====================
#define ARQ_PRODUTOS "data/produtos.bin"

// ==================== FUNÇÕES AUXILIARES ====================

// Validação de nome (deve estar em util.h/.c)
extern int validarNomeProduto(const char* nome);

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
    FILE *arquivo = fopen(ARQ_PRODUTOS, "rb");
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

// ==================== FUNÇÕES DE ARQUIVO ====================

void salvar_produto(Produto produto) {
    FILE* arquivo = fopen(ARQ_PRODUTOS, "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar produto.\n");
        return;
    }
    fwrite(&produto, sizeof(Produto), 1, arquivo);
    fclose(arquivo);
}

// ==================== FUNÇÕES DE LISTA LIGADA ====================

void inserir_ordenado_preco(ProdutoNo** lista, Produto prod, int crescente) {
    ProdutoNo* novo = (ProdutoNo*) malloc(sizeof(ProdutoNo));
    novo->produto = prod;
    novo->prox = NULL;

    if (*lista == NULL) {
        *lista = novo;
    } else if ((crescente && prod.preco < (*lista)->produto.preco) ||
               (!crescente && prod.preco > (*lista)->produto.preco)) {
        novo->prox = *lista;
        *lista = novo;
    } else {
        ProdutoNo* atual = *lista;
        ProdutoNo* prox = (*lista)->prox;
        while (prox != NULL &&
              ((crescente && prox->produto.preco < prod.preco) ||
               (!crescente && prox->produto.preco > prod.preco))) {
            atual = prox;
            prox = prox->prox;
        }
        atual->prox = novo;
        novo->prox = prox;
    }
}

// ==================== FUNÇÕES DE PRODUTO (CRUD) ====================

// Cadastrar produto
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

// Pesquisar produto por código
void pesquisar_produto(const char* codigo) {
    FILE* arquivo = fopen(ARQ_PRODUTOS, "rb");
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

// Editar produto
void editar_produto(const char* codigo) {
    FILE* arquivo = fopen(ARQ_PRODUTOS, "r+b");
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

// Deletar produto
void deletar_produto(const char* codigo) {
    FILE* arquivo = fopen(ARQ_PRODUTOS, "r+b");
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

// ==================== TELAS DE INTERAÇÃO ====================

// Tela principal de produtos
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

// Tela de pesquisa de produtos
void tela_pesquisar_produto(void) {
    int opcao;

    printf("\n");
    printf("+============================================================================+\n");
    printf("|                       PESQUISA DE PRODUTOS - SIG CHAPEU                    |\n");
    printf("+============================================================================+\n");
    printf("|  1. Pesquisar Produto por Código de Barras                                 |\n");
    printf("|  2. Listar Todos os Produtos Cadastrados                                   |\n");
    printf("|  3. Listar Produtos por Preço (faixa e ordem)                              |\n");
    printf("|  0. Voltar ao Menu de Produtos                                             |\n");
    printf("+============================================================================+\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

    system("cls||clear");

    switch (opcao) {
        case 1:
            {
                char codigo[20];
                b_produto_por_codigo(codigo);
            }
            break;
        case 2:
            listar_produtos();
            break;
        case 3:
            listar_produtos_por_preco_menu();
            break;
        case 0:
            printf("Voltando ao menu principal...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
    }
}

// Tela de edição de produto
void tela_editar_produto(void) {
    char codigo[20];
    printf("\nDigite o código de barras do produto para editar: ");
    fgets(codigo, sizeof(codigo), stdin);
    codigo[strcspn(codigo, "\n")] = '\0';
    editar_produto(codigo);
    printf("Pressione ENTER para continuar...");
    getchar();
}

// Tela de deleção de produto
void tela_deletar_produto(void) {
    char codigo[20];
    printf("\nDigite o código de barras do produto para deletar: ");
    fgets(codigo, sizeof(codigo), stdin);
    codigo[strcspn(codigo, "\n")] = '\0';
    deletar_produto(codigo);
    printf("Pressione ENTER para continuar...");
    getchar();
}

// ==================== FUNÇÕES DE LISTAGEM E PESQUISA ====================

// Listar todos os produtos ativos (com paginação)
void listar_produtos(void) {
    FILE* arquivo = fopen(ARQ_PRODUTOS, "rb");
    if (arquivo == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    Produto produto;
    Produto produtos[1000]; // Array para armazenar os produtos
    int total_produtos = 0;

    // Carrega os produtos ativos no array
    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        if (produto.status == 1) {
            produtos[total_produtos++] = produto;
        }
    }
    fclose(arquivo);

    if (total_produtos == 0) {
        printf("Nenhum produto ativo cadastrado.\n");
        return;
    }

    int pagina_atual = 0;
    int total_paginas = (total_produtos + 11) / 12; // Calcula o número total de páginas

    while (1) {
        system("cls||clear");
        printf("\nProdutos cadastrados - Página %d de %d:\n", pagina_atual + 1, total_paginas);
        printf("-----------------------------------------------------\n");
        printf("%-15s | %-30s | %s\n", "Código de Barras", "Nome", "Preço");
        printf("-----------------------------------------------------\n");

        int inicio = pagina_atual * 12;
        int fim = inicio + 12;
        if (fim > total_produtos) fim = total_produtos;

        for (int i = inicio; i < fim; i++) {
            printf("%-15s | %-30s | %.2f\n", produtos[i].codigo, produtos[i].nome, produtos[i].preco);
        }

        printf("-----------------------------------------------------\n");

        if (total_paginas > 1) {
            printf("Aperte 1 para ir para a próxima página\n");
            printf("Aperte 2 para voltar para a página anterior\n");
        }
        printf("Aperte 0 para retornar\n");

        int opcao;
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 0) {
            break;
        } else if (opcao == 1 && pagina_atual < total_paginas - 1) {
            pagina_atual++;
        } else if (opcao == 2 && pagina_atual > 0) {
            pagina_atual--;
        } else {
            printf("Opção inválida! Tente novamente.\n");
            printf("Pressione ENTER para continuar...");
            getchar();
        }
    }
}

// Listar produtos por preço (faixa e ordem)
void listar_produtos_por_preco_menu() {
    char buffer[50];
    float preco_min = 0.0f, preco_max = 1e9f;
    int ordem = 1; // 1 = crescente, 0 = decrescente

    // Definir faixa de preço
    printf("Digite o preço mínimo (ENTER para não definir): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        preco_min = atof(buffer);
        if (preco_min < 0) preco_min = 0;
    }

    printf("Digite o preço máximo (ENTER para não definir): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        preco_max = atof(buffer);
        if (preco_max <= 0) preco_max = 1e9f;
    }

    // Definir ordem de exibição
    printf("Escolha a ordem de exibição:\n");
    printf("1. Crescente\n");
    printf("2. Decrescente\n");
    printf("0. Retornar ao menu anterior\n");
    printf("Opção: ");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] == '0') return;
    if (buffer[0] == '2') ordem = 0; // decrescente

    // Monta lista ordenada e exibe
    FILE* arquivo = fopen(ARQ_PRODUTOS, "rb");
    if (arquivo == NULL) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    Produto produto;
    ProdutoNo* lista = NULL;
    while (fread(&produto, sizeof(Produto), 1, arquivo)) {
        if (produto.status == 1 && produto.preco >= preco_min && produto.preco <= preco_max) {
            inserir_ordenado_preco(&lista, produto, ordem);
        }
    }
    fclose(arquivo);

    if (lista == NULL) {
        printf("Nenhum produto encontrado na faixa de preço informada.\n");
        printf("Pressione ENTER para continuar...");
        getchar();
        return;
    }

    printf("\nProdutos na faixa de preço %.2f a %.2f em ordem %s:\n",
           preco_min, preco_max == 1e9f ? 99999999.0f : preco_max,
           ordem ? "crescente" : "decrescente");
    printf("-----------------------------------------------------\n");
    printf("%-15s | %-30s | %s\n", "Código de Barras", "Nome", "Preço");
    printf("-----------------------------------------------------\n");

    ProdutoNo* atual = lista;
    while (atual != NULL) {
        printf("%-15s | %-30s | %.2f\n", atual->produto.codigo, atual->produto.nome, atual->produto.preco);
        atual = atual->prox;
    }
    printf("-----------------------------------------------------\n");
    printf("Pressione ENTER para continuar...");
    getchar();

    // Libera memória
    while (lista != NULL) {
        ProdutoNo* temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

// Pesquisar produto por código (tela)
void b_produto_por_codigo(char* codigo) {
    printf("\nDigite o código de barras do produto para pesquisar: ");
    fgets(codigo, 20, stdin); // Usa o parâmetro diretamente
    codigo[strcspn(codigo, "\n")] = '\0';
    pesquisar_produto(codigo);
    printf("Pressione ENTER para continuar...");
    getchar();
}

// ==================== FIM DO ARQUIVO ====================