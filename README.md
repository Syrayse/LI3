# Summary LI3

Correr na pasta `~/c-ref/src/` o comando `make program` irá compilar automaticamente todos os módulos, desde que estes possuam o interface corretamente definido. A importação da _glib_ é feita de modo automático pelo _Makefile_. Todos os ficheiros objeto(__.o__) são armazenados na diretoria `~/c-ref/src/obj/`. Todos os ficheiros header (__.h__) devem ser armazenados na diretoria `~/c-ref/include/` de forma a permitir o correto funcionamento da _Makefile_.

Na versão corrente encontram-se definidos e testados os seguintes módulos:

* `validation`
* `sale`
* `kheap` -> talvez alterar funcionamento interno.
* `parse`

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

### PROJECT'S CHECKPOINTS

##### Ideia para implementação eficiente da verificação efetiva de um registo de venda
Primeiro ler os ficheiros `Clientes.txt` e `Produtos.txt`, criar duas _hash tables_ contendo informação de cada um destes ficheiros, após devidamente validada, e de seguida à medida que se lê cada registo de venda, verificar nas _hash tables_ a existências dos valores descritos. Neste caso verifica se o produto existe e se o cliente existe.
Tendo em conta que o tempo amortizado de `g_hash_table_contains` é O(1) então espera-se que esta verificação não traga um maior custo à função de _parsing_.


referências:
https://developer.gnome.org/glib/stable/glib-Hash-Tables.html
