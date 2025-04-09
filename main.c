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
        printf("///////////////////////////////////////////////////////////////////////////////\n");
        printf("///                                                                         ///\n");
        printf("///               Departamento de Computação e Tecnologia                   ///\n");
        printf("///                  Disciplina DCT1106 -- Programação                      ///\n");
        printf("///                          Projeto Sig-Chapéu                             ///\n");
        printf("///             Developed by @name.is.marco -- since Mar, 2023              ///\n");
        printf("///               Projeto Sistema de Gestão de Chapelaria                   ///\n");
        printf("///                  Developed by @HumanoGeovs- 2025.1                      ///\n");
        printf("///                                                                         ///\n");
        printf("///////////////////////////////////////////////////////////////////////////////\n");
        printf("///                                                                         ///\n");
        printf("///            1. Cliente                                                   ///\n");
        printf("///            2. Produtos                                                  ///\n");
        printf("///            3. Encomendas                                                ///\n");
        printf("///            4. Equipe                                                    ///\n");
        printf("///            5. Sobre                                                     ///\n");
        printf("///            0. Sair                                                      ///\n");
        printf("///                                                                         ///\n");
        printf("///////////////////////////////////////////////////////////////////////////////\n");
        printf("Digite sua opção: ");
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
            printf("Pressione ENTER para voltar ao menu principal...");
            getchar(); // Aguarda o usuário pressionar ENTER
        }

        system("cls||clear"); // Limpa a tela antes de exibir o menu novamente
    } while (opcao != 0);
}
 

 

 
void tela_sobre(void) {

    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///               Departamento de Computação e Tecnologia                   ///\n");
    printf("///                  Disciplina DCT1106 -- Programação                      ///\n");
    printf("///                          Projeto Sig-Chapéu                             ///\n");
    printf("///             Developed by @name.is.marco -- since Mar, 2023              ///\n");
    printf("///               Projeto Sistema de Gestão de Chapelaria                   ///\n");
    printf("///                  Developed by @HumanoGeovs- 2025.1                      ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///         = = = = = Sistema de Gestão de Chapelaria = = = = =             ///\n");
    printf("///                                                                         ///\n");
    printf("///  Programa visa facilitar encomendas e previsão de entregas de uma       ///\n");
    printf("///  Chapelaria ou estabelecimentos semelhantes que trabalhem com este ou   ///\n");
    printf("///  outro tipo de produto, para assim facilitar tanto para o cliente quanto///\n");
    printf("///  para os funcionários da chapelaria ou semelhante.                      ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
 
    printf("\n");
 
}
 

 
 
void tela_equipe(void) {
 
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///               Departamento de Computação e Tecnologia                   ///\n");
    printf("///                  Disciplina DCT1106 -- Programação                      ///\n");
    printf("///                          Projeto Sig-Chapéu                             ///\n");
    printf("///             Developed by @name.is.marco -- since Mar, 2023              ///\n");
    printf("///               Projeto Sistema de Gestão de Chapelaria                   ///\n");
    printf("///                  Developed by @HumanoGeovs- 2025.1                      ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");;
    printf("///            Este projeto foi desenvolvido por:                           ///\n");
    printf("///                                                                         ///\n");
    printf("///            Marco Geovane Araújo                                         ///\n");
    printf("///            E-mail: marcogeovane71@gmail.com                             ///\n");
    printf("///            Redes sociais: @Name.Is.Marco                                ///\n");
    printf("///            Git: https://github.com/HumanoGeovs/Sig_chapeu2.git          ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
}