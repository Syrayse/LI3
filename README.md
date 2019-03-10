# Summary LI3

Correr na pasta `~/c-ref/src/` o comando `make program` irá compilar automaticamente todos os módulos, desde que estes possuam o interface corretamente definido. A importação da _glib_ é feita de modo automático pelo _Makefile_. Todos os ficheiros objeto(__.o__) são armazenados na diretoria `~/c-ref/src/obj/`. Todos os ficheiros header (__.h__) devem ser armazenados na diretoria `~/c-ref/include/` de forma a permitir o correto funcionamento da _Makefile_.

Na versão corrente encontram-se definidos os seguintes módulos:

* `validation`, contém todas as funções necessárias para a validação de um produto,cliente ou registo de venda possui tanto validação semântica (estar bem escrito) como validação efetiva (por exemplo, nos registos de vendas os clientes e produtos ambas existirem na base dados).
* `sale`, contém todas as funções necessárias para trabalhar com a estrutura de dados que foi estabelecida como sendo a representativa de um registo de vendas na nossa versão atual.
* `mainstruct`, módulo que contém a base dados, esta estrutura está completamente encapsulada, de modo a nos facilitar testes com outras estruturas para bases de dados. Todas as alterações que pretendam alterar o funcionamento como são processados os clientes ou produtos e as estatisticas associadas a estes devem utilizar a respetiva API deste modulo.
* `appender`, este modulo contem a estrutura de dados que fica na base de dados (mainstruct) associada a cada cliente ou produto. O conteudo desta estrutura é basicamente dados estatisticos que uma empresa precisa de ter(vendas,lucro,...) por cada cliente/produto. A estrutura appender é igual para o cliente e para o produto.
* `vendasman`, este é modulo mais importante, visto que de momento é a cola que liga todos os outros de forma a formar um programa solido que é capaz de nos fornecer todas as informações que precisamos. Todas as alterações que pretendam alterar o funcionamento geral do programa devem ser feitas aqui.

* `util.h`, neste header file, que não é um modo, encontram-se várias macros que podem ser uteis para programar de uma forma mais fácil. basta fazer `#include "util.h"` para tirar partido das mesmas.

### OBJETIVOS E NOTAS DE APOIO TÉCNICO

De momento, terminamos a fase 1 do projeto. O nosso projeto de momento já não está apto a resolver a fase 1 da forma mais eficiente, pois já foram realizados updates que visam adaptar para a fase 2. Daí, __se nos for pedido o benchmarking especificamente da fase 1 deve ser feito um rollback ao commit 53__, e neste ser alterado a forma como é guardado o ultimo utilizador lido, para que a cada novo utilizador não precise de alocar mais espaço (como temos agora feito). O commit __53__ com essa alteração representa a versão mais eficiente para a fase 1 que possuimos.

__O que se pede na fase 2?__

Não incluido o sistema de I/O que é pedido nas várias queries do enunciado.

