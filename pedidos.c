#include <stdio.h>
#include <string.h>
#include "pedidos.h"
#include "util.h"

int tela_cadastrar_pedido(Pedido* pedido) {
    printf("\nCódigo do Produto: ");
    fgets(pedido->codigoProduto, sizeof(pedido->codigoProduto), stdin);
    pedido->codigoProduto[strcspn(pedido->codigoProduto, "\n")] = '\0';

    // Aqui você pode validar se o código existe em produtos.txt, se desejar

    printf("Quantidade: ");
    scanf("%d", &pedido->quantidade);
    getchar();

    printf("Cor/Estampa: ");
    fgets(pedido->corEstampa, sizeof(pedido->corEstampa), stdin);
    pedido->corEstampa[strcspn(pedido->corEstampa, "\n")] = '\0';

    return 1; // sucesso
}