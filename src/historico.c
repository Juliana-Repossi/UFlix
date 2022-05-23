#include "../include/historico.h"
#include "../include/filmes.h"
#include "../include/usuarios.h"
#include "../include/utils.h"
#include "../include/historico.h"


tHalocado *allocaQuant(int tam)
{
  tHalocado *p=(tHalocado*)calloc(tam,sizeof(tHalocado));
  return p;
}

void testaAberturaHistorico(FILE *arq)
{
  if(arq == NULL)
  {
    printf("Falha na abertura do arquivo historico.csv\n");
    exit(1);
  }
}

tHistorico **allocaHistorico(int totalUsuarios,tHalocado *a)
{
  tHistorico **p=(tHistorico **)malloc(sizeof(tHistorico *)*totalUsuarios);

  for(int i=0; i<totalUsuarios; i++)
  {
    p[i]=(tHistorico *)calloc(TAM_HIST,sizeof(tHistorico));
    a[i].total=TAM_HIST;
  }

 return p;
}

tHistorico *reallocaUmHist(tHistorico *h,tHalocado *a, int usuario)
{
  int tam=a[usuario].total+CTE_HIST;
  tHistorico *p=(tHistorico *)malloc(sizeof(tHistorico)*tam);

  if(p==NULL)
  {
    printf("Erro na reallocação de um usuario\n");
    exit(1);
  }

  //copiando dados
  for(int i=0;i<a[usuario].total;i++)
  {
    p[i].id=h[i].id;
    p[i].nota=h[i].nota;
    p[i].data.dia=h[i].data.dia;
    p[i].data.mes=h[i].data.mes;
    p[i].data.ano=h[i].data.ano; 
  }

  if(h!=NULL)
  {
    free(h);
  }


  a[usuario].total=tam;
  //retorna o tamanho maximo da allocação
  return p;
}

void copiaHistorico(tHistorico *h,tHistorico *p, tHalocado a)
{
  for(int i=0;i<a.usado;i++)
  {
    p[i].id=h[i].id;
    p[i].nota=h[i].nota;
    p[i].data=p[i].data;
  }
}

tHistorico **reallocaHistorico(tHistorico **h,int tamAntigo, int tamAtual,tHalocado *a)
{
  tHistorico **p=(tHistorico **)malloc(sizeof(tHistorico *)*tamAtual);

  //realocar o ponteiro com as informações do tamanho do tHistorico
  a=(tHalocado *)realloc(a,sizeof(tHalocado)*tamAtual);

  for(int i=0;i<tamAntigo;i++)
  {
    p[i]=(tHistorico *)malloc(sizeof(tHistorico)*a[i].total);
    copiaHistorico(h[i],p[i],a[i]);
  }
  for(int i=tamAntigo;i<tamAtual;i++)
  {
    p[i]=(tHistorico *)malloc(sizeof(tHistorico)*TAM_HIST); 
    a[i].total=TAM_HIST;
    a[i].usado=0;
  }

  //libera o h
  liberaHisto(h,tamAntigo);

  return p;
}

void leHistorico(FILE *hist,tHistorico **h,char c, tHalocado *quant)
{
  int usuario=-1;
  
  //para ler todos usuarios
  do{
    usuario++;
    int j=-1;
  
    //ler todos de um usuario
    do
    {
      int i=0;

      char ch[4]={',',',',','};
      //verificar se o usuario nao tem historico
      if(c=='\n')
      {
      break;
      }
      else
      {
        if(c!=',')
        {
        ch[0]=c;
        i++;
        }
      }
      j++;
      
      ////realloc caso passe a quantidade
      if(quant[usuario].usado==quant[usuario].total)
      {
        h[usuario]=reallocaUmHist(h[usuario],quant,usuario);
      }
      
      //usuario que tem historico
      for(i;i<4;i++)
      {
        c=fgetc(hist);
        if(c==',')
        { 
        break;
        } 
        else
        {
        ch[i]=c;
        }
      }
      //armazena id d filme
      int id=atoi(ch);
      (h[usuario])[j].id=id;
      //lendo a nota
      float nota;
      fscanf(hist, "%f,",&(h[usuario])[j].nota);
      //lendo a data
      tData data;
      fscanf(hist, "%d/%d/%d",&(h[usuario])[j].data.dia,&(h[usuario])[j].data.mes,&(h[usuario])[j].data.ano);     
      quant[usuario].usado=quant[usuario].usado+1;
      c=fgetc(hist);
    }while(c==',');
      quant[usuario].usado=j+1;
      c=fgetc(hist);
  }while(c!=EOF);
}

