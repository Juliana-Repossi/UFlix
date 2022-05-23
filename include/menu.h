#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "historico.h"
#include "filmes.h"

/**
 * @brief So retorna a operação quando a entrada do usuario for compatível com o menuLogin
 * Pós-condição: retorna "operacao 1 invalida" ate que seja digitada uma op valida e/ou a opcao escolhida pelo usuario para direcionar o programa 
*/
int validaEntrada1();

/**
 * @brief So retorna a operação quando a entrada do usuario for compatível com o menuLogin
 * Pós-condição: retorna "operacao 2 invalida" ate que seja digitada uma op valida e/ou a opcao escolhida pelo usuario para direcionar o programa 
*/
int validaEntrada2();

/**
 * @brief So retorna a operação quando a entrada do usuario for compatível com o menuLogin
 * Pós-condição: retorna "operacao invalida" ate que seja digitada uma op valida e/ou a opcao escolhida pelo usuario para direcionar o programa 
*/
char validaOpcao2();

/**
 * @brief Exibe o menu caso a verbisidade seja 1 e valida a entrada de acordo com as opçoes recebidas
 * Pós-condição: retorna a opcao valida escolhida pelo usuario para direcionar o programa
 * @param verbisidade  
*/
int menuLogin(int verbosidade);

/**Menu Meu perfil
 * @brief Exibe o menu caso a verbisidade seja 1 e valida a entrada de acordo com as opçoes recebidas
 * Pós-condição: retorna a opcao valida escolhida pelo usuario para direcionar o programa
 * @param verbisidade  
*/
char opcaoDois();

/**O menu principal
  *Imprime o menu principal
  *le a operacao que o usuário deseja
  *caso a operacao seja invalida, imprime "operacao 2 invalida"
  e le um novo numero, ate que um valido seja digitado
  *retorna o numero da operacao valida
*/
int menuPrincipal(int verbosidade);

/**Menu da opção 1 (listar filmes) do menu principal
  *Lista uma quantidade limitada de filmes (10 neste caso) e espera uma entrada
  *Caso a entrada esteja nos padrões esperados e seja um filme listado no momento, então segue para a opção de assistir ou não o filme, exibindo seus metadados
  @param pf - Ponteiro para a lista de filmes carregados (interpretado como um vetor);
  @param qualUsuario - Representa o id do usuário que está utilizando o sistema;
  @param hist - Ponteiro para o arquivo do historico (necessário para assistir à um filme);
  @param h - Matriz para o historico (linhas sao usuarios, colunas cada filme)
  @param quant - Quantidade de filmes assistidos por usuário
  verbosidade - Verbosidade passada no comando de execução
*/
int menuListaFilmes(tFilme* pf, int qualUsuario, FILE *hist,tHistorico **h, tHalocado *quant, int verbosidade);

/**Menu da opção 3 (procurar filmes) do menu principal
  *Lista todos os filmes com uma determinada palavra e espera uma entrada
  *Caso a entrada esteja nos padrões esperados e seja um filme listado no momento, então segue para a opção de assistir ou não o filme, exibindo seus metadados
  @param pf - Ponteiro para a lista de filmes carregados (interpretado como um vetor);
  @paramqualUsuario - Representa o id do usuário que está utilizando o sistema;
  @param hist - Ponteiro para o arquivo do historico (necessário para assistir à um filme);
  @param h - Matriz para o historico (linhas sao usuarios, colunas cada filme)
  @param quant - Quantidade de filmes assistidos por usuário
  verbosidade - Verbosidade passada no comando de execução
*/
int menuProcuraFilmes(tFilme *pf, int qualUsuario, FILE *hist,tHistorico **h, tHalocado *quant, int verbosidade);

#endif