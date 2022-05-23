#ifndef HISTORICO_H
#define HISTORICO_H

#include <stdio.h>
#include <stdlib.h>


#include "filmes.h"
#include "utils.h"



#define TAM_HIST 5
#define CTE_HIST 10

/*representa um tipo historico*/
typedef struct
{
  int id; //id do filme
  float nota; //nota do filme
  tData data; //data que foi assistido
}tHistorico;

/*representa capacidade e armazenamento do historico*/
typedef struct
{
  int total;
  int usado; 
}tHalocado;

/*representa um tipo para ordenar o historico*/
typedef struct
{
  int data;
  int  idFilme;
  float avaliacao;
  int copiado;
}tOrdenado;

/**
 * @brief Aloca um array de tam de tHalocado 
 * Pré-Condição: Existencia da quant de usuarios no sistema
 * Pós-condição: retorna o ponteiro p com o endereço allocado
 * @param tam  quantidade de usuarios no sitema
*/
tHalocado *allocaQuant(int tam);

/**
 * @brief Testa se a abertura do ponteiro de arquivo historico.csv foi feita com sucesso
 * Pré-Condição: Existencia do ponteiro de arquivo para historico.csv
 * Pós-condição: Impressão de mensagem de falha e finalização do programa se ponteiro == NULL
 * @param *arq  Ponteiro para arquivo historico.csv
*/
void testaAberturaHistorico(FILE *arq);

/**
 * @brief alloca um onteiro para cada usuario, para este ponteiro alocar um array de tHistorico
 * Pré-Condição: quantidade de usuarios no sistema
 * Pós-condição: retorna um array de ponteiros,um para cada usuario, e  cada um desses com um array tHistorico de tamanho TAM_HIST, além de atualizar a capacidade de armazenamento de historico de cada usuario em a.total
 * @param totalUsuarios quant de usuarios no sistema e *a ponteiro de tHalocado
*/
tHistorico **allocaHistorico(int totalUsuarios,tHalocado *a);


/**
 * @brief realloca o vetor de historico de um unico usuario
 * Pré-Condição: dados validos
 * Pós-condição: retorna um arrauy maior de historico para aquele usuario segundo um CTE_HIST
 * @param ponteiro tHistorico do usuario, o ponteiro da capacidade e armazenamento do historico do usuario e qual e o usuario;
 return vator tHistorico reallocado e maior, com as mesmas informações e atualiza o tamanho total dele no tHalocado
*/
tHistorico *reallocaUmHist(tHistorico *h,tHalocado *a, int usuario);

/**
 * @brief copia tods os dados de h para p
 * Pré-Condição: dados validos
 * Pós-condição: todos os dados copiados de h para p 
 * @param ponteiro "original" tHistorico do usuario,ponteiro "copia" tHistorico do usuario e tad do armazenamento do historico do usuario de um unic usuario;
*/
void copiaHistorico(tHistorico *h,tHistorico *p, tHalocado a);

/**
 * @brief Alloca um ponteiro de ponteiro maior que o tHistorico h e realloca o tHalocado os dois de um tamAntigo para um tamAtual
 * Pré-Condição:  ponteiro de ponteiro h, tamanho antigo e atual, e ponteiro tHalocado válidos
 * Pós-condição: um **tHistorico com os dados do antigo e tHalocado reallocado, os dois agora de tamAtual e **h liberado da memória
 * @param ***h ponteiro de ponteiro de tHistorico, tamAntigo: tamanho total do tHistorico **h, tamAtual: novo tamanho de tHistorico, e *a ponteiro de tHalocado
*/
tHistorico **reallocaHistorico(tHistorico **h,int tamAntigo, int tamAtual,tHalocado *a);

/**
 * @brief Copia as informações do csv historico para a estrutura dinamica tHistorico
 * Pré-Condição: Existencia do ponteiro de arquivo para historico.csv, ponteir de ponteiro da estrutura tHistorico, o primeiro caracter usado para teste de vazio
 * Pós-condição: dados carregados para a estrutura, valores de tamanho do historico do usuario alocado e o tamanho da capacidade da estrutura dinamica do seu historico
 * @param *hist  Ponteiro para arquivo historico.csv, **h ponteiro de ponteiro tHistorico, *quant ponteiro de tHalocado, caracter c primeiro do arquivo csv lido
*/
void leHistorico(FILE *hist,tHistorico **h,char c, tHalocado *quant);

/**
 * @brief Copia se existir para a estrutura tHistorico os dados de historico.csv atraves da função leHistorico
 * Pré-Condição: Existencia do ponteiro de arquivo para historico.csv, ponteiro de ponteiro tHistorico
 * Pós-condição: tHistorico com as informaçoes de historico.csv e atualiza para cada usuario o tamanho do seu historico e a capacidade da estrutura dinamica do seu historico
 * @param *hist  Ponteiro para arquivo historico.csv, **h ponteiro de ponteiro tHistorico, *quant ponteiro de tHalocado
*/
void carregaHistorico(FILE *hist,tHistorico **h,tHalocado *quant);

