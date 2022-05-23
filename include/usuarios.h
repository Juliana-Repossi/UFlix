#ifndef USUARIOS_H
#define USUARIOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "menu.h"
#include "historico.h"

#define TAM_USUA 10
#define TAM_LOGIN 15
#define TAM_SENHA 10
#define CTE_AUMENTO 2
#define CTE_AUMENTO2 10
#define CTE_AUMENTO3 50
//tamanho max de entrada de login e senha (real)
#define TAM_MAX 150


/**
  Representa o tipo de um usuario
*/
typedef struct
{
  char* login; //Login do usuario
  char* senha; //Senha do usuario
  char inativo; //Se está ou não inativo
}tUsuario;

/**
 * @brief Testa se a abertura do ponteiro de arquivo usuarios.csv foi feita com sucesso
 * Pré-Condição: Existencia do ponteiro de arquivo para usuarios.csv
 * Pós-condição: Impressão de mensagem de falha e finalização do programa se ponteiro == NULL
 * @param *newPointer  Ponteiro para arquivo usuarios.csv
*/
void testaAberturaUsuario(FILE* newPointer);

/**
 * @brief Testa se a abertura do ponteiro de arquivo inativos.csv foi feita com sucesso
 * Pré-Condição: Existencia do ponteiro de arquivo para inativos.csv
 * Pós-condição: Impressão de mensagem de falha e finalização do programa se ponteiro == NULL
 * @param *newPointer  Ponteiro para arquivo inativos.csv
*/
void testaAberturaInativos(FILE* newPointer);

/**
 * @brief Desaloca os membros da estrutura tUsuario
 * Pré-Condição: Existencia do ponteiro tUsuario 
 * Pós-condição: liberado da memória
 * @param *pu ponteiro tUsuario 
*/
void desalocaInternos(tUsuario *p);

/**
 * @brief Desaloca a estrutura tUsuario
 * Pré-Condição: Existencia do ponteiro tUsuario e o tamanho dele
 * Pós-condição: liberado da memória
 * @param *pu ponteiro tUsuario e o tam tamanho total dele
*/
void desalocaUsuario(tUsuario *pu, int tam);

/*Aloca dinamicamente estaço para login de TAM_LOGIN e de senha de TAM_SENHA*/
/**
 * @brief Aloca dinamicamente os menbros internos de tUsuario: login de TAM_LOGIN e senha de TAM_SENHA 
 * Pré-Condição: ponteiro do vetor de tUsuario válido
 * Pós-condição: Impressão de mensagem de falha e finalização do programa se ponteiro de login ou senha == NULL ou espaço devidamente allocado
 * @param *p ponteiro de array tUsuario allocado dinamicamente  
*/
void alocaUsuario(tUsuario *p);

/**
 * @brief Aloca dinamicamente um vetor de tam posicoes tUsuario e chama a funcao alocaUsuario para alocar membros internos 
 * Pré-Condição: quantidade de tamUsuarios a ser alocada 
 * Pós-condição: Impressão de mensagem de falha e finalização do programa se ponteiro == NULL  ou o ponteiro do endereço allocado em cas de sucesso
 * @param tam quantidade de tUsuario a ser alocado  
*/
tUsuario *allocaVetorUsuario(int tam);

/**
 * @brief Testa se a abertura do ponteiro de tUsuario foi feita com sucesso
 * Pré-Condição: Existencia do ponteiro de tUsuario
 * Pós-condição: Impressão de mensagem de falha e finalização do programa se ponteiro == NULL
 * @param *pp  Ponteiro do tUsuario
*/
void testaPonteiroUsuario(tUsuario *pp);

/**
 * @brief copia os dados(login e senha) de um ponteiro tUsuario para outro
 * Pré-Condição:Existencia de dois ponteiros tUsua validos
 * Pós-condição:dados copiados do primeiro para o segundo
 * @param *pu para o ponteiro tUsuario,*g para o ponteiro tUsuario
*/
void copiaDados(tUsuario *pu,tUsuario *g);

/**
 * @brief Realoca aumentando a estrutura tUsuario
 * Pré-Condição: Existencia do ponteiro tUsuario e do tamanho de usuarios no sistema
 * Pós-condição: um tUsuario maior que o anterior segundo o CTE_AUMENTO3, com todos os dados do antigo(usa a copiaDados) e este ultimo liberado da memoria
 * @param *pu para o ponteiro tUsuario e totalUsuario quantidade de usuarios no sitema
 return: o novo endereço do ponteiro tUsuario, e atualiza a nova quantidade maxima
*/
tUsuario *reallocUsuario(tUsuario *pu, int *totalUsuario);

