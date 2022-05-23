#ifndef FILMES_H
#define FILMES_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_INIT 25
#define QTD_FILMES 986
#define CTE_AUMENTO 2

/**
Representa o tipo de um filme
*/
typedef struct{
  char* nome; //Nome do filme
  int ano; //Ano do filme
  int duracao; //Duração do filme
  float avaliacao; //Avaliação do filme
  char* descricao; //Descrição do filme
}tFilme;


/**
 * @brief Testa se a abertura do ponteiro de arquivo Filmes foi feita com sucesso
 * Pré-Condição: Existencia do ponteiro de arquivo para Filmes
 * Pós-condição: Impressão de mensagem de falha e finalização do programa se ponteiro == NULL
 * @param *newPointer  Ponteiro de arquivo  filmes.csv
 */
void testaAberturaFilmes(FILE* newPointer);

/*Aloca dinamicamente um nome e descrição de cada filme */
/**
 * @brief Aloca dinamicamente um nome e descrição de cada filme 
 */
void allocFilme(tFilme* filme);

/**
 * @brief Aloca dinamicamente um vetor de tFilme com a quantidade de filmes definida pela constante QTD_FILMES
 * Pré-Condição: Ponteiro de tFilme para receber o retorno da função, QTD_FILMES definida corretamente
 * Pós-condição: Um ponteiro alocado com a quantidade devida de filmes
 * @return tFilme* ponteiro de tFilme que aponta pra um vetor de struct de tFilme
 */
tFilme* allocVetorFilmes();


/**
 * @brief Testa se a abertura do ponteiro de tFilme foi feita com sucesso
 * Pré-Condição: Existencia do ponteiro de tFilme
 * Pós-condição: Impressão de mensagem de falha e finalização do programa se ponteiro == NULL
 * @param *pp  Ponteiro dos filmes
 */
void testaPonteiroFilmes(tFilme *pp);


/**
 * @brief Lê o nome de um filme do arquivo
 * Pré-Condição: Arquivo nos padrões predefinidos e com a abertura correta
 * Pós-condição: Nome do filme carregado devidamente para o struct
 * @param filme Ponteiro do struct de filmes (interpretado como vetor)
 * @param arq Ponteiro para o arquivo onde se encontram os filmes
*/
void leNome(tFilme* filme, FILE *arq);

/*carrega a string descrição do filme do arquivo para a estrutura dinamica propria criada
*/
void leDesc(tFilme* filme, FILE *arq);

/*auxilia a leitura de cada linha do arquivo para passar para a estrutura
*/
void leLinhaFilme(tFilme* filmes, FILE *arq);

/*carrega os filmes do arquivo csv para a estrutura dinamica
*/
void carregaFilmes(tFilme* filmes, FILE *arq);

/**
  * @brief Libera o ponteiro para o vetor de filmes
  * @param filmes Ponteiro a ser liberado
*/
void liberaFilmes(tFilme* filmes);

/**
  * @brief Lista os filmes carregados no vetor de filmes, caso reset = 1 volta a lista do início. Caso voltar = 1, volta a lista em 10 filmes.
  * @param filmes Vetor de filmes
  * @param reset Varíavel que indica se é ou não para resetar a lista
  * @param voltar Variável que indica se é ou não para voltar a lista
  * @param verbosidade Verbosidade passada no comando de execução
  * @return Último id de filme que foi listado
*/
int listaFilmes(tFilme* filmes, int* reset, int voltar, int verbosidade);

/**
  * @brief Exibe os metadados de um determinado filme e oferece a opção de assistir ao filme
  * @param filmes Vetor de filmes
  * @param opcao Id do filme escolhido pelo usuário
  * @param verbosidade Verbosidade passada no comando de execução
*/
void exibeMetadadosFilme(tFilme* filmes, int opcao, int verbosidade);

/**
  * @brief Exibe a lista de filmes que contêm uma determinada combinação de caracteres. É possível assistir aos filmes
  * @param filmes Vetor com os filmes
  * @param nome Combinação de caracteres digitada pelo usuário
  * @return Vetor de inteiros que relaciona a ordem da lista(1, 2, 3, ...) com os ids dos filmes correspondentes. A primeira posicao do vetor sempre é a quantidade de filmes encontrados
*/
int *procuraFilmes(tFilme* filmes, char* nome);

/**
  * @brief Captura a entrada para a função procuraFilmes
  * @return String alocada dinamicamente
*/
char* capturaNomeFilme();

/**
  * @brief Libera uma string qualquer, neste caso a alocada pela função capturaNomeFilme
  * @param nome String a ser liberada
*/
void liberaNomeFilme(char* nome);

#endif