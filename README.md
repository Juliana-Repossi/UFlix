# Trabalho Prático  I - TEP - UFLix 
Prof. Vinicíus Mota 
DI/UFES

Alunos: 
  - Juliana Repossi 
  - Christian Junji

## Considerações
Para tornar a leitura de arquivos mais simples, separamos o historico em um outro .csv, assim como a informação de inatividade dos usuários. Dessa forma, existem dois arquivos .csv a mais: inativos.csv e historico.csv.

O arquivo historico.csv está organizado sendo cada linha do arquivo correspondente à um usuário e o número da linha que estão as informações é correspondente à linha do usuario no usuario.csv.

De modo análogo, a organização do arquivo inativos.csv está de forma que cada linha corresponda à linha do usuario no usuarios.csv.

Decidimos, também, por fazer todas as strings serem alocadas dinamicamente, comportando apenas o espaço necessário para elas, para que assim o seu tamanho seja de acordo com o que o usuário digitar.

## Bibliotecas
Decidimos por separar as funções em 5 bibliotecas, da forma mais modularizada possivel, com o objetivo de atender às regras de implementação de TADs.
### filmes.h: 
Reúne todas as funções que envolvem a manipulação e carregamento dos filmes com exceção das funções que gravariam no histórico, para fins de organização.

### historico.h:
Agrega todas as funções e TADs para a construção do histórico e sua ordenação, seja dele propriamente dito ou de alguma ferramenta para manipulá-lo. 
 
### menu.h:
Conjunto dos menus. Cada menu ou o que foi necessário para construir o menu.

### usuarios.h:
Agrupa todas as funções e TADs necessárias para lidar com o tipo tUsuario, seja para usar suas informações, aletrá-las ou consultá-las.

### utils.h:
Biblioteca que reúne as funções utilitárias que não se encaixariam em outras bibliotecas.
