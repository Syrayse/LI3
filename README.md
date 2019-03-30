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

### PREVIOUS STATE

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

### CURRENT STATE
```
query1:
	Sucessfully read file product tests/Produtos.txt, with 171008 valids and 171008 in total!
	Sucessfully read file client tests/Clientes.txt, with 16384 valids and 16384 in total!
	Sucessfully read file sale tests/Vendas_1M.txt, with 891108 valids and 1000000 in total!
CPU Time:1.357566
query2:
	A -> 6578
	examples: AA1001 AA1006 AA1011 AA1017 AA1022 
	B -> 6562
	examples: BA1003 BA1005 BA1020 BA1023 BA1031 
	C -> 6558
	examples: CA1000 CA1002 CA1010 CA1012 CA1020 
	D -> 6749
	examples: DA1001 DA1010 DA1016 DA1022 DA1023 
	E -> 6560
	examples: EA1005 EA1013 EA1018 EA1019 EA1024 
	F -> 6493
	examples: FA1001 FA1004 FA1013 FA1015 FA1019 
	G -> 6450
	examples: GA1001 GA1010 GA1014 GA1027 GA1031 
	H -> 6465
	examples: HA1014 HA1015 HA1019 HA1023 HA1025 
	I -> 6670
	examples: IA1000 IA1002 IA1003 IA1006 IA1030 
	J -> 6577
	examples: JA1008 JA1012 JA1015 JA1021 JA1025 
	K -> 6497
	examples: KA1001 KA1004 KA1010 KA1015 KA1017 
	L -> 6548
	examples: LA1008 LA1011 LA1014 LA1020 LA1023 
	M -> 6651
	examples: MA1007 MA1015 MA1016 MA1019 MA1020 
	N -> 6593
	examples: NA1008 NA1009 NA1015 NA1020 NA1024 
	O -> 6639
	examples: OA1000 OA1001 OA1005 OA1008 OA1020 
	P -> 6580
	examples: PA1002 PA1011 PA1014 PA1015 PA1017 
	Q -> 6593
	examples: QA1005 QA1008 QA1010 QA1011 QA1022 
	R -> 6510
	examples: RA1005 RA1007 RA1012 RA1013 RA1017 
	S -> 6413
	examples: SA1004 SA1007 SA1009 SA1019 SA1023 
	T -> 6677
	examples: TA1005 TA1007 TA1008 TA1011 TA1012 
	U -> 6592
	examples: UA1006 UA1011 UA1013 UA1019 UA1023 
	V -> 6454
	examples: VA1001 VA1002 VA1007 VA1009 VA1012 
	W -> 6650
	examples: WA1003 WA1009 WA1011 WA1017 WA1019 
	X -> 6587
	examples: XA1005 XA1007 XA1014 XA1017 XA1023 
	Y -> 6741
	examples: YA1000 YA1005 YA1007 YA1012 YA1017 
	Z -> 6621
	examples: ZA1003 ZA1017 ZA1020 ZA1031 ZA1032 
CPU Time:0.029832
query3:
	Para o produto AF1184:
	Month 6
	For filial 1:
		Sales, Promo 1, No Promo 1
		Revenue, Promo 60210.890000, No Promo 791.120000
	For filial 2:
		Sales, Promo 0, No Promo 0
		Revenue, Promo 0.000000, No Promo 0.000000
	For filial 3:
		Sales, Promo 0, No Promo 0
		Revenue, Promo 0.000000, No Promo 0.000000
	In all:
		Sales, Promo 1, No Promo 1
		Revenue, Promo 60210.890000, No Promo 791.120000
CPU Time:0.000012
query4:
	In total weren't bought 928, examples: AA1022 AA1143 AA1236 AB1432 AB1643 
	Filial 1, weren't bought 30006, examples: AA1022 AA1032 AA1055 AA1075 AA1081 
	Filial 2, weren't bought 30205, examples: AA1006 AA1022 AA1041 AA1081 AA1112 
	Filial 3, weren't bought 30083, examples: AA1022 AA1038 AA1078 AA1092 AA1134 
CPU Time:0.029884
query5:
	A total of 16384 clients bought in all, examples: A1231 A1234 A1238 A1240 A1242 
CPU Time:0.003880
query6:
	A total of 0 clients didn't buy
	A total of 928 products weren't sold
CPU Time:0.000002
query7:

	For client Z500:
		|1|	|2|	|3|

	mes1	99	0	502
	mes2	183	46	248
	mes3	0	23	16
	mes4	186	76	142
	mes5	156	41	267
	mes6	167	0	0
	mes7	344	201	532
	mes8	71	65	121
	mes9	292	115	0
	mes10	127	7	320
	mes11	30	497	337
	mes12	19	360	175
CPU Time:0.000022
query8:
	In the range [1,3], 222421 transactions were registred
	In the range [1,3], the cashflow was 11186236943.299974
CPU Time:0.000003
query9:

	For product AF1184:
	-> 1 For transactions without promotion, examples: J3976 
	-> 3 For transactions with promotion, examples: F3550 W2450 W3157 
CPU Time:0.000005
Query 10:

	For client Z5000:
	Para o mes 1 foram encontrados 7 produtos distintos:
		1º: LC1788
		2º: VA1543
		3º: ZQ1560
		4º: UY1955
		5º: IL1829
		6º: CO1951
		7º: FE1784
CPU Time:0.000009
Query 11:
O produto CC1684, foi o 1º mais vendido
O produto XU1621, foi o 2º mais vendido
O produto IP1934, foi o 3º mais vendido
O produto KE1836, foi o 4º mais vendido
O produto QG1283, foi o 5º mais vendido
O produto WS1261, foi o 6º mais vendido

CPU Time:0.238021
free:
CPU Time:0.145988
total:
CPU Time:1.805258
```

Para 200 amostras
build	Q1	Q2	Q3	Q4	Q5	Q6	Q7	Q8	Q9	Q10	Q11	Q12	free	

AVERAGE: 
	
	build -> 1,336806125
	Q1 -> 0,030384005
	Q2 -> 1,7865E-05
	Q3 -> 0,02991901
	Q4 -> 0,00358831
	Q5 -> 1,81E-06
	Q6 -> 2,3405E-05
	Q7 -> 4,705E-06
	Q8 -> 4,76E-06
	Q9 -> 8,28499999999998E-06
	Q10 -> 0,231458695
	Q11 -> 4,637E-05
	Q12 -> 0,13412446
	free -> 0,134128855	

STDEV: 
```
build -> 0,024961581571731
Q1 -> 0,001251178702546
Q2 -> 4,22920867659078E-06
Q3 -> 0,00133025958471
Q4 -> 0,000350208141843
Q5 -> 1,26566565400925E-06
Q6 -> 2,08149902497089E-06
Q7 -> 1,1421460009286E-06
Q8 -> 1,81628590050185E-06
Q9 -> 8,41018167335846E-07
Q10 -> 0,006523694126587
Q11 -> 5,81136471054734E-06
Q12 -> 0,002966739000974
free -> 0,002966790249732	
```
