#include <stdio.h>
#include <locale.h>
#include "clientes.h"
#include "produtos.h" // Adicionado

 

 
/////
 
// Assinatura das fun��es
 
void tela_principal(void);
 
void tela_sobre(void);
 
void tela_equipe(void);

void tela_encomendas(void);

void tela_cadastrar_encomenda(void);

void tela_pesquisar_encomenda(void);
 
void tela_editar_encomenda(void);

void tela_deletar_encomenda(void);

/////
 
// Programa principal
 
int main(void) {
    setlocale(LC_ALL, "Portuguese_Brazil");
    tela_principal();
        getchar();
        system("cls|clear");
        
    tela_sobre();
        getchar();
        system("cls|clear");

    tela_equipe();
        getchar();
        system("cls|clear");

    tela_encomendas();
        getchar();
        system("cls|clear");

    tela_cadastrar_encomenda();
        getchar();
        system("cls|clear");

    tela_pesquisar_encomenda();
        getchar();
        system("cls|clear");

    tela_editar_encomenda();
        getchar();
        system("cls|clear");

    tela_deletar_encomenda();
        getchar();
        system("cls|clear");

    return 0;
 
}
 

 
/////
 
// Fun??es
 

 
void tela_principal(void) {
 
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///               Departamento de Computa??o e Tecnologia                   ///\n");
    printf("///                  Disciplina DCT1106 -- Programa??o                      ///\n");
    printf("///                          Projeto Sig-Chap?u                             ///\n");
    printf("///             Developed by @name.is.marco -- since Mar, 2023              ///\n");
    printf("///               Projeto Sistema de Gest?o de Chapelaria                   ///\n");
    printf("///                  Developed by @HumanoGeovs- 2025.1                      ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///            1. Cliente                                                   ///\n");
    printf("///            2. Produtos                                                  ///\n");
    printf("///            3. Encomendas                                                ///\n");
    printf("///            4. Equipe                                                    ///\n");
    printf("///            5. Sobre                                                     ///\n");
    printf("///            0. Sair                                                      ///\n");
    printf("///                                                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
 
    printf("\n");
 
}
 

 

 
void tela_sobre(void) {

    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///               Departamento de Computa??o e Tecnologia                   ///\n");
    printf("///                  Disciplina DCT1106 -- Programa??o                      ///\n");
    printf("///                          Projeto Sig-Chap?u                             ///\n");
    printf("///             Developed by @name.is.marco -- since Mar, 2023              ///\n");
    printf("///               Projeto Sistema de Gest?o de Chapelaria                   ///\n");
    printf("///                  Developed by @HumanoGeovs- 2025.1                      ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///         = = = = = Sistema de Gest?o de Chapelaria = = = = =             ///\n");
    printf("///                                                                         ///\n");
    printf("///  Programa visa facilitar encomendas e previs?o de entregas  de uma      ///\n");
    printf("///  Chapelaria ou estabelecimentos semelhantes que trabalhem com este ou   ///\n");
    printf("///  outro tipo de produto, para assim facilitar tanto para o cliente quanto///\n");
    printf("///  para os funcionarios da chapelaria ou semelhante.                      ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
 
    printf("\n");
 
}
 

 
 
void tela_equipe(void) {
 
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///               Departamento de Computa??o e Tecnologia                   ///\n");
    printf("///                  Disciplina DCT1106 -- Programa??o                      ///\n");
    printf("///                          Projeto Sig-Chap?u                             ///\n");
    printf("///             Developed by @name.is.marco -- since Mar, 2023              ///\n");
    printf("///               Projeto Sistema de Gest?o de Chapelaria                   ///\n");
    printf("///                  Developed by @HumanoGeovs- 2025.1                      ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");;
    printf("///            Este projeto foi desenvolvido por:                           ///\n");
    printf("///                                                                         ///\n");
    printf("///            Marco Geovane Ara?jo                                         ///\n");
    printf("///            E-mail: marcogeovane71@gmail.com                             ///\n");
    printf("///            Redes sociais: @Name.Is.Marco                                ///\n");
    printf("///            Git: https://github.com/HumanoGeovs/Sig_chapeu2.git          ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
}

void tela_encomendas(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///               Departamento de Computa??o e Tecnologia                   ///\n");
    printf("///                  Disciplina DCT1106 -- Programa??o                      ///\n");
    printf("///                          Projeto Sig-Chap?u                             ///\n");
    printf("///             Developed by @name.is.marco -- since Mar, 2023              ///\n");
    printf("///               Projeto Sistema de Gest?o de Chapelaria                   ///\n");
    printf("///                  Developed by @HumanoGeovs- 2025.1                      ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Gerenciar Encomendas = = = = =                ///\n");
    printf("///                                                                         ///\n");
    printf("///            1. Cadastrar Encomenda                                       ///\n");
    printf("///            2. Pesquisar Encomenda                                       ///\n");
    printf("///            3. Editar Encomenda                                          ///\n");
    printf("///            4. Deletar Encomenda                                         ///\n");
    printf("///            0. Sair                                                      ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
}

void tela_cadastrar_encomenda(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Cadastrar Encomenda = = = = =                 ///\n");
    printf("///                                                                         ///\n");
    printf("///            Nome do Cliente:                                             ///\n");
    printf("///            C?digo da Encomenda:                                         ///\n");
    printf("///            Descri??o do Produto:                                        ///\n");
    printf("///            Data de Entrega:                                             ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
}

void tela_pesquisar_encomenda(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Pesquisar Encomenda = = = = =                 ///\n");
    printf("///                                                                         ///\n");
    printf("///            C?digo da Encomenda:                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
}

void tela_editar_encomenda(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Editar Encomenda = = = = =                    ///\n");
    printf("///                                                                         ///\n");
    printf("///            C?digo da Encomenda:                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
}

void tela_deletar_encomenda(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Deletar Encomenda = = = = =                   ///\n");
    printf("///                                                                         ///\n");
    printf("///            C?digo da Encomenda:                                         ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
}