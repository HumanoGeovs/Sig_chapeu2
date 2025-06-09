///////////////////////////////////////////////////////////////////////////////
///								Módulo Utilitário
///////////////////////////////////////////////////////////////////////////////

#define True 1
#define False 0


void delay(int);
void limpaTela(void);
int ehDigito(char);
int ehLetra(char);
int ehBissexto(int);
int ehData(int, int, int);

int validarNome(char*);
int validarEmail(char*);
int validarData(char*);
int validarFone(char*);
int validarMatr(char*);
int validarNomeProduto(const char* nome);
int validarCPF(const char* cpf);
int validarDataEntrega(const char* data);