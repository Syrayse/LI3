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

### CURRENT STATE

```
tarefa 1:	CPU Time:2.446231
	A: size -> 6578
	Examples: AA1001 AA1006 AA1011 AA1017 AA1022 
	B: size -> 6562
	Examples: BA1003 BA1005 BA1020 BA1023 BA1031 
	C: size -> 6558
	Examples: CA1000 CA1002 CA1010 CA1012 CA1020 
	D: size -> 6749
	Examples: DA1001 DA1010 DA1016 DA1022 DA1023 
	E: size -> 6560
	Examples: EA1005 EA1013 EA1018 EA1019 EA1024 
	F: size -> 6493
	Examples: FA1001 FA1004 FA1013 FA1015 FA1019 
	G: size -> 6450
	Examples: GA1001 GA1010 GA1014 GA1027 GA1031 
	H: size -> 6465
	Examples: HA1014 HA1015 HA1019 HA1023 HA1025 
	I: size -> 6670
	Examples: IA1000 IA1002 IA1003 IA1006 IA1030 
	J: size -> 6577
	Examples: JA1008 JA1012 JA1015 JA1021 JA1025 
	K: size -> 6497
	Examples: KA1001 KA1004 KA1010 KA1015 KA1017 
	L: size -> 6548
	Examples: LA1008 LA1011 LA1014 LA1020 LA1023 
	M: size -> 6651
	Examples: MA1007 MA1015 MA1016 MA1019 MA1020 
	N: size -> 6593
	Examples: NA1008 NA1009 NA1015 NA1020 NA1024 
	O: size -> 6639
	Examples: OA1000 OA1001 OA1005 OA1008 OA1020 
	P: size -> 6580
	Examples: PA1002 PA1011 PA1014 PA1015 PA1017 
	Q: size -> 6593
	Examples: QA1005 QA1008 QA1010 QA1011 QA1022 
	R: size -> 6510
	Examples: RA1005 RA1007 RA1012 RA1013 RA1017 
	S: size -> 6413
	Examples: SA1004 SA1007 SA1009 SA1019 SA1023 
	T: size -> 6677
	Examples: TA1005 TA1007 TA1008 TA1011 TA1012 
	U: size -> 6592
	Examples: UA1006 UA1011 UA1013 UA1019 UA1023 
	V: size -> 6454
	Examples: VA1001 VA1002 VA1007 VA1009 VA1012 
	W: size -> 6650
	Examples: WA1003 WA1009 WA1011 WA1017 WA1019 
	X: size -> 6587
	Examples: XA1005 XA1007 XA1014 XA1017 XA1023 
	Y: size -> 6741
	Examples: YA1000 YA1005 YA1007 YA1012 YA1017 
	Z: size -> 6621
	Examples: ZA1003 ZA1017 ZA1020 ZA1031 ZA1032 
tarefa 2:	CPU Time:0.038191
	Product:	NR1091
	Vendas:		3
	Revenue:	245035.200000
	Buyers:		3
tarefa 3:	CPU Time:0.000022
	In total 928 products were not bought, examples: AA1022 AA1143 AA1236 AB1432 AB1643 
	filial 1, 30006 not bought, examples: AA1022 AA1032 AA1055 AA1075 AA1081 
	filial 2, 30205 not bought, examples: AA1006 AA1022 AA1041 AA1081 AA1112 
	filial 3, 30083 not bought, examples: AA1022 AA1038 AA1078 AA1092 AA1134 
tarefa 4:	CPU Time:0.032058
	In total 0 clients didn't buy, examples: 
tarefa 5:	CPU Time:0.001741
	In total 171008 products didn't sell
	In total 16384 clients didn't buy
tarefa 6:	CPU Time:0.000005
	mes 1 filial 1 bought 2!
	mes 2 filial 1 bought 1!
	mes 4 filial 1 bought 1!
	mes 5 filial 1 bought 2!
	mes 6 filial 1 bought 1!
	mes 7 filial 1 bought 3!
	mes 8 filial 1 bought 1!
	mes 9 filial 1 bought 2!
	mes 10 filial 1 bought 2!
	mes 11 filial 1 bought 2!
	mes 12 filial 1 bought 1!

	mes 2 filial 2 bought 2!
	mes 3 filial 2 bought 1!
	mes 4 filial 2 bought 1!
	mes 5 filial 2 bought 1!
	mes 7 filial 2 bought 2!
	mes 8 filial 2 bought 2!
	mes 9 filial 2 bought 1!
	mes 10 filial 2 bought 1!
	mes 11 filial 2 bought 3!
	mes 12 filial 2 bought 3!

	mes 1 filial 3 bought 5!
	mes 2 filial 3 bought 3!
	mes 3 filial 3 bought 1!
	mes 4 filial 3 bought 1!
	mes 5 filial 3 bought 2!
	mes 7 filial 3 bought 4!
	mes 8 filial 3 bought 2!
	mes 10 filial 3 bought 2!
	mes 11 filial 3 bought 3!
	mes 12 filial 3 bought 2!

	mes 1 bought 7!
	mes 2 bought 6!
	mes 3 bought 2!
	mes 4 bought 3!
	mes 5 bought 5!
	mes 6 bought 1!
	mes 7 bought 9!
	mes 8 bought 5!
	mes 9 bought 3!
	mes 10 bought 5!
	mes 11 bought 8!
	mes 12 bought 6!
tarefa 7:	CPU Time:0.000142
	Entre 1 e 3 houve 222421 vendas registadas
	Entre 1 e 3 facturou-se 11186236943.299974!
tarefa 8:	CPU Time:0.000008
	O top 3 do cliente Z5000 é: MU1740 WD1962 UW1170 
tarefa 12:	CPU Time:0.000022
destroy:	CPU Time:1.071385
total:		CPU Time:3.589901
```

### REFERÊNCIAS

https://developer.gnome.org/glib/stable/glib-Hash-Tables.html
