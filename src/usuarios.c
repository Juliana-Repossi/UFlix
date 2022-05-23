#include "../include/usuarios.h"



void testaAberturaUsuario(FILE* newPointer)
{
  if(newPointer==NULL)
  {
    printf("Falha na abertura de arquivo usuario.csv\n");
    exit(1);
  }
}

void testaAberturaInativos(FILE* newPointer)
{
  if(newPointer==NULL)
  {
    printf("Falha na abertura de arquivo inativos.csv\n");
    exit(1);
  }
}

void desalocaInternos(tUsuario *p)
{
  if(p->login!=NULL)
  {
    free(p->login);
  }
  if(p->senha!=NULL)
  {
    free(p->senha);
  }
}

void desalocaUsuario(tUsuario *pu, int tam)
{
  if(pu!=NULL)
  {
    for(int i=0; i<tam; i++)
    {
     desalocaInternos(&pu[i]); 
    }
  free(pu);
  }
}

void alocaUsuario(tUsuario *p)
{
  p->login=(char *)calloc(TAM_LOGIN,sizeof(char));
   if(p->login==NULL)
   {
    printf("Erro na alocacao dinamica de login\n");
    exit(1);
   }
   p->senha=(char *)calloc(TAM_SENHA,sizeof(char));
   if(p->senha==NULL)
   {
    printf("Erro na alocacao dinamica de senha\n");
    exit(1);
   }
}

tUsuario *allocaVetorUsuario(int tam)
{
  tUsuario *p=(tUsuario *)malloc(sizeof(tUsuario)*tam);
  
  if(p==NULL)
  {
    printf("Erro na alocacao dinamica de tUsuario\n");
    exit(1);
  }

  for(int i=0; i<tam;i++)
  {
    alocaUsuario(&p[i]);
  }  
  return p;
}

void testaPonteiroUsuario(tUsuario *pp)
{
  if(pp==NULL)
  {
   printf("Falha no ponteiro de usuario\n");
   exit(1); 
  }
}

void copiaDados(tUsuario *pu,tUsuario *g)
{
  strcpy(g->login,pu->login);
  strcpy(g->senha,pu->senha);
}

tUsuario *reallocUsuario(tUsuario *pu, int *totalUsuario)
{
  int i=*totalUsuario;
  int tam= i + CTE_AUMENTO3;
  
  //ponteiro generico para alocar(para não perder informações)
  tUsuario *g=allocaVetorUsuario(tam);

  //agora copiar os dados que ja estavam no ponteiro
  for(int j=0;j<i;j++)
  {
   copiaDados(&pu[j],&g[j]); 
   g[j].inativo=pu[j].inativo; 
  }
  //agora que os dados estao copiados,desaloca o ponteiro pu 
  desalocaUsuario(pu,i);
  //novo tamanho total do tUsuario
  //por isso coloquei ele como referencia
  *totalUsuario=tam;

  return g;
}

void leLogin(tUsuario *p, FILE *u,char aux)
{
  //colocar o primeiro caracter que usou para verificar se nao era fim de arquivo
  p->login[0]=aux;
  //logo a proxima posicao e a 1;
  int i=1;
  int tam=TAM_LOGIN;
  char c=fgetc(u);
  while(c != ',')
  {
    // se ultrapassar o valor maximo alocado
    if(i==(tam-1))
    {
      tam=tam+CTE_AUMENTO2;
      p->login=realloc(p->login,sizeof(char)*tam);
    }
    p->login[i]=c;
    i++;
    c=fgetc(u);
  }
}

void leSenha(tUsuario *p, FILE *u)
{
  int i=0;
  int tam=TAM_SENHA;
  char c=fgetc(u);
  while(c != '\n')
  {
    if(i==tam-1)
    {
      tam=tam+CTE_AUMENTO2;
      p->senha=realloc(p->senha,sizeof(char)*tam);
    }
    p->senha[i]=c;
    i++;
    c=fgetc(u);     
  }
}

