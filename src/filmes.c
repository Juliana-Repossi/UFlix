#include "../include/filmes.h"

void testaAberturaFilmes(FILE* newPointer)
{
  if(newPointer==NULL)
  {
    printf("Falha na abertura de arquivo filme.csv\n");
    exit(1);
  }

}

void allocFilme(tFilme* filme)
{
  if(filme != NULL)
  {
    filme->descricao = (char *)calloc(TAM_INIT, sizeof(char));
    filme->nome = (char *)calloc(TAM_INIT, sizeof(char));
  }
  else
  {
    printf("Entre com um ponteiro válido!\n");
    exit(3);
  }
}

tFilme* allocVetorFilmes()
{
  tFilme* ponteiro = malloc(sizeof(tFilme) * QTD_FILMES);
  for(int i = 0; i < QTD_FILMES; i++)
  {
    allocFilme(&ponteiro[i]);
  }
  return ponteiro;
}

void testaPonteiroFilmes(tFilme *pp)
{
  if(pp==NULL)
  {
   printf("Falha no ponteiro de filme\n");
   exit(1); 
  }
}


void leNome(tFilme *filme, FILE *f)
{
  int i = 0, tam = TAM_INIT;
  char ch;
  while(1)
  {
    ch = fgetc(f);

    if(ch == ',') break;

    if(i == tam - 1)
    {
      tam *= CTE_AUMENTO;
      filme->nome = (char*)realloc(filme->nome, sizeof(char) * tam);
    }

    if(filme->nome + i != NULL)
    {
      filme->nome[i] = ch;
      i++;
    }
    else
    {
      //Apenas para efeito de debug
      printf("Nao há espaço para atribuir o nome!\n");
      exit(4);
    }
  }
  filme->nome = (char *)realloc(filme->nome, sizeof(char) * strlen(filme->nome));
}

void leDesc(tFilme *filme, FILE *f)
{
  int i = 0, tam = TAM_INIT;
  char ch;
  ch = fgetc(f);

  if(ch != '"')
  {
    if(filme->descricao != NULL)
    {
      filme->descricao[0] = ch;
      i++;
    }
    else exit(5);
  }

  while(1)
  {
    ch = fgetc(f);
    if(ch == '\n') break;

    if(i == tam - 1)
    {
      tam *= CTE_AUMENTO;
      filme->descricao = (char*)realloc(filme->descricao, sizeof(char) * tam);
    }

    if(filme->descricao + i != NULL)
    {
      filme->descricao[i] = ch;
      i++;
    }
    else
    {
      //Apenas para efeito de debug
      printf("Nao há espaço para atribuir a descricao!\n");
      exit(5);
    }
  }
  if(filme->descricao[i - 1] == '"') filme->descricao[i - 1] = '\0';

  filme->descricao = (char *)realloc(filme->descricao, sizeof(char) * strlen(filme->descricao));
}

void leLinhaFilme(tFilme* filme, FILE* f)
{
  leNome(filme, f);
  fscanf(f, "%d,", &filme->ano);
  fscanf(f, "%d,", &filme->duracao);
  fscanf(f, "%f,", &filme->avaliacao);
  leDesc(filme, f);
}

void carregaFilmes(tFilme *filmes, FILE *f)
{
  int i = 0;
  if(f!= NULL)
  {
    while(i < QTD_FILMES)
    {
      leLinhaFilme(&filmes[i], f);
      i++;
    }
  }
}

void liberaFilmes(tFilme *filmes)
{
  if(filmes != NULL)
  {
    for(int i = 0; i < QTD_FILMES; i++)
    {
      if(filmes[i].descricao != NULL)
      {
        free(filmes[i].descricao);
      }
      if(filmes[i].nome != NULL)
      {
        free(filmes[i].nome);
      }
    }
    free(filmes);
  }
}

int listaFilmes(tFilme* filmes, int* reset, int voltar, int verbosidade)
{
  static int i;
  //se for a primeira passagem
  if(*reset == 1)
  {
    i = 0;
    *reset = 0;
  }
  if(voltar==1)
  {
    i=i-10;
  }

  if(i < QTD_FILMES)
  {
    for(int j = 0; j < 10 && i < QTD_FILMES; j++)
    {
      if(filmes[i].nome != NULL)
      {
        printf("%d- %s\n", i + 1, filmes[i].nome);
        i++;
      }
    }
    if(verbosidade == 1)
    {
      printf("M - Mais filmes\n");
      printf("0 - Voltar\n");
    }
  }
  if(i >= QTD_FILMES - 1)
  {
   printf("Fim de filmes disponiveis\n"); 
   if(verbosidade == 1) printf("0 - Voltar\n");
  } 

  return i;
}

void exibeMetadadosFilme(tFilme* filmes, int opcao, int verbosidade)
{
  if(filmes + (opcao - 1) != NULL)
  {
    system("clear");
    printf("Título: %s\n", filmes[opcao - 1].nome);
    printf("Ano: %d\n", filmes[opcao - 1].ano);
    printf("Duração: %d minutos\n", filmes[opcao - 1].duracao);
    printf("Avaliação: %.1f\n", filmes[opcao - 1].avaliacao);
    printf("Descrição: %s\n\n", filmes[opcao - 1].descricao);
    if(verbosidade == 1)
    {
      printf("1- Assistir\n");
      printf("2- Voltar\n");
    }
  }
}

int *procuraFilmes(tFilme* filmes, char* nome)
{
  system("clear");
  int ehIgual = 1, count = 1;
  int *ids = (int *)calloc(QTD_FILMES, sizeof(int));
  if(filmes != NULL)
  {
    //Percorre os filmes
    for(int i = 0; i < QTD_FILMES; i++)
    {
      //Percorre os caracteres do nome do filme
      for(int j = 0; j < strlen(filmes[i].nome); j++)
      {
        int l;
        l = 0;
        ehIgual = 1;
        //Encontrou a primeira letra do nome
        if(toupper(filmes[i].nome[j]) == toupper(nome[0]))
        {
          //Testa se o restante dos caracteres é igual
          for(int k = j; k < strlen(nome) + j; k++)
          {
            if(filmes[i].nome + k != NULL)
            {
              if(toupper(filmes[i].nome[k]) != toupper(nome[l]))
              {
                ehIgual = 0;
                break;
              }
              l++;
            }
          }
        }
        //É necessario verificar se percorreu todo o nome, pois o nome deve estar inteiramente contido
        if(ehIgual == 1 && l == strlen(nome))
        {
          printf("%d- %s\n", count, filmes[i].nome);
          ids[count] = i;
          count++;
          break;
        }
      }
    }
    if(count == 1) printf("Nenhum filme encontrado!\n");
  }
  ids[0] = count - 1;
  return ids;
}

char *capturaNomeFilme()
{
  char *string = (char *)calloc(TAM_INIT, sizeof(char));
  int i = 0, tam = TAM_INIT;
  char ch = getchar();
  ch = 0;
  while(ch != '\n')
  {
    if(i == tam - 1)
    {
      tam *= CTE_AUMENTO;
      string = (char *)realloc(string, sizeof(char) * tam);
    }

    ch = getchar();
    if(ch != '\n')
    {
      string[i] = ch;
      i++;
    }
    else break;
  }
  string = (char *)realloc(string, strlen(string));
  return string;
}

void liberaNomeFilme(char* nome)
{
  if(nome != NULL) free(nome);
}