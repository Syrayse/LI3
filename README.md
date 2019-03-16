# Summary LI3

Correr na pasta `./c-ref/src/` o comando `make program` irá compilar automaticamente todos os módulos, desde que estes possuam o interface corretamente definido. A importação da _glib_ é feita de modo automático pelo _Makefile_. Todos os ficheiros objeto(__.o__) são armazenados na diretoria `./c-ref/src/obj/`. Todos os ficheiros header (__.h__) devem ser armazenados na diretoria `./c-ref/include/` de forma a permitir o correto funcionamento da _Makefile_. Todas as estruturas básicas de dados que se pretendam criar ou alterar devem estar ou ser adicionadas na diretoria `./c-ref/src/lib`.

### OBJETIVOS E NOTAS DE APOIO TÉCNICO

__O que se pede na fase 2?__

Não incluido o sistema de I/O que é pedido nas várias queries do enunciado.

1. Ler os 3 ficheiros (Produtos, Clientes e vendas), cujos nomes poderão ser introduzidos pelo utilizador ou, opcionalmente, assumidos por omissão. __DONE @ `main.c`__.
2. Determinar a lista ordenada e o nº total de produtos cujo código se inicia por uma dada letra (maiúscula). __DONE @ StrSet in `strset_dump_ordered`__.
3. Dado um mês e um código de produto determinar o número total de vendas e o total facturado com esse produto em tal mês, distinguido entre modo N e modo P, permitir resultado global ou por filial. __DONE @ StatInfo__
4. Determinar a lista ordenada dos códigos dos produtos (e o seu total) que ninguém comprou, valores totais ou por filial. __DONE @ DBase :: `GrowingArray not_bought[4]`__
5. Determinar a lista ordenada de códigos de clientes que realizaram compras em todas as filiais. __DONE @ DBase in `dbase_get_overall`__
6. Determinar o número de clientes registados que não realizaram compras bem como o número de produtos que ninguém comprou. __DONE @ DBase :: `int not_init_n`__.
7. Dado um código de cliente, criar uma tabela com o numero total de produtos comprados por mes e por filial. __API DONE, FALTA INTERFACE__
8. Dado um intervalo fechado de meses, por exemplo [1..3], determinar  total de vendas registadas nesse intervalo e o total facturado. __NOT DONE__.
9. Dado um código de produto e uma filial, determinar os códigos (e número total) dos clientes que o compraram, distinguindo entre compra N e compra P. __NOT DONE__.
10. Dado um código de cliente e um mês, determinar a lista de códigos de produtos que mais comprou por quantidade e não por facturação. __NOT DONE__.
11. Criar uma lista dos N produtos mais vendidos em todo o ano, indicando o número total de clientes e o número de unidades vendidas, filial a filial. __NOT IMPLEMENTED__.
12. Dado um código de cliente determinar quais os códigos do 3 produtos em que mais gastou dinheiro durante o ano. __NOT IMPLEMENTED__.

## Repartição

#### Ana 'Jónni' Almeida

* Idealizar o design do programa que vai comunicar com o utilizador. Como apresentar a informação ao utilizador? Que delimitações devem ser feitas de tal modo que o utilizador consiga aceder a todas as estatisticas sobre o seu supermercado? Pensar no paradigma de _navegadores_ e _cursores_ que é falado no enunciado de LI3.

#### André 'Pistolas' Figueiredo

* Realizar a tarefa __(8)__. (fim de semana)
* Realizar a tarefa __(11)__. (next fim de semana)

#### Rui 'Small Dick Joe' Reis

* Realizar a tarefa __(9)__.
* Realizar a tarefa __(10)__.
* Realizar a tarefa __(12)__.
(domingo)

#### Em grupo, cristão

* Desenvolver módulos _navegadores_ e _cursores_.
* Criar relatorio.
* Implementar uma forma eficiente de leitura adaptativa, de tal modo, que seja qual for o tamanho da linha que se pretende ler, seja possivel ler sem gerar _segmentation fault_.

### REFERÊNCIAS

https://developer.gnome.org/glib/stable/glib-Hash-Tables.html