1. Ler os 3 ficheiros (Produtos, Clientes e vendas), cujos nomes poderão ser introduzidos pelo utilizador ou, opcionalmente, assumidos por omissão. __NOT IMPLEMENTED__.
2. Determinar a lista ordenada e o nº total de produtos cujo código se inicia por uma dada letra (maiúscula). __NOT IMPLEMENTED__.
3. Dado um mês e um código de produto determinar o número total de vendas e o total facturado com esse produto em tal mês, distinguido entre modo N e modo P, permitir resultado global ou por filial. __CURRENTLY IMPLEMENTED, pelos módulos `appender` e `mainstruct`__.
4. Determinar a lista ordenada dos códigos dos produtos (e o seu total) que ninguém comprou, valores totais ou por filial. __NOT IMPLEMENTED__.
5. Determinar a lista ordenada de códigos de clientes que realizaram compras em todas as filiais. __CURRENTLY IMPLEMENTED, desde 10/03/2019__.
6. Determinar o número de clientes registados que não realizaram compras bem como o número de produtos que ninguém comprou. __CURRENTLY IMPLEMENTED, desde 10/03/2019__.
7. Dado um código de cliente, criar uma tabela com o numero total de produtos comprados por mes e por filial. __CURRENTLY IMPLEMENTED, na API do `appender` só falta o I/O com o utilizador__.
8. Dado um intervalo fechado de meses, por exemplo [1..3], determinar  total de vendas registadas nesse intervalo e o total facturado. __NOT IMPLEMENTED__.
9. Dado um código de produto e uma filial, determinar os códigos (e número total) dos clientes que o compraram, distinguindo entre compra N e compra P. __NOT IMPLEMENTED__.
10. Dado um código de cliente e um mês, determinar a lista de códigos de produtos que mais comprou por quantidade e não por facturação. __NOT IMPLEMENTED__.
11. Criar uma lista dos N produtos mais vendidos em todo o ano, indicando o número total de clientes e o número de unidades vendidas, filial a filial. __NOT IMPLEMENTED__.
12. Dado um código de cliente determinar quais os códigos do 3 produtos em que mais gastou dinheiro durante o ano. __NOT IMPLEMENTED__.

## Repartição

Devido ao aumento da complexidade associada a esta segunda fase, apresenta-se a seguinte proposta de repartição de trabalho pelos membros do grupo:

#### Ana 'Jónni' Almeida

* Realizar a tarefa __(1)__.
* Escolher a melhor ferramenta para gerar documentação automatica, e criar guia para os outros membros perceberem como cada função deve estar comentada de forma a gerar a melhor documentação na respetiva ferramenta.
* Idealizar o design do programa que vai comunicar com o utilizador. Como apresentar a informação ao utilizador? Que delimitações devem ser feitas de tal modo que o utilizador consiga aceder a todas as estatisticas sobre o seu supermercado? Pensar no paradigma de _navegadores_ e _cursores_ que é falado no enunciado de LI3.

#### André 'Pistolas' Figueiredo

* Implementar uma forma eficiente de leitura adaptativa, de tal modo, que seja qual for o tamanho da linha que se pretende ler, seja possivel ler sem gerar _segmentation fault_.
* Realizar a tarefa __(2)__.
* Realizar a tarefa __(8)__.
* Realizar a tarefa __(11)__.


#### Rui 'Small Dick Joe' Reis
* Realizar a tarefa __(4)__.
* Realizar a tarefa __(5)__.
* Realizar a tarefa __(6)__. __DONE__
* Realizar a tarefa __(9)__.
* Realizar a tarefa __(10)__.
* Realizar a tarefa __(12)__.

#### Em grupo, cristão
* Desenvolver módulos _navegadores_ e _cursores_.
* Benchmarking.
* Estudo de possiveis leaks de memoria.
* Debater complexidade de algoritmos atuais e a possibilidade de melhorar.
* Criar relatorio.

#### Nota importante:

É imperativo que cada membro, ao desenvolver o seu código tenho a atenção de comentar devidamente e estrutura o código de forma a manter o que é pedido sobre encapsulamento.

### PRIMEIRO BOLETIM PEDIDO (`LI3_BRP_1`).

```C

FIM DA LEITURA DO Vendas_1M.txt
A maior linha tem tamanho 32
Produtos envolvidos: 171008
Clientes envolvidos: 16384
Vendas efectivas: 891108
Ultimo cliente: Q4462
Numero de vendas regitadas para o cliente Q4462: 48
Numero de vendas registadas na filial 1: 296989
Numero de vendas registadas na filial 2: 296799
Numero de vendas registadas na filial 3: 297320
A:523
B:628
C:687
D:660
E:670
F:560
G:558
H:629
I:716
J:674
K:651
L:545
M:587
N:708
O:688
P:647
Q:528
R:553
S:709
T:691
U:666
V:588
W:498
X:613
Y:738
Z:669
Faturacao total: 44758896640.000000
CPU Time:1.321149

```

### REFERÊNCIAS

https://developer.gnome.org/glib/stable/glib-Hash-Tables.html
