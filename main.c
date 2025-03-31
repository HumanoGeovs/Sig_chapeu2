#include <stdio.h>
#include <locale.h>
 

 
/////
 
// Assinatura das funções
 
void tela_principal(void);
 
void tela_sobre(void);
 
void tela_equipe(void);

void tela_produtos(void);

void tela_cadastrar_produto(void);

void tela_pesquisar_produto(void);
 
void tela_editar_produto(void);

void tela_deletar_produto(void);

void tela_clientes(void);

void tela_cadastrar_cliente(void);

void tela_pesquisar_cliente(void);

void tela_editar_cliente(void);

void tela_deletar_cliente(void);

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

    tela_produtos();
        getchar();
        system("cls|clear");

    tela_cadastrar_produto();
        getchar();
        system("cls|clear");

    tela_pesquisar_produto();
        getchar();
        system("cls|clear");

    tela_editar_produto();
        getchar();
        system("cls|clear");

    tela_deletar_produto();
        getchar();
        system("cls|clear");

    tela_clientes();
        getchar();
        system("cls|clear");

    tela_cadastrar_cliente();
        getchar();
        system("cls|clear");

    tela_pesquisar_cliente();
        getchar();
        system("cls|clear");

    tela_editar_cliente();
        getchar();
        system("cls|clear");

    tela_deletar_cliente();
        getchar();
        system("cls|clear");

    return 0;
 
}
 

 

 
/////
 
// Funções
 

 
void tela_principal(void) {
 
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
    printf("///                                                                         ///\n");
    printf("///            1. Módulo Cliente                                            ///\n");
    printf("///            2. Módulo Produtos                                           ///\n");
    printf("///            3. Módulo Equipe                                             ///\n");
    printf("///            4. Módulo Encomendas                                         ///\n");
    printf("///            5. Módulo Relatórios                                         ///\n");
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
    printf("///  Programa visa facilitar encomendas e previsão de entregas  de uma      ///\n");
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


void tela_produtos(void) {
 
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
    printf("///                 = = = = = Gerenciar Produtos = = = = =                  ///\n");
    printf("///                                                                         ///\n");
    printf("///            1. Cadastrar produto                                         ///\n");
    printf("///            2. Pesquisar produto                                         ///\n");
    printf("///            3. Editar Produto                                            ///\n");
    printf("///            4. Deletar produto                                           ///\n");
    printf("///            0. Sair                                                      ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
 
}

void tela_cadastrar_produto(void) {
 
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Cadastrar Produto = = = = =                   ///\n");
    printf("///                                                                         ///\n");
    printf("///            Nome do Produto:                                             ///\n");
    printf("///            Código do Produto:                                           ///\n");
    printf("///            Descrição do Produto:                                        ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
 
}

void tela_pesquisar_produto(void) {
 
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Pesquisar Produto = = = = =                   ///\n");
    printf("///                                                                         ///\n");
    printf("///            Código do Produto:                                           ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");

}
void tela_editar_produto(void) {
 
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Editar Produto = = = = =                      ///\n");
    printf("///                                                                         ///\n");
    printf("///            Código do Produto:                                           ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");

}
void tela_deletar_produto(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Deletar Produto = = = = =                     ///\n");
    printf("///                                                                         ///\n");
    printf("///            Código do Produto:                                           ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
}

 
void tela_clientes(void) {
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
    printf("///                 = = = = = Gerenciar Clientes = = = = =                  ///\n");
    printf("///                                                                         ///\n");
    printf("///            1. Cadastrar Cliente                                         ///\n");
    printf("///            2. Pesquisar Cliente                                         ///\n");
    printf("///            3. Editar Cliente                                            ///\n");
    printf("///            4. Deletar Cliente                                           ///\n");
    printf("///            0. Sair                                                      ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
}

void tela_cadastrar_cliente(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Cadastrar Cliente = = = = =                   ///\n");
    printf("///                                                                         ///\n");
    printf("///            Nome do Cliente:                                             ///\n");
    printf("///            CPF do Cliente:                                              ///\n");
    printf("///            Telefone:                                                    ///\n");
    printf("///            Endereço:                                                    ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
}

void tela_pesquisar_cliente(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Pesquisar Cliente = = = = =                   ///\n");
    printf("///                                                                         ///\n");
    printf("///            CPF do Cliente:                                              ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
}

void tela_editar_cliente(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Editar Cliente = = = = =                      ///\n");
    printf("///                                                                         ///\n");
    printf("///            CPF do Cliente:                                              ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
}

void tela_deletar_cliente(void) {
    printf("\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("///                                                                         ///\n");
    printf("///                 = = = = = Deletar Cliente = = = = =                     ///\n");
    printf("///                                                                         ///\n");
    printf("///            CPF do Cliente:                                              ///\n");
    printf("///                                                                         ///\n");
    printf("///////////////////////////////////////////////////////////////////////////////\n");
    printf("-----------      pressione ENTER para ir para a proxima tela     --------------\n");
    printf("\n");
}