/**
 * @brief Inicializa os valores inativos 
 * Pré-Condição: Existencia do ponteiro de arquivo para inativos.csv, do ponteiro tUsuario e do tamanho de usuarios no sistema
 * Pós-condição: inicializa com 0 caso o arquivo inativos.csv esteja vazio ou carrega as informacoes existentes (0 para ativo e 1 para inativo)
 * @param *pu para o ponteiro tUsuario, *a para ponteiro de arquivo inativos.csv e tamUsuarios quantidade de usu no sitema
*/
void preencheInativos(tUsuario *pu, FILE *a, int tamUsuarios);


/**
 * @brief Armazena a string login do arquivo na estrutura criada
 * Pré-Condição: Existencia do ponteiro de arquivo para usuarios.csv, do ponteiro tUsuario
 * Pós-condição: carrega um dado de login do arquivo para a estrutura dinamica tUsuario
 * @param *pu para o ponteiro tUsuario, *u para ponteiro de arquivo usuarios.csv 
*/
void leLogin(tUsuario *p, FILE *u,char aux);

/**
 * @brief Armazena a string senha do arquivo na estrutura criada
 * Pré-Condição: Existencia do ponteiro de arquivo para usuarios.csv, do ponteiro tUsuario
 * Pós-condição: carrega um dado de senha do arquivo para a estrutura dinamica tUsuario
 * @param *pu para o ponteiro tUsuario, *u para ponteiro de arquivo usuarios.csv 
*/
void leSenha(tUsuario *p, FILE *u);


/**
 * @brief Carrega as informacoes do arquivo csv para a estrutura dinamica criada
 * Pré-Condição: Existencia do ponteiro de tUsuario, do ponteiro de arquivo usuarios.csv e da capacidade total da estrutura tUsuario
 * Pós-condição: retorna um ponteiro tUsuario, para asegurar em caso de realloc da estrutura dinamica, atualiza a capacidade da estrutura tUsuario e a quantidade de usua alocados;
 * @param *pu  Ponteiro dos tUsuario, *u ponteiro para arquivo usuarios.csv, *totalUsuario endereço da capacidade da estrutura tUsuario e *tamAloc quantidade de tUsuario alocada
*/ 
tUsuario *carregaUsuario(tUsuario *pu, FILE *u, int *totalUsuario,int *tamAloc);


/**
 * @brief Verifica se o login escolhido ja existe no sistema 
 * Pré-Condição: ponteiro de tUsuario, o tamanho do nome e o nome escolhido
 * @param *pu ponteiro de tUsuario, o tam tamanho do nome e *nome string do nome escolhido
 return -1 caso o usuario nao esteja no sistema ou outro numero com a posição dele no sistema
*/
int verificaLogin(tUsuario *pu, int tam, char *nome);

/* verifica se a senha daquele login esta correta */
/**
 * @brief Verifica se a senha do login escolhido esta correta 
 * Pré-Condição: ponteiro de tUsuario, a posicao do login anteriormente digitado, senha digitada 
 * @param *pu ponteiro de tUsuario, a posicao do login,anteriormente digitado, no tUsuario, a string senha digitada, e o endereço da posição do usuario caso a senha esteja correta
 return -1 caso o usuario nao esteja no sistema ou outro numero com a posição dele no sistema
*/
int verificaSenha(tUsuario *pu, int posicao, char *senha,int *usuario);

/**
 * @brief Verifica se o usuario esta cadastrado no sistema com o auxilo  verificaLogin e verificaSenha
 * Pré-Condição: ponteiro tUsuario, numero de usuarios no sistema
 * Pós-condição: caso o usuario esteja no sistema atualiza o valor de *usuario para a posicao dele no ponteiro pu
 * @param *pu para o ponteiro tUsuario,tam quantidade de usuarios no sitema, *usuario endereço de qual usuario esta no sistema e a verbosidade
 return mensagem de "usuario nao cadastrado", "senha invalida" ou "usuario inativo" e chama o menu anterior e caso o usuario esteja no sistema retorna 4 para sair do do-while e seguir para o proximo menu
*/
int verificaCadastro(tUsuario *pu,int tam, int *usuario, int verbosidade);

