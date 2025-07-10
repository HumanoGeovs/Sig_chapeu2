#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "clientes.h"
#include "produtos.h" // Adicionado
#include "encomendas.h"
#include <conio.h> // Para getch()


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
    system("mkdir -p data"); // Cria o diretório data se não existir
    tela_principal();
        getchar();
        system("cls|clear");

    return 0;
 
}
 

 
/////
 
// Funções
 

 
void tela_principal(void) {
    int opcao = 0;
    int tecla;

    const char* opcoes[] = {
        "Cliente",
        "Produtos",
        "Encomendas",
        "Equipe",
        "Sobre",
        "Sair"
    };
    int total = 6;

    do {
        system("cls||clear");
        printf("+============================================================================+\n");
        printf("|                SISTEMA DE GESTAO DE CHAPELARIA - SIG CHAPEU               |\n");
        printf("+============================================================================+\n");
        for (int i = 0; i < total; i++) {
            if (i == opcao)
                printf(" > %-70s <\n", opcoes[i]);
            else
                printf("   %-70s  \n", opcoes[i]);
        }
        printf("+============================================================================+\n");
        printf("Use as setas ↑ ↓ e ENTER para selecionar.\n");

        tecla = _getch();
        if (tecla == 224) {
            tecla = _getch();
            if (tecla == 72) { // Cima
                opcao = (opcao - 1 + total) % total;
            } else if (tecla == 80) { // Baixo
                opcao = (opcao + 1) % total;
            }
        }
    } while (tecla != 13); // ENTER

    system("cls||clear");
    switch (opcao) {
        case 0:
            tela_clientes();
            break;
        case 1:
            tela_produtos();
            break;
        case 2:
            tela_encomendas();
            break;
        case 3:
            tela_equipe();
            break;
        case 4:
            tela_sobre();
            break;
        case 5:
            printf("Saindo do programa...\n");
            return;
    }

    printf("\nPressione ENTER para voltar ao menu principal...");
    getchar();
    tela_principal(); // Retorna ao menu principal após a operação
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