void carregaHistorico(FILE *hist,tHistorico **h,tHalocado *quant)
{
  char ch;

  //primeiro caractere
  ch=fgetc(hist);

  if(ch==EOF)
  {
    //arquivo vazio
   //printf("vazio\n");
  }
  else
  {
   leHistorico(hist,h,ch,quant);
  }
}

void assistirFilme(tFilme *filmes, int idFilme, int idUsuario, tHistorico **h, tHalocado *quant)
{
  
  tData data;
  float nota;
  printf("O que achou de %s? De uma nota entre 0 e 10: ", filmes[idFilme - 1].nome);
  nota = filtraNota();
  //Se nota é inválida
  while(nota == -2)
  {
    printf("Digite uma nota válida\n");
    nota = filtraNota();
  }
  printf("Data: ");
  do
  {
    data = filtraData();
  }while(verificaData(filmes[idFilme - 1], data) == 0);
  
  //verificar se ha espaço
  if(quant[idUsuario].total==quant[idUsuario].usado)
  {
    
    h[idUsuario]=reallocaUmHist(h[idUsuario],quant,idUsuario);
  }

  //colocando na estrutura dinamica de historico
  (h[idUsuario])[quant[idUsuario].usado].id=idFilme;
  (h[idUsuario])[quant[idUsuario].usado].nota=nota;
  (h[idUsuario])[quant[idUsuario].usado].data=data;
  
  quant[idUsuario].usado=quant[idUsuario].usado+1;
}

void salvaHistorico(tHistorico **h, tHalocado *a, FILE *hist,int tamTotal)
{

  for(int i=0;i<tamTotal;i++)
  {
    if(a[i].usado==0)
    {
      fputc('\n', hist);
    }
    else
    {
      for(int j=0;j<a[i].usado;j++)
      {
        fprintf(hist,"%d,",(h[i])[j].id);
        fprintf(hist,"%.2f,",(h[i])[j].nota);
        fprintf(hist,"%.2d/",(h[i])[j].data.dia);
        fprintf(hist,"%.2d/",(h[i])[j].data.mes);
        fprintf(hist,"%.4d",(h[i])[j].data.ano);

        if((j+1)<a[i].usado)
        {
          fputc(',', hist);
        }
        else
        {
          fputc('\n', hist);
        }

      }
    }
  }
}

void liberaHisto(tHistorico **h, int tamTotal)
{

  if(h!=NULL)
  {
    for(int i=0;i<tamTotal;i++)
    {
      if(h[i]!=NULL)
      {
        free(h[i]);
      }
    }
   free(h);
  }
}

void imprimeOrdenadoNota(tHistorico *h,tHalocado a, tFilme *f)
{
  for(int j=0;j<a.usado;j++)
  {
  printf("%.2d/%.2d/%.4d - %s:",h[j].data.dia,h[j].data.mes,h[j].data.ano,f[h[j].id - 1].nome);

  /*testando se ha avaliação*/
  if(h[j].nota==-1)
  {
    printf("Sem avaliacao\n");
  }
  else
  {
    printf("%.2f\n",h[j].nota);
  }

  }
}

void ordenaNota(tHistorico *h,tHalocado a,tFilme *f)
{
  tHistorico aux;
  int alterou = 0;

  do
  {
    alterou = 0;
    for(int i = 0; i < a.usado - 1; i++)
    {
      if(h[i].nota < h[i + 1].nota)
      {
        aux = h[i];
        h[i] = h[i + 1];
        h[i + 1] = aux;
        alterou = 1;
      }
    }
  }while(alterou == 1);

 imprimeOrdenadoNota(h,a,f);

  //imprime a opcao voltar
  int c;
  printf("\n0 - Voltar\n");

  c=validaVolta();  

}

