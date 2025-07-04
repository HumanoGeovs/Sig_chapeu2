#include <stdio.h>
#include <string.h>
#include "pedidos.h"
#include "util.h"

// ==================== DEFINIÇÕES DE ARQUIVOS ====================
#define ARQ_PEDIDOS "data/pedidos.bin"

// Exemplo de função para salvar pedido (adicione se necessário)
void salvar_pedido(Pedido pedido) {
    FILE* arquivo = fopen(ARQ_PEDIDOS, "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pedidos.\n");
        return;
    }
    fwrite(&pedido, sizeof(Pedido), 1, arquivo);
    fclose(arquivo);
}

// Exemplo de função para listar pedidos (adicione se necessário)
void listar_pedidos(void) {
    FILE* arquivo = fopen(ARQ_PEDIDOS, "rb");
    if (arquivo == NULL) {
        printf("Nenhum pedido cadastrado.\n");
        return;
    }
    Pedido pedido;
    printf("Pedidos cadastrados:\n");
    while (fread(&pedido, sizeof(Pedido), 1, arquivo)) {
        printf("Código Produto: %s | Quantidade: %d | Cor/Estampa: %s\n",
               pedido.codigoProduto, pedido.quantidade, pedido.corEstampa);
        printf("----------------------------------------\n");
    }
    fclose(arquivo);
}

// Função para cadastrar pedido
int tela_cadastrar_pedido(Pedido* pedido) {
    printf("\nCódigo do Produto: ");
    fgets(pedido->codigoProduto, sizeof(pedido->codigoProduto), stdin);
    pedido->codigoProduto[strcspn(pedido->codigoProduto, "\n")] = '\0';

    // Aqui você pode validar se o código existe em produtos.bin, se desejar

    printf("Quantidade: ");
    scanf("%d", &pedido->quantidade);
    getchar();

    printf("Cor/Estampa: ");
    fgets(pedido->corEstampa, sizeof(pedido->corEstampa), stdin);
    pedido->corEstampa[strcspn(pedido->corEstampa, "\n")] = '\0';

    // Salva o pedido no arquivo binário
    salvar_pedido(*pedido);

    return 1; // sucesso
}