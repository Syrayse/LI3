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
