#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "util.h" // Adicionado para usar as funções de validação

typedef struct clientes Clientes;

// Estrutura para lista ligada de clientes
typedef struct ClienteNo {
    Cliente cliente;
    struct ClienteNo* prox;
} ClienteNo;

// ==================== DEFINIÇÕES DE ARQUIVOS ====================
#define ARQ_CLIENTES "data/clientes.bin"

// ==================== FUNÇÕES AUXILIARES ====================

// Função auxiliar para inserir cliente em ordem alfabética na lista ligada
ClienteNo* inserir_ordenado(ClienteNo* head, Cliente cliente) {
    ClienteNo* novo = (ClienteNo*)malloc(sizeof(ClienteNo));
    novo->cliente = cliente;
    novo->prox = NULL;

    if (head == NULL || strcmp(cliente.nome, head->cliente.nome) < 0) {
        novo->prox = head;
        return novo;
    }

    ClienteNo* atual = head;
    while (atual->prox != NULL && strcmp(cliente.nome, atual->prox->cliente.nome) > 0) {
        atual = atual->prox;
    }
    novo->prox = atual->prox;
    atual->prox = novo;
    return head;
}

// Função auxiliar para verificar se CPF já existe
int cpf_existe(const char* cpf) {
    FILE* arquivo = fopen(ARQ_CLIENTES, "rb");
    if (arquivo == NULL) return 0;
    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente), 1, arquivo)) {
        if (cliente.status == 1 && strcmp(cliente.cpf, cpf) == 0) {
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}

// Função auxiliar para buscar cliente pelo índice na lista ordenada
Cliente buscar_cliente_por_indice(int indice) {
    FILE* arquivo = fopen(ARQ_CLIENTES, "rb");
    ClienteNo* lista = NULL;
    Cliente cliente, resultado;
    resultado.status = 0; // status 0 indica não encontrado
    int idx = 1;
    if (arquivo == NULL) return resultado;
    while (fread(&cliente, sizeof(Cliente), 1, arquivo)) {
        if (cliente.status == 1) {
            lista = inserir_ordenado(lista, cliente);
        }
    }
    fclose(arquivo);
    ClienteNo* atual = lista;
    while (atual != NULL) {
        if (idx == indice) {
            resultado = atual->cliente;
            break;
        }
        atual = atual->prox;
        idx++;
    }
    // Libera memória
    while (lista != NULL) {
        ClienteNo* temp = lista;
        lista = lista->prox;
        free(temp);
    }
    return resultado;
}

// ==================== FUNÇÕES DE ARQUIVO ====================

// Função para salvar os dados de um cliente no arquivo binário
void salvar_cliente(Cliente cliente) {
    FILE* arquivo = fopen(ARQ_CLIENTES, "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }
    fwrite(&cliente, sizeof(Cliente), 1, arquivo);
    fclose(arquivo);
}

// Função para listar todos os clientes cadastrados (binário)
void listar_clientes(void) {
    FILE* arquivo = fopen(ARQ_CLIENTES, "rb");
    if (arquivo == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    Cliente cliente;
    printf("Clientes cadastrados:\n");
    while (fread(&cliente, sizeof(Cliente), 1, arquivo)) {
        if (cliente.status == 1) {   
            printf("Nome: %s | CPF: %s\n", cliente.nome, cliente.cpf);
            printf("Telefone: %s\n", cliente.telefone);
            printf("Endereço: %s\n", cliente.endereco);
            printf("Status: %s\n", cliente.status ? "Ativo" : "Inativo");
            printf("----------------------------------------\n");
        }
    }
    fclose(arquivo);
}

// Função para exibir clientes em ordem alfabética, apenas nome e CPF, numerados
int listar_clientes_alfabetico_menu(void) {
    FILE* arquivo = fopen(ARQ_CLIENTES, "rb");
    if (arquivo == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return 0;
    }
    ClienteNo* lista = NULL;
    Cliente cliente;
    int total = 0;
    while (fread(&cliente, sizeof(Cliente), 1, arquivo)) {
        if (cliente.status == 1) {
            lista = inserir_ordenado(lista, cliente);
        }
    }
    fclose(arquivo);

    printf("Clientes cadastrados (ordem alfabética):\n");
    ClienteNo* atual = lista;
    int idx = 1;
    while (atual != NULL && idx <= 9) {
        printf("%d - Nome: %s | CPF: %s\n", idx, atual->cliente.nome, atual->cliente.cpf);
        atual = atual->prox;
        idx++;
    }
    total = idx - 1;

    // Libera a memória da lista
    while (lista != NULL) {
        ClienteNo* temp = lista;
        lista = lista->prox;
        free(temp);
    }
    return total;
}

// Função para deletar um cliente pelo CPF (binário)
void deletar_cliente(const char* cpf) {
    FILE* arquivo = fopen(ARQ_CLIENTES, "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cliente cliente;
    int encontrado = 0;
    while (fread(&cliente, sizeof(Cliente), 1, arquivo)) {
        if (strcmp(cpf, cliente.cpf) == 0 && cliente.status == 1) {
            cliente.status = 0; // Marca o cliente como deletado
            fseek(arquivo, -1 * sizeof(Cliente), SEEK_CUR); // Volta para o início do registro
            fwrite(&cliente, sizeof(Cliente), 1, arquivo);
            encontrado = 1;
            break; // Sai do loop após encontrar o cliente
        }
    }

    fclose(arquivo);
    
    if (encontrado) {
        printf("Cliente deletado com sucesso.\n");
    } else {
        printf("Cliente com CPF %s não encontrado.\n", cpf);
    }
}

// Função para editar os dados de um cliente pelo CPF (binário)
void editar_cliente(const char* cpf) {
    FILE* arquivo = fopen(ARQ_CLIENTES, "r+b");
    if (arquivo == NULL ) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cliente cliente;
    int encontrado = 0;
    while (fread(&cliente, sizeof(Cliente), 1, arquivo)) {
        if (strcmp(cpf, cliente.cpf) == 0) {
            encontrado = 1;
            printf("Novo nome: ");
            fgets(cliente.nome, sizeof(cliente.nome), stdin);
            cliente.nome[strcspn(cliente.nome, "\n")] = '\0';

            printf("Novo telefone: ");
            fgets(cliente.telefone, sizeof(cliente.telefone), stdin);
            cliente.telefone[strcspn(cliente.telefone, "\n")] = '\0';

            printf("Novo endereço: ");
            fgets(cliente.endereco, sizeof(cliente.endereco), stdin);
            cliente.endereco[strcspn(cliente.endereco, "\n")] = '\0';
            fseek(arquivo, -1*sizeof(Cliente), SEEK_CUR);
            fwrite(&cliente, sizeof(Cliente), 1, arquivo);
            break;
        }
    }
    fclose(arquivo);

    if (encontrado) {
        printf("Cliente editado com sucesso.\n");
    } else {
        printf("Cliente com CPF %s não encontrado.\n", cpf);
    }
}

// ==================== TELAS (INTERFACE) ====================

// Tela principal para gerenciar clientes
void tela_clientes(void) {
    int opcao;
    do {
        printf("\n");
        printf("+============================================================================+\n");
        printf("|                        MENU DE CLIENTES - SIG CHAPEU                      |\n");
        printf("+============================================================================+\n");
        printf("|  1. Cadastrar Cliente   |  2. Pesquisar Cliente   |  3. Editar Cliente     |\n");
        printf("|-------------------------+-------------------------+------------------------|\n");
        printf("|  4. Deletar Cliente     |  0. Voltar ao Menu Principal                     |\n");
        printf("+============================================================================+\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        system("cls||clear");

        // Executa a ação correspondente à opção escolhida
        switch (opcao) {
            case 1:
                tela_cadastrar_cliente();
                break;
            case 2:
                tela_pesquisar_cliente();
                break;
            case 3:
                tela_editar_cliente();
                break;
            case 4:
                tela_deletar_cliente();
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para voltar ao menu de clientes...");
            getchar();
        }

        system("cls||clear");
    } while (opcao != 0);
}

// Tela para cadastrar um novo cliente
void tela_cadastrar_cliente(void) {
    Cliente cliente;

    printf("\nNome do Cliente: ");
    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = '\0'; // Remove o '\n'

    if (!validarNome(cliente.nome)) { // Valida o nome
        printf("Nome inválido! Deve conter apenas letras. Tente novamente.\n");
        return;
    }

    printf("CPF do Cliente: ");
    fgets(cliente.cpf, sizeof(cliente.cpf), stdin);
    cliente.cpf[strcspn(cliente.cpf, "\n")] = '\0'; // Remove o '\n'

    // Verifica se CPF já está cadastrado
    if (cpf_existe(cliente.cpf)) {
        printf("CPF já cadastrado\n");
        return;
    }

    if (!validarMatr(cliente.cpf)) { // Valida o CPF (usando validarMatr como exemplo de validação numérica)
        printf("CPF inválido! Deve conter apenas dígitos e ter 11 caracteres. Tente novamente.\n");
        return;
    }

    printf("Telefone: ");
    fgets(cliente.telefone, sizeof(cliente.telefone), stdin);
    cliente.telefone[strcspn(cliente.telefone, "\n")] = '\0'; // Remove o '\n'

    if (!validarFone(cliente.telefone)) { // Valida o telefone
        printf("Telefone inválido! Deve conter exatamente 11 dígitos. Tente novamente.\n");
        return;
    }

    printf("Endereço: ");
    fgets(cliente.endereco, sizeof(cliente.endereco), stdin);
    cliente.endereco[strcspn(cliente.endereco, "\n")] = '\0'; // Remove o '\n'

    if (strlen(cliente.endereco) == 0) { // Verifica se o endereço foi preenchido
        printf("Endereço não pode estar vazio. Tente novamente.\n");
        return;
    }
    cliente.status = 1;
    salvar_cliente(cliente); // Salva os dados do cliente
    printf("Cliente cadastrado com sucesso!\n");
}

// Tela para pesquisar clientes (lista todos os clientes em ordem alfabética, numerados)
void tela_pesquisar_cliente(void) {
    int total, opcao;
    do {
        system("cls||clear");
        total = listar_clientes_alfabetico_menu();
        printf("0 - Voltar\n");
        printf("Escolha um cliente pelo número ou 0 para voltar: ");
        scanf("%d", &opcao);
        getchar();
        if (opcao == 0) {
            break;
        }
        if (opcao < 1 || opcao > total) {
            printf("Opção inválida! Tente novamente.\n");
            printf("Pressione ENTER para continuar...");
            getchar();
        } else {
            // Buscar e mostrar dados completos do cliente selecionado
            Cliente cliente = buscar_cliente_por_indice(opcao);
            if (cliente.status == 1) {
                printf("\n--- Dados do Cliente Selecionado ---\n");
                printf("Nome: %s\n", cliente.nome);
                printf("CPF: %s\n", cliente.cpf);
                printf("Telefone: %s\n", cliente.telefone);
                printf("Endereço: %s\n", cliente.endereco);
                printf("Status: %s\n", cliente.status ? "Ativo" : "Inativo");
                printf("------------------------------------\n");
                printf("1 - Editar Cliente\n");
                printf("2 - Deletar Cliente\n");
                printf("0 - Voltar\n");
                printf("Escolha uma opção: ");
                int acao;
                scanf("%d", &acao);
                getchar();
                if (acao == 1) {
                    // Chama tela de editar já com o CPF preenchido
                    editar_cliente(cliente.cpf);
                    printf("\nCliente alterado com sucesso!\n");
                    printf("Pressione ENTER para voltar ao menu de clientes...");
                    getchar();
                    return; // Volta ao menu de clientes
                } else if (acao == 2) {
                    // Chama tela de deletar já com o CPF preenchido
                    deletar_cliente(cliente.cpf);
                    printf("Pressione ENTER para continuar...");
                    getchar();
                }
                // Se acao == 0, apenas volta ao menu de pesquisa
            } else {
                printf("Cliente não encontrado.\n");
                printf("Pressione ENTER para continuar...");
                getchar();
            }
        }
    } while (1);
}

// Função para editar um cliente
void tela_editar_cliente(void) {
    char cpf[15];
    printf("Digite o CPF do cliente a ser editado: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0'; // Remove o '\n'

    editar_cliente(cpf);
}

// Tela para deletar um cliente
void tela_deletar_cliente(void) {
    char cpf[15];
    printf("Digite o CPF do cliente a ser deletado: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = '\0'; // Remove o '\n'

    deletar_cliente(cpf);
}
