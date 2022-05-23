#include "../include/utils.h"



float filtraNota()
{
  float nota = 0;
  char *aux = capturaString(); 
  int valido = 1, negativo = 0, ponto = 0, esquerda = 0;
  //Verifica se tem algo invalido
  for(int i = 0; i < strlen(aux); i++)
  {
    if(aux[i] < '0' || aux[i] > '9')
    {
      if(i == 0 && aux[i] == '-') negativo = 1;
      else
      {
        if(aux[i] == '.' && ponto == 0) ponto = 1;
        else
        {
          if(aux != NULL) free(aux);
          return -2;
        }
      }
    }
  }

  for(int i = 0; i < strlen(aux); i++)
  {
    if(aux[i] == '.') break;
    if(aux[i] != '-') esquerda++;
  }
  esquerda--;
  if(esquerda >= 1) esquerda--;
  //Converte para float
  for(int i = 0; i < strlen(aux); i++)
  {
    if(aux[i] == '.') continue;
    if(aux[i] == '-') continue;

    nota += atoi(&aux[i]) * pow(10, esquerda);
    esquerda--;
  }
  if(negativo == 1) nota *= -1;
  if(nota < -1|| (nota > -1 && nota < 0) || nota > 10)
  {
    if(aux != NULL) free(aux);
    return -2;
  }
  
  if(aux != NULL) free(aux);
  return nota;
}

int bissexto(tData data)
{
  if(data.ano % 4 == 0 && (data.ano % 100 != 0 || data.ano % 400 == 0))
  {
    return 1;
  }
    return 0;
}

int verificaData(tFilme filme, tData data)
{
  int valido = 1;
  if(data.dia > 31 || data.mes > 12 || data.ano < filme.ano ||data.dia <= 0 || data.mes <= 0)  valido = 0;
  else
  {
    //Meses com 30 dias
    if(data.mes == 4 || data.mes == 6 || data.mes == 9 ||data.mes == 11)
    {
      if(data.dia > 30) valido = 0;
    }
    else if(data.mes == 2)
    {
      if(bissexto(data))
      {
        if(data.dia > 29) valido = 0;
      }
      else if(data.dia > 28) valido = 0;
    }
  }
  if(valido == 0) printf("Digite uma data válida\n");

  return valido;
}

int filtraIds(int max)
{
  int id, valido = 1;
  static int aux = 0;
  do
  {
    if(valido == 0) printf("Digite uma opção válida\n");
    scanf("%d", &id);
    getchar();
    if(id == 0) return 0;
    if(id < 0 || id > max)  valido = 0;
    else valido = 1;
  }while(valido != 1);

  return id;
}

char *capturaString()
{
  char *string = (char *)calloc(TAM_INIT, sizeof(char));
  char ch = 0;
  int i = 0, tam = TAM_INIT; 
  while(1)
  {
    scanf("%c", &ch);

    if(ch == '\n') break;

    if(i == tam - 1)
    {
      tam *= CTE_AUMENTO;
      string = (char *)realloc(string, sizeof(char) * tam);
    }

    string[i] = ch;
    i++;
  }
  string = (char *)realloc(string, sizeof(char) * strlen(string));
  return string;
}

int isNum(char ch)
{
  if(ch >= '0' && ch <= '9') return 1;
  return 0;
}

tData filtraData()
{
    char *aux = capturaString();
    tData data;
    int tam = strlen(aux);

    for(int i = 0; i < tam; i++)
    {
      if((aux[i] < '0' || aux[i] > '9') && aux[i] != '/')
      {
        printf("Caracteres inválidos!\n");
        data.dia = -1;
        data.mes = -1;
        data.ano = -1;
        if(aux != NULL) free(aux);
        return data;
      }
    }

    //Verifica se a data tem o formato dd/mm/aaaa
    if(strlen(aux) > 10)
    {
      printf("Data com formato inválido!\n");
      data.dia = -1;
      data.mes = -1;
      data.ano = -1;
      if (aux != NULL) free(aux);
      return data;
    }

    if ((!isNum(aux[0])) || (!isNum(aux[1])) || (!isNum(aux[3])) || (!isNum(aux[4])) || (!isNum(aux[6])) || (!isNum(aux[7])) || (!isNum(aux[8])) || (!isNum(aux[9])))
    {
      printf("Data com formato inválido!\n");
      data.dia = -1;
      data.mes = -1;
      data.ano = -1;
      if (aux != NULL) free(aux);
      return data;
    }

    data.dia = (aux[0] - '0') * 10 + (aux[1] - '0');
    data.mes = (aux[3] - '0') * 10 + (aux[4] - '0');
    data.ano = (aux[6] - '0') * 1000 + (aux[7] - '0') * 100 + (aux[8] - '0') * 10 + (aux[9] - '0');

    if (aux != NULL) free(aux);
    return data;
}

int transformaData(tData d)
{
  /*para simplificar criamos um int a partir da data 
  ano*10000 + mes*100 + dia*/

 return (d.ano*10000)+(d.mes*100)+(d.dia);
}

tData voltaData(int x)
{
  tData data;

  data.ano=x/10000;
  data.mes=(x-data.ano*10000)/100;
  data.dia=((x-data.ano*10000)-data.mes*100);
  return data;
}