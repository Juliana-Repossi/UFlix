#include "../include/menu.h"

int validaEntrada1()
{
  char op[100];

  while(1)
  {

  scanf("%s",op);

  if(strlen(op)==1 && (op[0]=='1'|| op[0]=='2' || op[0]=='3'))
  {
    break;
  }
  printf("Operacao 1 Invalida\n");
  }

  system("clear");

  return atoi(op);
}


int validaEntrada2()
{
  char op[100];

  while(1)
  {

  scanf("%s",op);

  if(strlen(op)==1 && (op[0]=='1'|| op[0]=='2' || op[0]=='3'||op[0]=='4'))
  {
    break;
  }
  printf("Operacao 2 Invalida\n");
  }

  system("clear");

  return atoi(op);
}

char validaOpcao2()
{
  char op[100];

  while(1)
  {

  scanf("%s",op);

  if(strlen(op)==1 && (op[0]=='D'|| op[0]=='N' || op[0]=='2'||op[0]=='3'))
  {
    break;
  }
  printf("Opcao Invalida\n");
  }

  system("clear");

  return op[0];
}


int menuLogin(int verbosidade)
{
  
  int opcao;
  char op[50];

  //print das informacoes do menu
  if(verbosidade == 1)
  {
    printf("1- Login\n");
    printf("2- Cadastrar\n");
    printf("3- Sair\n");
  }

  return validaEntrada1();
}

char opcaoDois()
{
  printf("D ou N- Histórico ordenado por data ou por Nota\n");
  printf("2. Excluir minha conta\n");
  printf("3. Voltar\n");
  
  return validaOpcao2();
}

int menuPrincipal(int verbosidade){

  //print das informacoes do menu principal
  if(verbosidade == 1)
  {
    printf("1- Listar filmes\n");
    printf("2- Meu perfil\n");
    printf("3- Procurar Filme\n");
    printf("4- Sair\n");
  }
  
  return validaEntrada2();
}

int menuListaFilmes(tFilme* pf, int qualUsuario, FILE *hist,tHistorico **h,tHalocado *quant, int verbosidade)
{
  int voltar=0;
  int reset = 1, opcaoInt = 0, opcaoAssistir = 0, maxId;
  char opcao[3];
  maxId = listaFilmes(pf, &reset,voltar, verbosidade);
  int validoOp = 1;
  

  while(1)
  {
    opcaoInt = 0;
    //zerando o vetor opcao
    for(int i = 0; i < 3; i++)  opcao[i] = '0';

    if(validoOp == 0) printf("Digite uma opção válida\n");
    

    scanf("%c", &opcao[0]);

    //desconsidera \n
    if(opcao[0] == '\n')
    {
     scanf("%c", &opcao[0]);  
    } 
    //tratamento da op digitada
    if(opcao[0] != 'M' && opcao[0] != '0')
    {
      if(opcao[0] >= '0' && opcao[0] <= '9')
      {
        validoOp = 1;
        scanf("%c", &opcao[1]);
        if(opcao[1] != '\n')
        {
          scanf("%c", &opcao[2]);
          if(opcao[2] == '\n') opcao[2] = 0;
          else getchar();
        }
        else opcao[1] = 0;
      }
      opcaoInt = atoi(opcao);
      if((opcaoInt > maxId || opcaoInt < maxId - 9) && (opcaoInt > 0 && opcao[0] != 'M'))
      {
        printf("Filme inválido!\n");
        continue;
      }
      if(opcaoInt > 0 && opcaoInt <= maxId && opcaoInt >= maxId - 9)
      {
        
        system("clear");
        exibeMetadadosFilme(pf, opcaoInt, verbosidade);
        int validoAssistir = 1;
        do
        {
          scanf("%d", &opcaoAssistir);
          getchar();
          if(opcaoAssistir == 1 || opcaoAssistir == 2)
          {
            validoAssistir = 1;
            if(opcaoAssistir == 1)
            {
              system("clear");
              assistirFilme(pf, opcaoInt, qualUsuario, h,quant);
              return 0;
            }
            if(opcaoAssistir == 2)
            {
              system("clear");
              voltar=1;
              maxId = listaFilmes(pf, &reset,voltar, verbosidade);
              voltar=0;
              continue;
            }
          }
          else
          {
            printf("Digite uma opção válida\n");
            validoAssistir = 0;
          }
        }while(validoAssistir != 1);
      }
      else
      {
        printf("Digite uma opção válida\n");
      }
    }
    if(opcao[0] == 'M')
    {
      system("clear");
      maxId = listaFilmes(pf, &reset,voltar, verbosidade);
      validoOp = 1;
      
    }
    if(opcao[0] == '0')
    {
      system("clear");
      break;
    }
  }
  return atoi(&opcao[0]);
}

int menuProcuraFilmes(tFilme *pf, int qualUsuario, FILE *hist,tHistorico **h,tHalocado *quant, int verbosidade)
{
  char *nome;
  int opcao;
  int *ids;
  printf("Nome do filme: ");
  nome = capturaNomeFilme();
  ids = procuraFilmes(pf, nome);
  if(verbosidade == 1)
  {
    printf("0 - Voltar\n\n");
  }

  do
  {
    opcao = filtraIds(ids[0]);
    
    if(opcao == 0)
    {
      if(ids != NULL) free(ids);
      liberaNomeFilme(nome);
      system("clear");
      return 0;
    }
    exibeMetadadosFilme(pf, ids[opcao] + 1, verbosidade);
    int validoAssistir = 1;
    int opcaoAssistir;
    do
    {
      scanf("%d", &opcaoAssistir);
      getchar();
      if(opcaoAssistir == 1 || opcaoAssistir == 2)
      {
        validoAssistir = 1;
        if(opcaoAssistir == 1)
        {
          system("clear");
          assistirFilme(pf, ids[opcao] + 1, qualUsuario, h,quant);
          system("clear");
          if(ids != NULL) free(ids);
          liberaNomeFilme(nome);
          return 0;
        }
        if(opcaoAssistir == 2)
        {
          system("clear");
          if(ids != NULL) free(ids);
          ids = procuraFilmes(pf, nome);
          if(verbosidade == 1)
          {
            printf("0 - Voltar\n\n");
          }
          continue;
        }
      }
      else
      {
        printf("Digite uma opção válida\n");
        validoAssistir = 0;
      }
    }while(validoAssistir != 1);

  }while(opcao != 0);
  liberaNomeFilme(nome);
  if(ids != NULL){free(ids);}
   
  return 0;
}
