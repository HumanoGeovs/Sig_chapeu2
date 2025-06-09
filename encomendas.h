#ifndef ENCOMENDAS_H
#define ENCOMENDAS_H
#include "pedidos.h"

typedef struct {
    char codigoEncomenda[25];
    char cpfCliente[15];
    char dataEntrega[9];
    Pedido pedidos[20];
    int numPedidos;
} Encomenda;

void tela_cadastrar_encomenda(void);
void tela_ver_encomendas(void);
void tela_editar_encomenda(void);
void tela_deletar_encomenda(void);

#endif