tUsuario *carregaUsuario(tUsuario *pu, FILE *u,int *totalUsuario, int *tamAloc)
{

  int tam=*totalUsuario;
  int i=0;
  char aux=fgetc(u);
  while(aux!=EOF)
  { 
    
    if(i==tam)
    {     
     pu=reallocUsuario(pu,totalUsuario);
     tam=*totalUsuario;
    }

    leLogin(&pu[i],u,aux);
    leSenha(&pu[i],u);
    i++;
    aux=fgetc(u);
  }

  //printf("tamanho=%d\n",i);
  //retorna a quantidade de usuarios alocada 
  *tamAloc=i; 
  return pu;
}


void preencheInativos(tUsuario *pu,FILE *a, int tamUsuarios)
{
  
  char c;
  //pega o primeiro caractere
  c=fgetc(a);
  //se o arquivo estiver vazio
  if(c==EOF)
  {
    //printf("vazio\n");
    //esta vazio
    //inicializa com 0;
    for(int j=0;j<tamUsuarios;j++)
    {
      pu[j].inativo='0';
    }
  }
  else{
  //caso já exista o arquivo

  pu[0].inativo=c;
  fgetc(a);
  //ler o \n;
  
  for(int j=1;j<tamUsuarios;j++)
    {
      c=fgetc(a);
      pu[j].inativo=c;
      fgetc(a);
      //ler o \n      
    }
  }
}

int verificaLogin(tUsuario *pu, int tam, char *nome)
{   
  int i;
  for(i=0;i<tam;i++)
  {
    if(strcmp(nome,pu[i].login)==0)
    {
      //strings iguais 
      //i eh a posicao da tad que confere com o usuario digitado
      return i;
    }
  }
  //nao ha usuario igual
  //numero invalido sob o ponto de vista de posicao 
  return -1; 
}

int verificaSenha(tUsuario *pu, int posicao, char *senha,int *usuario)
{
  if(strcmp(senha,pu[posicao].senha)==0)
    {
      //strings iguais 
      //indica o usuario que esta navegando
      *usuario=posicao;
      return 0;
    }
  //numero invalido sob o ponto de vista de posicao 
  //senha incorreta
  return -1;
}

int verificaCadastro(tUsuario *pu, int tam, int *usuario, int verbosidade)
{
  int x=0;
  char nome[TAM_MAX];
  scanf("%s",nome);
  
  x=verificaLogin(pu,tam,nome);

  if(x==-1)
  {
    printf("Usuario nao cadastrado\n");
    x=menuLogin(verbosidade);
    return x;
  }

  if(pu[x].inativo=='1')
  {
    printf("Conta inativa\n");
    x=menuLogin(verbosidade);
    return x;
  }

  char senha[TAM_MAX];
  scanf("%s",senha);

  x=verificaSenha(pu,x,senha,usuario);

  if(x==-1)
  {
    printf("Senha incorreta\n");
    x=menuLogin(verbosidade);
    return x;
  }
  //usuario e senha no sistema entao retorna 4, numero arbitrariamente escolhido(diferente de 1,2,3)
  system("clear");
  return 4;
}

void alocaNovoUsuario(tUsuario *p,char *nome, char *senha, int tamNome, int tamSenha)
{
  for(int i=0; i<tamNome; i++)
  {
    p->login[i]=nome[i];
  }

  for(int j=0; j<tamSenha; j++)
  {
    p->senha[j]=senha[j];
  }

  p->inativo='0';

}

int verificaNomeSenha(char *nome)
{
  int x=0;
  int tam=strlen(nome);

  for(int i=0; i<tam ; i++)
  {
     if( !( (nome[i]>47 && nome[i]<58) || (nome[i]>64 && nome[i]<91) || (nome[i]>96 && nome[i]<123) ) )
    {
      //nao estiver no intervalo alfanumerico
      //usuario fora do padrao     
     return -1;
    }
  }
  //passando desse for, todos os caracteres são validos
  //retornando tamanho para facilitar na atribuiçao na tad
  return tam;
}

