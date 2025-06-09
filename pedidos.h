#ifndef PEDIDOS_H
#define PEDIDOS_H

typedef struct pedido {
    char codigoProduto[20];
    int quantidade;
    char corEstampa[30];
} Pedido;

int tela_cadastrar_pedido(Pedido* pedido);

#endif