void carregaOrdena(tHistorico *h, tHalocado a,tOrdenado *d)
{
  /*informacoes que compoem o historico: data, nome do filme e avaliacao*/
  for(int i=0; i<a.usado;i++)
  {
    /*armazenando a data como int*/
    d[i].data=transformaData(h[i].data);
    /*armazena id do filme*/
    d[i].idFilme=h[i].id;
    /*armazena avaliacao*/
    d[i].avaliacao=h[i].nota;
    /*inicializa copiado*/
    d[i].copiado=0;
  }
}

void testaOrdenado(tOrdenado *p)
{
  if(p==NULL)
  {
    printf("Erro no ponteiro de ordenação\n");
    exit(1);
  }
}

void copiaDadosOrdenados(tOrdenado *d, tOrdenado *o,int *somaCopiados, int posicao)
{
  o[*somaCopiados].data=d[posicao].data;
  o[*somaCopiados].idFilme=d[posicao].idFilme;
  o[*somaCopiados].avaliacao=d[posicao].avaliacao;

  d[posicao].copiado=1;
  *somaCopiados=*somaCopiados+1;
}

void liberaOrdenacao(tOrdenado *p)
{
  if(p!=NULL)
  {
    free(p);
  }
}

tOrdenado *Ordena(tOrdenado *d, tHalocado a)
{
  /*allocar outra estrutura dinamica para receber ordenado*/
  tOrdenado *o=(tOrdenado *)malloc(sizeof(tOrdenado)*a.usado);

  /*inicializa com a primeira data*/
  int maior=d[0].data;
  int somaCopiados=0;
  int posicao=0;
  
  while(somaCopiados!=a.usado)
  {
    for(int i=0;i<a.usado;i++)
    {
      if(d[i].data>maior && d[i].copiado==0)
      {
        maior=d[i].data;
        posicao=i;
      }
    }
    copiaDadosOrdenados(d,o,&somaCopiados,posicao);
      
    for(posicao=0;posicao<a.usado;posicao++)
    {
      /*pegar o proximo*/
      maior=d[posicao].data;
        
       if(d[posicao].copiado==0)
       {
        break;
       }
    }
  }
  /*liberar o d*/
  liberaOrdenacao(d);
  /*retorna o ordenado*/
  return o;
}


void imprimeOrdenado(tOrdenado *o,tHalocado a, tFilme *f)
{
  tData data;

  for(int j=0;j<a.usado;j++)
  {
  data=voltaData(o[j].data);
  printf("%.2d/%.2d/%.4d - %s:",data.dia,data.mes,data.ano,f[o[j].idFilme - 1].nome);
  /*testando se ha avaliação*/
  if(o[j].avaliacao==-1)
  {
    printf("Sem avaliacao\n");
  }
  else
  {
    printf("%.2f\n",o[j].avaliacao);
  }

  }
}

int validaVolta()
{
  char op[100];

  while(1)
  {
  scanf("%s",op);

  if(strlen(op)==1 && op[0]=='0')
  {
    break;
  }
  printf("Operacao Invalida\n");
  }

  system("clear");

  return 0;
}

int ordenaData(tHistorico *h,tHalocado a,tFilme *f)
{

  //alocando estrutura para receber o historico do usuario
  tOrdenado *d=(tOrdenado *)malloc(sizeof(tOrdenado)*a.usado);
  //testa alocacao
  testaOrdenado(d);

  //copia dados do historico para a estrutura
  carregaOrdena(h,a,d);

  //ordenando
  d=Ordena(d,a);

  //imprime
  imprimeOrdenado(d,a,f);

  liberaOrdenacao(d);

  //imprime a opcao voltar
  int c;
  printf("\n0 - Voltar\n");

  c=validaVolta();  

  return c; 
}