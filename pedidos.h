#ifndef PEDIDOS_H
#define PEDIDOS_H

typedef struct {
    char codigoProduto[20];
    int quantidade;
    char corEstampa[30];
} Pedido;

// Protótipo da função fora da struct:
int tela_cadastrar_pedido(Pedido* pedido);

#endif