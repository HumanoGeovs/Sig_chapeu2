#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "util.h" // Adicionado para usar as funções de validação

typedef struct clientes Clientes;

// Função para salvar os dados de um cliente no arquivo "clientes.dat" (binário)
void salvar_cliente(const char* nome, const char* cpf, const char* telefone, const char* endereco) {
    Cliente cliente;
    strncpy(cliente.nome, nome, sizeof(cliente.nome));
    strncpy(cliente.cpf, cpf, sizeof(cliente.cpf));
    strncpy(cliente.telefone, telefone, sizeof(cliente.telefone));
    strncpy(cliente.endereco, endereco, sizeof(cliente.endereco));

    FILE* arquivo = fopen("clientes.bin", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }
    fwrite(&cliente, sizeof(Cliente), 1, arquivo);
    fclose(arquivo);
}

// Função para listar todos os clientes cadastrados (binário)
void listar_clientes(void) {
    FILE* arquivo = fopen("clientes.bin", "rb");
    if (arquivo == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    Cliente cliente;
    printf("Clientes cadastrados:\n");
    while (fread(&cliente, sizeof(Cliente), 1, arquivo)) {
        printf("Nome: %s | CPF: %s\n", cliente.nome, cliente.cpf);
        printf("Telefone: %s\n", cliente.telefone);
        printf("Endereço: %s\n", cliente.endereco);
        printf("----------------------------------------\n");
    }
    fclose(arquivo);
}

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

    salvar_cliente(cliente.nome, cliente.cpf, cliente.telefone, cliente.endereco); // Salva os dados do cliente
    printf("Cliente cadastrado com sucesso!\n");
}

// Tela para pesquisar clientes (lista todos os clientes)
void tela_pesquisar_cliente(void) {
    listar_clientes();
    printf("Pressione ENTER para continuar...");
    getchar();
}

// Função para deletar um cliente pelo CPF (binário)
void deletar_cliente(const char* cpf) {
    FILE* arquivo = fopen("clientes.bin", "rb");
    FILE* temp = fopen("temp_clientes.bin", "wb");
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cliente cliente;
    int encontrado = 0;
    while (fread(&cliente, sizeof(Cliente), 1, arquivo)) {
        if (strcmp(cpf, cliente.cpf) != 0) {
            fwrite(&cliente, sizeof(Cliente), 1, temp);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("clientes.bin");
    rename("temp_clientes.bin", "clientes.bin");

    if (encontrado) {
        printf("Cliente deletado com sucesso.\n");
    } else {
        printf("Cliente com CPF %s não encontrado.\n", cpf);
    }
}

// Função para editar os dados de um cliente pelo CPF (binário)
void editar_cliente(const char* cpf) {
    FILE* arquivo = fopen("clientes.bin", "rb");
    FILE* temp = fopen("temp_clientes.bin", "wb");
    if (arquivo == NULL || temp == NULL) {
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
        }
        fwrite(&cliente, sizeof(Cliente), 1, temp);
    }

    fclose(arquivo);
    fclose(temp);

    remove("clientes.bin");
    rename("temp_clientes.bin", "clientes.bin");

    if (encontrado) {
        printf("Cliente editado com sucesso.\n");
    } else {
        printf("Cliente com CPF %s não encontrado.\n", cpf);
    }
}

// Tela para editar um cliente
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
