#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"
#include "util.h" // Adicionado para usar as funções de validação

typedef struct clientes Clientes;

// Função para salvar os dados de um cliente no arquivo "clientes.txt"
void salvar_cliente(const char* nome, const char* cpf, const char* telefone, const char* endereco) {
    FILE* arquivo = fopen("clientes.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }
    fprintf(arquivo, "%s;%s;%s;%s\n", nome, cpf, telefone, endereco); // Salva os dados no formato CSV
    fclose(arquivo);
}

// Função para listar todos os clientes cadastrados
void listar_clientes(void) {
    FILE* arquivo = fopen("clientes.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    char linha[256];
    printf("Clientes cadastrados:\n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        char nome[50], cpf[15], telefone[15], endereco[100];
        sscanf(linha, "%49[^;];%14[^;];%14[^;];%99[^\n]", nome, cpf, telefone, endereco); // Extrai os dados do cliente
        printf("Nome: %s | CPF: %s\n", nome, cpf); // Exibe o nome e o CPF
        printf("Telefone: %s\n", telefone);        // Exibe o telefone
        printf("Endereço: %s\n", endereco);        // Exibe o endereço
        printf("----------------------------------------\n"); // Separador entre clientes
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

// Função para deletar um cliente pelo CPF
void deletar_cliente(const char* cpf) {
    FILE* arquivo = fopen("clientes.txt", "r");
    FILE* temp = fopen("temp_clientes.txt", "w");
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];
    int encontrado = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        char cpf_atual[15];
        sscanf(linha, "%*[^;];%14[^;]", cpf_atual); // Lê o CPF do cliente
        if (strcmp(cpf, cpf_atual) != 0) {
            fputs(linha, temp); // Escreve no arquivo temporário se o CPF não corresponder
        } else {
            encontrado = 1; // Marca que o cliente foi encontrado
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("clientes.txt"); // Remove o arquivo original
    rename("temp_clientes.txt", "clientes.txt"); // Renomeia o arquivo temporário

    if (encontrado) {
        printf("Cliente deletado com sucesso.\n");
    } else {
        printf("Cliente com CPF %s não encontrado.\n", cpf);
    }
}

// Função para editar os dados de um cliente pelo CPF
void editar_cliente(const char* cpf) {
    FILE* arquivo = fopen("clientes.txt", "r");
    FILE* temp = fopen("temp_clientes.txt", "w");
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[256];
    int encontrado = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        char cpf_atual[15];
        sscanf(linha, "%*[^;];%14[^;]", cpf_atual); // Lê o CPF do cliente
        if (strcmp(cpf, cpf_atual) == 0) {
            encontrado = 1;
            char nome[50], telefone[15], endereco[100];
            printf("Novo nome: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';

            if (strlen(nome) == 0) {
                printf("Nome não pode estar vazio. Tente novamente.\n");
                fclose(arquivo);
                fclose(temp);
                remove("temp_clientes.txt");
                return;
            }

            printf("Novo telefone: ");
            fgets(telefone, sizeof(telefone), stdin);
            telefone[strcspn(telefone, "\n")] = '\0';

            if (strlen(telefone) == 0) {
                printf("Telefone não pode estar vazio. Tente novamente.\n");
                fclose(arquivo);
                fclose(temp);
                remove("temp_clientes.txt");
                return;
            }

            printf("Novo endereço: ");
            fgets(endereco, sizeof(endereco), stdin);
            endereco[strcspn(endereco, "\n")] = '\0';

            if (strlen(endereco) == 0) {
                printf("Endereço não pode estar vazio. Tente novamente.\n");
                fclose(arquivo);
                fclose(temp);
                remove("temp_clientes.txt");
                return;
            }

            fprintf(temp, "%s;%s;%s;%s\n", nome, cpf, telefone, endereco); // Salva os novos dados
        } else {
            fputs(linha, temp); // Escreve no arquivo temporário se o CPF não corresponder
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("clientes.txt");
    rename("temp_clientes.txt", "clientes.txt");

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
