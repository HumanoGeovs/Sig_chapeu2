#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "clientes.h"
#include "produtos.h" // Adicionado
#include "encomendas.h"
 

 
/////
 
// Assinatura das funções
 
void tela_principal(void);
 
void tela_sobre(void);
 
void tela_equipe(void);
 
void tela_integrantes(void); // Adicione a assinatura

/////

 
// Programa principal
 
int main(void) {
    setlocale(LC_ALL, "Portuguese_Brazil");
    system("cls||clear"); // Limpa a tela no início do programa
    tela_principal();
        getchar();
        system("cls|clear");

    return 0;
 
}
 

 
/////
 
// Funções
 

 
void tela_principal(void) {
    int opcao;  // Variável para armazenar a escolha do usuário

    do {
        printf("\n");
        printf("+============================================================================+\n");
        printf("|                SISTEMA DE GESTAO DE CHAPELARIA - SIG CHAPEU                |\n");
        printf("+============================================================================+\n");
        printf("|  1. Cliente      |  2. Produtos     |  3. Encomendas                       |\n");
        printf("|------------------+------------------+--------------------------------------|\n");
        printf("|  4. Equipe       |  5. Sobre        |  0. Sair                             |\n");
        printf("+============================================================================+\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao); // Captura a entrada do usuário
        getchar(); // Limpa o buffer do teclado

        system("cls||clear"); // Limpa a tela

        switch (opcao) {
            case 1:
                tela_clientes(); // Chama a função de clientes
                break;
            case 2:
                tela_produtos(); // Chama a função de produtos
                break;
            case 3:
                tela_encomendas(); // Chama a função de encomendas
                break;
            case 4:
                tela_equipe(); // Chama a função de equipe
                break;
            case 5:
                tela_sobre(); // Chama a função de sobre
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para voltar ao menu principal...");
            getchar(); // Aguarda o usuário pressionar ENTER
        }

        system("cls||clear"); // Limpa a tela antes de exibir o menu novamente
    } while (opcao != 0);
}
 

 

 
void tela_sobre(void) {
    printf("\n");
    printf("+============================================================================+\n");
    printf("|                        SOBRE O PROJETO SIG CHAPEU                          |\n");
    printf("+============================================================================+\n");
    printf("| Departamento de Computação e Tecnologia                                    |\n");
    printf("| Disciplina DCT1106 -- Programação                                          |\n");
    printf("| Projeto Sig-Chapéu                                                         |\n");
    printf("| Projeto Sistema de Gestão de Chapelaria                                    |\n");
    printf("| Desenvolvido por @HumanoGeovs - 2025.1                                     |\n");
    printf("+----------------------------------------------------------------------------+\n");
    printf("| = = = = = Sistema de Gestão de Chapelaria = = = = =                        |\n");
    printf("|                                                                            |\n");
    printf("| O programa visa facilitar encomendas e previsão de entregas de uma         |\n");
    printf("| chapelaria ou estabelecimentos semelhantes, facilitando para clientes      |\n");
    printf("| e funcionários.                                                            |\n");
    printf("+============================================================================+\n");
    printf("Pressione ENTER para ir para a próxima tela...\n");
    getchar();
    system("cls||clear");
}

void tela_equipe(void) {
    printf("\n");
    printf("+============================================================================+\n");
    printf("|                              EQUIPE DO PROJETO                             |\n");
    printf("+============================================================================+\n");
    printf("| Departamento de Computação e Tecnologia                                    |\n");
    printf("| Disciplina DCT1106 -- Programação                                          |\n");
    printf("| Projeto Sig-Chapéu                                                         |\n");
    printf("| Projeto Sistema de Gestão de Chapelaria                                    |\n");
    printf("| Desenvolvido por @HumanoGeovs - 2025.1                                     |\n");
    printf("+----------------------------------------------------------------------------+\n");
    printf("| Este projeto foi desenvolvido por:                                         |\n");
    printf("|   Marco Geovane Araújo                                                     |\n");
    printf("|   E-mail: marcogeovane71@gmail.com                                         |\n");
    printf("|   Redes sociais: @Name.Is.Marco                                            |\n");
    printf("|   Git: github.com/HumanoGeovs/Sig_chapeu2.git                              |\n");
    printf("+============================================================================+\n");
    printf("Pressione ENTER para ir para a próxima tela...\n");
    getchar();
    system("cls||clear");
    tela_integrantes(); // Chama a nova tela
}

void tela_integrantes(void) {
    printf("\n");
    printf("+============================================================================+\n");
    printf("| Referência de código utilizada:                                            |\n");
    printf("|   Autor: isasalmeron                                                       |\n");
    printf("|   Repositório: github.com/isasalmeron/arvore-b                             |\n");
    printf("|   Trecho utilizado: Validação de nome (letras, números e espaço)           |\n");
    printf("+============================================================================+\n");
    printf("Pressione ENTER para voltar ao menu principal...\n");
    getchar();
    system("cls||clear");
}