# Summary LI3

Correr na pasta `~/c-ref/src/` o comando `make program` irá compilar automaticamente todos os módulos, desde que estes possuam o interface corretamente definido. A importação da _glib_ é feita de modo automático pelo _Makefile_. Todos os ficheiros objeto(__.o__) são armazenados na diretoria `~/c-ref/src/obj/`. Todos os ficheiros header (__.h__) devem ser armazenados na diretoria `~/c-ref/include/` de forma a permitir o correto funcionamento da _Makefile_.

Na versão corrente encontram-se definidos e testados os seguintes módulos:

* `validation`
* `sale`
* `kheap` -> talvez alterar funcionamento interno.
* `parse`

Objetivo principal a 25/02/2019:
* Pensar numa forma de retirar a necessidade de aplicar a mesma função duas vezes por cada elemento que se pretende verificar quando se está a fazer o parse e a verificação.
* Aplicar GHash para verificar validação efetiva (para além de semântica).
* Pensar numa forma eficiente de verificar se o registo de compra/venda é efetivamente válido.

Notas sobre a utilização e funções úteis da glib:
* Usar g_hash_table_new para criar uma nova hash table de base.
* Podemos utilizar o metódo g_hash_table_contains de forma a verificar as relações entre clientes, produtos e vendas.
* Usar g_str_hash para fazer hash dos códigos de produtos/clientes.
* usar g_str_equal para fazer testes de igualdade de códigos de produtos/clientes.
* utilizando hash table da glib verifica-se que se está num caso de eficiência máxima quando as key's são os próprios values. (talvez inutil).
* g_hash_table_lookup pode ser muito util se decidirmos utilizar um valor a uma dada chave.

Que tipo de utilidade se podia dar a este 'value'?
* Talvez o 'value' podia conter todos os registos de vendas associados a um dado cliente, a um dado produto. De qualquer forma que nos fosse mais agradável.

referências:
https://developer.gnome.org/glib/stable/glib-Hash-Tables.html
