#include "../include/menu.h"
#include "../include/filmes.h"
#include "../include/usuarios.h"
#include "../include/historico.h"


int main(int argc, char **argv){

  /*verbosidade recebida como argumento*/
  int verbosidade;
  if(argv[1] == NULL || (atoi(argv[1]) != 0 && atoi(argv[1]) != 1))
  {
    printf("Verbosidade inválida!\n");
    exit(1);
  }
  verbosidade = atoi(argv[1]);

  
 /////////////////ABERTURA DOS ARQUIVOS CSV/////////////////

  /*abertura do arquivo de usuarios*/
  FILE *u = fopen("data/usuarios.csv", "r");
  /*testando a abertura do arquivo usuario*/
  testaAberturaUsuario(u);

  /*abertura do arquivo de filmes*/
  FILE *f = fopen("data/filmes-grande.csv", "r");
  /*testando a abertura do arquivo filme*/
  testaAberturaFilmes(f);


  /////////////////ALOCANDO AS INFORMACOES CSV /////////////////
  
  /////DE FILME///////

  /*ponteiro para alocar um vetor tFilme*/
  tFilme *pf = allocVetorFilmes();
  testaPonteiroFilmes(pf);  

  /*carregando filmes para a estrutura de alocacao dinamica criada*/
  carregaFilmes(pf,f);

  /////DE USUARIO///////

  /*primeiro tamanho de alocação da estrutura usuario*/
  int totalUsuario=TAM_USUA;
  int tamUsuario=0;

  /*declarando ponteiro para usuario e
  alocando dinamicamente as estruturas de usuario*/
  tUsuario *pu=allocaVetorUsuario(totalUsuario);
  testaPonteiroUsuario(pu);
  
  /*copiando dados do arquivo para a estrutura dinamica*/
  pu=carregaUsuario(pu,u,&totalUsuario,&tamUsuario);
  /*tamUsuario e totalUsuario passando por referencia para atualizar os valores sem precisar retornar*/
 
  /*carregar um arquivo csv para guardar se o usuario é ativo ou n*/
  FILE *a=fopen("data/inativos.csv","a+");
  testaAberturaInativos(a);
  
  /*preenchendo o valor inativo na struct tUsuario*/
  preencheInativos(pu,a,tamUsuario);

  ///////DE HISTORICO/////////

  /*abertura do arquivo do historico*/
  FILE *hist = fopen("data/historico.csv", "a+");
  /*testando a abertura do arquivo historico*/
  testaAberturaHistorico(hist);
  
  /*preciso saber o numero de filmes assitidos por usuario*/
  tHalocado *quant=allocaQuant(totalUsuario);

  /*inicializando com o tamanho alocado maximo por usuario na estrutura*/   
  /*Estrutura dinamica do historico*/
  tHistorico **h=allocaHistorico(totalUsuario,quant);  
    
  /*carregando historico do csv para a estrutura dinamicamente*/
  carregaHistorico(hist,h,quant);

  /*variaveis para receber comandos do usuario para selecionar o menu*/
  int op1, op2;

  //primeiro menu e recebendo a opcao escolhida
  op1=menuLogin(verbosidade);

  //indica qual ususario esta no sistema
  int qualUsuario=-1;

  //switch case para direcionar o usuario na operacao que ele escolheu
  //do-while para possibilitar a volta no switch case, ou seja a volta no menu anterior
  //o primeiro do-while: para voltar do segundo menu para o primeiro
  do
  {
    //se vier de uma exclusao de conta tem que sair sem dar a possibilidade de outro login, para salvar que excluiu a conta
    if(qualUsuario!=-1 && pu[qualUsuario].inativo=='1')
    {
      op1=3;
    }

   //o segundo do-while: para voltar do primeiro menu para ele mesmo
    do
    {
      switch(op1)
      {
        case 1:
        //funcao que le o login 
        op1=verificaCadastro(pu,tamUsuario,&qualUsuario, verbosidade); 
        break;

        case 2:
        //condicional de realloc (caso aloque mais usuarios do que o tamanho inicial alocado)
        if(totalUsuario==tamUsuario)
        {
          int tamAntigo=totalUsuario;
          pu=reallocUsuario(pu,&totalUsuario); 
          //se aumenta o numero total de usuarios e necessario aumentar tambem  historico
          h=reallocaHistorico(h,tamAntigo,totalUsuario,quant); 
        }    
        //cadastrar usuario        
        op1=cadastrarUsuario(pu,&tamUsuario,&qualUsuario, verbosidade);
        //ta ok: printf("%d",qualUsuario); 
        break;

        case 3:       
        //libera o ponteiro filme
        liberaFilmes(pf);
        
        //libera o ponteiro do csv filme
        fclose(f);

        //fecha os arquivos csv, depois vou abrir em outro formato para salvar;
        fclose(u);
        fclose(a);

        //abrir o arquivo limpo agora atraves do modo w que substitui o conteudo
        FILE *a = fopen("data/inativos.csv", "w");
        //testando a abertura do arquivo usuario
        testaAberturaInativos(a);        
        
        //salvar todas informaçoes da estrutura dinamica no csv
        salvaInativos(pu,tamUsuario,a);

        //fecha o arquivo
        fclose(a);        
              
        //abrir o arquivo limpo agora atraves do modo w que substitui o conteudo
        FILE *u = fopen("data/usuarios.csv", "w");
        //testando a abertura do arquivo usuario
        testaAberturaUsuario(u);
        
        //salvar todas informaçoes da estrutura dinamica tUsuario
        salvaUsuarios(pu,u,tamUsuario);

        //fecha o arquivo
        fclose(u);   
        //libera o ponteiro usuario
        desalocaUsuario(pu,totalUsuario);

        //Fecha o arquivo do historico
        fclose(hist);

        //abertura do arquivo do historico
        FILE *hist = fopen("data/historico.csv", "w");
        //testando a abertura do arquivo historico
        testaAberturaHistorico(hist);

        //salvando o historico
        salvaHistorico(h,quant,hist,totalUsuario);

        //libera o ponteiro quant
        free(quant);
        //libera o ponteiro de ponteiro h
        liberaHisto(h,totalUsuario);

        //fecha o arquivo csv HISTORICO
        fclose(hist);

        exit(1);
        break;
      }
    }while(op1!=4);

    char op;
    char *nome;
    
    //do while para retornar ao menu principal, se op2==0;
    do{
      op2=menuPrincipal(verbosidade);
      switch(op2)
      {

        case 1:
          //teste lista de filmes
          //pegando o \n
          getchar();
          op2=menuListaFilmes(pf,qualUsuario,hist,h,quant, verbosidade); 
        break;

        case 2:
          op=opcaoDois();  

          switch(op)
          {
            case 'D':
            imprimeInicioOrdenacao(pu[qualUsuario]);
            op2=ordenaData(h[qualUsuario],quant[qualUsuario],pf);
           
            break;

            case 'N':
            imprimeInicioOrdenacao(pu[qualUsuario]);
            ordenaNota(h[qualUsuario],quant[qualUsuario],pf);
            
            op2=0;
            break;

            case '2':
            //inativar usuario
            op2=inativaUsuario(pu,qualUsuario);    
            break;

            case'3':
            op2=0;
            break;
          } 
              
        break;

        case 3:
          op2 = menuProcuraFilmes(pf, qualUsuario, hist,h,quant, verbosidade);
        break;

        case 4:
          op1=sairQuatro(pu,qualUsuario, verbosidade);          
        break;
      }
    }while(op2==0);
  }while(op2==4);

return 0;
}