/**
 * @brief Aloca novo ususario no sistema 
 * Pré-Condição: ponteiro de tUsuario, nome escolhido, senha escolhida,o tamanho do nome e tamanho da senha
 * @param *p ponteiro de tUsuario,*nome string do nome escolhido,*senha string da senha escolhida o tamNome tam tamanho do nome e tamSenha tam tamanho da senha
*/
void alocaNovoUsuario(tUsuario *p,char *nome, char *senha, int tamNome, int tamSenha);

/**
 * @brief Verifica se nome e senha estao nos padroes alfanumericos exigidos
 * Pré-Condição: nome digitado
 * @param *nome nome difgitado pelo usuario
 return -1 caso fora do padrao e o tamanho do nome caso esteja no padrão
*/
int verificaNomeSenha(char *nome);

/**
 * @brief Cadastra um novo usuario no sistema segundo as regras do programa
 * Pré-Condição: ponteiro tUsuario, numero de usuarios no sistema
 * Pós-condição: caso o usuario esteja no sistema atualiza o valor de *quantUsuario para a posicao dele no ponteiro pu
 * @param *pu para o ponteiro tUsuario,*quantUsuario endereço da quantidade de usuarios no sitema, *posicao endereço da posição do usuario no sistema e a verbosidade
 return 4 se o usuario novo foi cadastrado com sucesso e o menu anterior(e a nova escolha de op1) e as mensagens do que ocorreu caso o cadastro não se efetue
*/
int cadastrarUsuario(tUsuario *pu,int *quantUsuario, int *posicao, int verbosidade);

/**
 * @brief Salva dados de login do usuario no csv usuarios
 * Pré-Condição: ponteiro tUsuario,ponteiro do arquivo csv e a posição dele na estrutura
 * @param *pu para o ponteiro tUsuario,*u ponteiro de arquivo usuarios.csv e a posicao na estrutura
*/
void gravaLogin(FILE *u,tUsuario *pu, int posicao);

/**
 * @brief Salva dados de senha do usuario no csv usuarios
 * Pré-Condição: ponteiro tUsuario,ponteiro do arquivo csv e a posição dele na estrutura
 * @param *pu para o ponteiro tUsuario,*u ponteiro de arquivo usuarios.csv e a posicao na estrutura
*/
void gravaSenha(FILE *u,tUsuario *pu, int posicao);

/**
 * @brief Salva dados usuarios no csv usuarios
 * Pré-Condição: ponteiro tUsuario, numero de usuarios no sistema e ponteiro do arquivo csv
 * @param *pu para o ponteiro tUsuario,*quantUsuario endereço da quantidade de usuarios no sitema,*a ponteiro de arquivo usuarios.csv
*/
void salvaUsuarios(tUsuario *pu, FILE *u,int quantUsuarios);

/**
 * @brief Salva dados de ativo e inativo no csv inativos
 * Pré-Condição: ponteiro tUsuario, numero de usuarios no sistema e ponteiro do arquivo csv
 * @param *pu para o ponteiro tUsuario,*quantUsuario endereço da quantidade de usuarios no sitema,*a ponteiro de arquivo inativos.csv
*/
void salvaInativos(tUsuario *pu, int quantUsuarios, FILE *a);

/**
 * @briefinativa um usuario
 * Pré-Condição: ponteiro tUsuario,posição do usuario na estrutura
 * @param *pu para o ponteiro tUsuario e sua posição na estrutura dinamica
 return tUsuario na posição em questao em inativo recebe 1
*/
int inativaUsuario(tUsuario *pu, int posicao);

/**
 * @brief Se o usuario e inativo para tomar decisao
 * Pré-Condição: dados validos
 * Pós-condição: Se o usuario e inativo e retorna 3, se nao reseta o indicador de usuario do sistema e retorna o menu de login 
 @param *pu para o ponteiro tUsuario,posição qual usuario esta no sistema
*/
int sairQuatro(tUsuario *pu, int posicao, int verbosidade);

/**
 * @brief Imprime o cabeçalho da ordenação
 * Pré-Condição: tUsuario do usuario em questao
 * @param pu infos tUsuario do usuario em questao
*/
void imprimeInicioOrdenacao(tUsuario pu);

#endif