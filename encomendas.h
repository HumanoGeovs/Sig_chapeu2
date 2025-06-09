#ifndef ENCOMENDAS_H
#define ENCOMENDAS_H

typedef struct encomenda Encomenda;
struct encomenda {
    char cpfCliente[15];
    char codigoEncomenda[20];
    char dataEntrega[9];
};


void tela_encomendas(void);
void tela_cadastrar_encomenda(void);
void tela_pesquisar_encomenda(void);
void tela_editar_encomenda(void);
void tela_deletar_encomenda(void);
void tela_ver_encomendas(void);

#endif
