#include <stdio.h>
#include <locale.h>
 

 
/////
 
// Assinatura das funções
 
void tela_principal(void);
 
void tela_sobre(void);
 
void tela_equipe(void);

void tela_produtos(void);

void tela_cadastrar_produto(void);
 

 
/////
 
// Programa principal
 
int main(void) {
    setlocale(LC_ALL, "Portuguese_Brazil");
    tela_principal();
        getchar();
    tela_sobre();
        getchar();
    tela_equipe();
        getchar();
    tela_produtos();
        getchar();
    tela_cadastrar_produto();
        getchar();
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
    printf("///            2. Módulo Administrador                                      ///\n");
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
    printf("///               Departamento de Computação e Tecnologia                   ///\n");
    printf("///                  Disciplina DCT1106 -- Programação                      ///\n");
    printf("///                          Projeto Sig-Chapéu                             ///\n");
    printf("///             Developed by @name.is.marco -- since Mar, 2023              ///\n");
    printf("///               Projeto Sistema de Gestão de Chapelaria                   ///\n");
    printf("///                  Developed by @HumanoGeovs- 2025.1                      ///\n");
    printf("///                                                                         ///\n");
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