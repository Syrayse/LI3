# Summary LI3

Correr na pasta `~/c-ref/src/` o comando `make program` irá compilar automaticamente todos os módulos, desde que estes possuam o interface corretamente definido. A importação da _glib_ é feita de modo automático pelo _Makefile_. Todos os ficheiros objeto(__.o__) são armazenados na diretoria `~/c-ref/src/obj/`. Todos os ficheiros header (__.h__) devem ser armazenados na diretoria `~/c-ref/include/` de forma a permitir o correto funcionamento da _Makefile_.

Na versão corrente encontram-se definidos e testados os seguintes módulos:

* `validation`
* `sale`
* `kheap` -> talvez alterar funcionamento interno.
* `parse` -> este módulo foi removido pelo branch `RR/efficiency_up`, que atualizou o módulo `validation` de forma a realizar as funções do antigo módulo `parse`.

### OBJETIVOS E NOTAS DE APOIO TÉCNICO

Objetivo principal a 25/02/2019:
* Pensar numa forma de retirar a necessidade de aplicar a mesma função duas vezes por cada elemento que se pretende verificar quando se está a fazer o parse e a verificação.
* Aplicar `GHash` para verificar validação efetiva (para além de semântica).

Notas sobre a utilização e funções úteis da glib:
* Usar `g_hash_table_new` para criar uma nova hash table de base.
* Podemos utilizar o metódo `g_hash_table_contains` de forma a verificar as relações entre clientes, produtos e vendas.
* Usar `g_str_hash` para fazer _hash_ dos códigos de produtos/clientes.
* usar `g_str_equal` para fazer testes de igualdade de códigos de produtos/clientes.
* utilizando a _hash table_ da _glib_ verifica-se que se está num caso de eficiência máxima quando as _key's_ são os próprios _values_. (talvez inutil).
* `g_hash_table_lookup` pode ser muito útil se decidirmos utilizar um valor a uma dada chave.

Que tipo de utilidade se podia dar a este _value_?
* Talvez o _value_ possa conter todos os registos de vendas associados a um dado cliente, a um dado produto. De qualquer forma que nos fosse mais agradável.

##### Benchmarking a 25/02/2019 da verificação semântica de todos os registos de vendas.
RAM: 5,7 GiB

CPU: Intel® Core™ i5-5200U CPU @ 2.20GHz × 4 

GPU: Intel® HD Graphics 5500 (Broadwell GT2)

Utilizando o comando `time` da _bash_ a versão atual demora 0.91s a verificar semânticamente todas as vendas do ficheiro `Vendas_1M.txt`.

Após aplicada a branch `RR/efficiency-up`, exatamente o mesmo procedimento passou a demorar 0.57s.

### PROJECT'S CHECKPOINTS

##### Ideia para retirar a necessidade de fazer _parse_ duas vezes do mesmo valor.
Na versão corrente deste program há duas vezes por cada registo de venda que são efetuadas funções de parse que sucedem aquando da verificação e no parse efetivo. Funções do género `atof` e `atoi` são executadas duas vezes por registo, e estas aparentam ser dispendiosas. Daí provém a necessidade encurtar o número de execuções destas funções para só uma por registo. A ideia para alcançar este objetivo é criar uma estrutura auxiliar que à medida que válida estes valores coloca-os dentro duma _dummy structure_ que guarda a informação proveniente destas funções "caras". Retirando assim a necessidade de execucões repetidas.

##### Ideia para implementação eficiente da verificação efetiva de um registo de venda.
Primeiro ler os ficheiros `Clientes.txt` e `Produtos.txt`, criar duas _hash tables_ contendo informação de cada um destes ficheiros, após devidamente validada, e de seguida à medida que se lê cada registo de venda, verificar nas _hash tables_ a existências dos valores descritos. Neste caso verifica se o produto existe e se o cliente existe.
Tendo em conta que o tempo amortizado de `g_hash_table_contains` é O(1) então espera-se que esta verificação não traga um maior custo à função de _parsing_.

##### Onde verificar este predicado?
Na função `prs_obj_str` deve ser adicionado um argumento que corresponde a um _tuplo_ de 2 tabelas de _hash_, um representa os clientes todos e outro representa os produtos existentes. Quando a `prs_obj_str` recebe a flag `PRS_CLIENT` ou `PRS_PRODUCT` deve adicionar os elementos que conseguir fazer _parse_ às respetivas tabelas de _hash_. Porém quando recebe a flag `PRS_SALE` e verifica que de facto a string recebida é válida, deve ser efetuado um ultimo teste predicado, que verifica ambas as tabelas de _hash_.

### NOTAS SOBRE O PRIMEIRO BOLETIM PEDIDO (`LI3_BRP_1`).
1. __LINHA MAIS LONGA (VENDA)__ : Não faço a minima ideia como podemos fazer isto utilizando a estrutura atual o programa.
2. __PRODUTOS ENVOLVIDOS__ : A função `g_hash_table_insert` retorna `TRUE` se o elemento que se pretende adicionar à _hash table_ não existir previamente nesta. Para contar o numero de produtos envolvidos basta contar quantas vezes a função retorna `TRUE` ao adicionar numa _hash table_ de produtos. O(1).
3. __CLIENTES ENVOLVIDOS__ : Aparentemente pode ser resolvida da mesma forma que a questão de produtos envolvidos. O(1).
4. __VENDAS EFETIVAS__ : Fazer a validação semântica atual, e para além disso verificar que ambos os clientes e produtos existem nas _hash tables_ acima referenciadas. O que possui um custo amortizado de O(1).
5. __ULTIMO CLIENTE__ : Guardar um registo único para armazenar o ultimo cliente. O(1).
6. __NUMERO DE VENDAS ASSOCIADAS A UM DADO CLIENTE__ : Adicionar à _hash table_ para além da própria _key_, um _value_ que contém associada a cada cliente informação sucinta deste no sistema. Por exemplo, o número de compras que este efetuou, em que filiais, e o seu histórico de compras. O(1).
7. __NUMERO DE VENDAS NA FILIAL N__ : Guardar num array o número de vendas associadas a cada filial, após feito o parse a obtenção deste valor é O(1).
8. __NUMERO DE CLIENTES COM CODIGO COMEÇADO POR A, B, ...?__ : Guardar num array com ('Z'-'A'+1) slots, o número de codigos de clientes começados com as letras especificadas, por ordem crescente. O(1).
9. __FATURAÇÃO TOTAL REGISTADA__ : Guardar numa estrutura principal esta informação à medida que se vai lendo.

### DÚVIDAS PARA A AULA DE 26/02/2019.
* Temos de criar outro ficheiro só com vendas válidas? Porque?

### REFERÊNCIAS

https://developer.gnome.org/glib/stable/glib-Hash-Tables.html