/**
 * @brief Confere ao usuario a opcao de assistir a um filme e se isso acontecer grava o filme no struct do histórico
 * Pré-Condição: Parametros definidos e carregados corretamente
 * Pós-condição: Filme gravado no struct do histórico
 * @param filmes Ponteiro para o vetor de tFilme, que representa os filmes
 * @param idFilme Id do filme a ser assitido
 * @param idUsuario Id do usuário que está logado
 * @param h
 * @param quant Vetor para a quantidade de filmes assistidos por cada usuário
*/
void assistirFilme(tFilme *filmes, int idFilme, int idUsuario, tHistorico **h, tHalocado *quant);

/**
 * @brief Desaloca a estrutura tHistorico
 * Pré-Condição: Existencia do ponteiro tHistorico, do ponteiro tHalocado, ponteiro de arquivo historico.csv e o tamanho dele
 * Pós-condição: Salva os dados da estrutura no csv mencionado
 * @param **h ponteiro de ponteiro tHistorico, *a ponteiro de tHalocado,*hist ponteiro do arquivo historico.csv e tamTotal tamanho total de usuarios
*/
void salvaHistorico(tHistorico **h, tHalocado *a, FILE *hist,int tamTotal);

/**
 * @brief Desaloca a estrutura tHistorico
 * Pré-Condição: Existencia do ponteiro tHistorico e o tamanho dele
 * Pós-condição: liberado da memória
 * @param *pu ponteiro tHistorico e o tam tamanho total dele
*/
void liberaHisto(tHistorico **h, int tamTotal);


/**
 * @brief Imprime o histórico odenado por nota de acordo com o padrao
 * Pré-Condição: historico do usuario em questao ordenado por nota, quantidade de historicos alocados 
 * Pós-condição: Histórico ordenado printado
 * @param h Ponteiro para um vetor de tHistorico, representando o historico do usuario, a quantidade de historico do usuario e ponteiro de tFilme
*/
void imprimeOrdenadoNota(tHistorico *h,tHalocado a, tFilme *f);

/**
 * @brief Ordena o histórico por ordem decrescente de nota
 * Pré-Condição: Parametros definidos corretamente
 * Pós-condição: Histórico ordenado
 * @param h Ponteiro para um vetor de tHistorico, representando o historico do usuario
 * @param a Struct que representa a quantidade de filmes usados e alocados pelo historico
*/
void ordenaNota(tHistorico *h,tHalocado a,tFilme *f);

/**
 * @brief Copia os dados importantes de tHistorico para tOrdenado fazendo a transformação da data
 * Pré-Condição: Existencia do ponteiro tOrdenado ,tHistorico e das informaçoes do tad tHalocado
 * Pós-condição:dados copiados de tHistorico para tOrdenado
 * @param *ponteiro para tHistorico, ponteiro tOrdenado e tad tHalocado
*/
void carregaOrdena(tHistorico *h, tHalocado a,tOrdenado *d);

/**
 * @brief Testa se a abertura do ponteiro tOrdenado foi feita com sucesso
 * Pré-Condição: Existencia do ponteiro tOrdenado
 * Pós-condição: Impressão de mensagem de falha e finalização do rograma se ponteiro == NULL
 * @param *arq  Ponteiro para tOrdenado
*/
void testaOrdenado(tOrdenado *p);

/**
 * @brief Copia dados de de d na posição para o na mesma posição
 * Pré-Condição: dados validos
 * Pós-condição: copia da posicao posicao feita de d para o
 * @param ponteiro tOrdenado d e o, posição que a copia vai ser realizada e um contador somads copiados passad por referencia
 return copia realizada e soma dos copiados recebe +1
*/
void copiaDadosOrdenados(tOrdenado *d, tOrdenado *o,int *somaCopiados, int posicao);

/**
 * @brief libera um tipo tOrdenado alocado dinamicamente
 * Pré-Condição: ponteiro valido
 * Pós-condição:ponteiro liberado
*/
void liberaOrdenacao(tOrdenado *p);

/**
 * @brief Ordena o historico por data
 * Pré-Condição: tOrdenado valido e quantidade de historico(tHalocado)
 * Pós-condição: Histórico ordenado na estrutura dinamica
 * @param  Ponteiro para um vetor de tOrdenado e a quantidade de historico do usuario 
 return o ponteiro da estrutura dinamica com o historico ordenado e libera a antiga da memoria
*/
tOrdenado *Ordena(tOrdenado *d, tHalocado a);

/**
 * @brief Imprime o histórico odenado por data de acordo com o padrao
 * Pré-Condição: historico do usuario em questao ordenado por data, quantidade de historicos alocados 
 * Pós-condição: Histórico ordenado printado
 * @param h Ponteiro para um vetor de tHistorico, representando o historico do usuario, a quantidade de historico do usuario e ponteiro de tFilme
*/
void imprimeOrdenado(tOrdenado *o,tHalocado a, tFilme *f);

/**
 * @brief So retorna a operação quando a entrada do usuario for 0
 * Pós-condição: retorna "operacao  invalida" ate que seja digitado 0
*/
int validaVolta();

/**
 * @brief Ordena o histórico por ordem decrescente de data
 * Pré-Condição: historico do usuario em questao, quantidade de historicos alocados
 * Pós-condição: Histórico ordenado
 * @param h Ponteiro para um vetor de tHistorico, representando o historico do usuario, a quantidade de historico do usuario e ponteiro de tFilme
*/
int ordenaData(tHistorico *h,tHalocado a,tFilme *f);

#endif