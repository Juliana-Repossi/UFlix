#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "filmes.h"

/**
  Representa o tipo de datas
*/
typedef struct
{
  int dia; //Dia da data
  int mes; //Mes da data
  int ano; //Ano da data
}tData;



/**
  * @brief Lê um float, que representa a nota, e filtra para saber se esse float se encaixa nos padroes de nota esperados
  * @return Um float representando a nota, já filtrada
*/
float filtraNota();

/**
 * @brief tData data representa a data a ser analisada
 *Verifica se o ano de uma data é bissexto e retorna 1 se verdadeiro e 0 senão. 
*/
int bissexto(tData data);

/**
  * @ brief Verifica se uma data é possível de existir e se ela pode ser dada como a data de vizualização de um filme
  * @param filme Struct do filme
  * @param data Data a ser analisada
*/
int verificaData(tFilme filme, tData data);

/**
  * @brief Captura o id de um filme, verifica se a entrada está nos padrões esperados e se está dentre os ids listados
  * @param max representa o maior id possível de ser escolhido
  * @return Id do filme, ja filtrado
*/
int filtraIds(int max);

/**
  * @brief Captura uma string do teclado, alocando ela dinamicamente de acordo com o seu tamanho
  * @return Ponteiro de char que representa a string capturada
*/
char *capturaString();

/**
  * @brief Verifica se um caractere é número
  * @param ch Caractere a ser analisado
  * @return Retorna 1 se é número e 0 senão
*/
int isNum(char ch);

/**
  * @brief Captura uma data e verifica se a entrada está nos padrões esperados
  * @return Data já filtrada
*/
tData filtraData();

/**
  * @brief Transforma uma data em um inteiro, tornando a ordenação por data mais simples anomesdia
  * @param d Data a ser transformada
  * @return O inteiro que representa a data
*/
int transformaData(tData d);

/**
  * @brief Transforma um inteiro que representa uma data ao seu valor em dia, mes e ano
  * @param x Inteiro a ser manipulado
  * @return Data transformada
*/
tData voltaData(int x);

#endif