int cadastrarUsuario(tUsuario *pu,int *quantUsuario, int *usuario, int verbosidade)
{
  ////////////////ANALISANDO LOGIN ////////////////
  int tam=*quantUsuario;

  char nome[TAM_MAX];
  int tamNome;
  int x=0;
  
  printf("Usuario: ");
  //e necessario ler o \n do op1, pois influencia no segmento do problema
  scanf("\n %[^\n]",nome);

  tamNome=verificaNomeSenha(nome);

  if(tamNome==-1)
  {
    printf("Usuario fora do padrao\n");
    x=menuLogin(verbosidade);
    return x;
  }
  else
  {
    //verificar se ja nao existe usuario com o mesmo nome
    if(verificaLogin(pu,tam,nome)==-1)
    {
      //nao ha usuarios iguais no tad
      //para facilitar so vou armazenar o usuario depois de verificar a senha
      x=4;
    }
    else
    {
      printf("Usuario ja cadastrado\n");
      x=menuLogin(verbosidade);
      return x;
    }
  }
  ////////////////ANALISANDO SENHA ////////////////

  char senha[TAM_MAX];
  char confirma[TAM_MAX];
  int tamSenha;
  int y=0;

  printf("Senha:");
  //necessario ler o \n por causa do enter do nome de usuario
  scanf("\n %[^\n]",senha);
 
  tamSenha=verificaNomeSenha(senha);

  if( tamSenha==-1)
  {
    printf("Senha fora do padrao\n");
    x=menuLogin(verbosidade);
    return x;
  }
  else
  {
     printf("Confirmar senha:");
    //necessario ler o \n por causa do enter do nome de usuario
    scanf("\n %[^\n]",confirma);
    
    //verificar se as senhas sao compativeis
    if(strcmp(senha,confirma)==0)
    {
      //senhas compativeis
      //atribuir usuario e senha na tad 
      alocaNovoUsuario(&pu[tam],nome,senha,tamNome,tamSenha);//usuario do sistema
      *usuario=tam;
      //mais um usuario cadastrado
      *quantUsuario=tam+1;    

      return 4;
    }
    else
    {
      printf("Senha incorreta\n");
      x=menuLogin(verbosidade);
      return x;
    }
  }
}

void gravaLogin(FILE *u,tUsuario *pu, int posicao)
{
  //passando login para o arquivo
  fprintf(u, "%s", pu[posicao].login);
  //gravando a virgula padrao 
  fputc(',',u);
}

void gravaSenha(FILE *u,tUsuario *pu, int posicao)
{
  //passando senha para o arquivo
  fprintf(u, "%s", pu[posicao].senha);
  //gravando a virgula padrao 
  fputc('\n',u);
}

void salvaUsuarios(tUsuario *pu, FILE *u,int quantUsuarios)
{
  for(int i=0;i<quantUsuarios;i++)
  {
   gravaLogin(u,pu,i);
   gravaSenha(u,pu,i); 
  }

}

void salvaInativos(tUsuario *pu, int quantUsuarios, FILE *a)
{
  for(int i=0;i<quantUsuarios;i++)
  {
    fputc(pu[i].inativo,a);
    fputc('\n',a);
  }
}

void liberaInativos(char *inativos)
{
  if(inativos!=NULL)
  {
    free(inativos);
  }
}

int inativaUsuario(tUsuario *pu, int posicao)
{
  pu[posicao].inativo='1';
  printf("Conta excluida\n"); 
  //salvar alteraçoes e sair  
  //para voltar para o primeiro menu
  return 4;    
}

int sairQuatro(tUsuario *pu, int posicao, int verbosidade)
{
  int x;
  if(pu[posicao].inativo=='1')
  {
    //tem que sair do prgrama
    return 3;
  }
  else
  {
  //reseta o usuario que esta no sistema
  posicao=-1;
  return menuLogin(verbosidade);
  }
}

void imprimeInicioOrdenacao(tUsuario pu)
{
  printf("Nome: %s\n",pu.login);
  printf("Meu historico:\n");
}