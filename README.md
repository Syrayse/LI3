# Summary LI3

Correr na pasta `./c-ref/src/` o comando `make program` irá compilar automaticamente todos os módulos, desde que estes possuam o interface corretamente definido. A importação da _glib_ é feita de modo automático pelo _Makefile_. Todos os ficheiros objeto(__.o__) são armazenados na diretoria `./c-ref/src/obj/`. Todos os ficheiros header (__.h__) devem ser armazenados na diretoria `./c-ref/include/` de forma a permitir o correto funcionamento da _Makefile_. Todas as estruturas básicas de dados que se pretendam criar ou alterar devem estar ou ser adicionadas na diretoria `./c-ref/src/lib`.

### OBJETIVOS E NOTAS DE APOIO TÉCNICO

__O que se pede na fase 2?__

Não incluido o sistema de I/O que é pedido nas várias queries do enunciado.

11. Criar uma lista dos N produtos mais vendidos em todo o ano, indicando o número total de clientes e o número de unidades vendidas, filial a filial. __NOT IMPLEMENTED__.

## Repartição

#### Ana 'Jónni' Almeida

* Idealizar o design do programa que vai comunicar com o utilizador. Como apresentar a informação ao utilizador? Que delimitações devem ser feitas de tal modo que o utilizador consiga aceder a todas as estatisticas sobre o seu supermercado? Pensar no paradigma de _navegadores_ e _cursores_ que é falado no enunciado de LI3.

#### André 'Pistolas' Figueiredo

* Realizar a tarefa __(11)__. (next fim de semana)

#### Rui 'Small Dick Joe' Reis

* All done.

#### Em grupo, cristão

* Desenvolver módulos _navegadores_ e _cursores_.
* Criar relatorio.
* Implementar uma forma eficiente de leitura adaptativa, de tal modo, que seja qual for o tamanho da linha que se pretende ler, seja possivel ler sem gerar _segmentation fault_.

### REFERÊNCIAS

https://developer.gnome.org/glib/stable/glib-Hash-Tables.html
