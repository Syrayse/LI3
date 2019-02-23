# Summary LI3

Correr na pasta `~/c-ref/src/` o comando `make program` irá compilar automaticamente todos os módulos, desde que estejam possuam o interface corretamente definido. A importação da _glib_ é feita de modo automático o _Makefile_. Todos os ficheiros objeto(.o) são armazenados na diretoria `~/c-ref/src/obj/`.

Na versão corrente encontram-se definidos e testados os seguintes ódulos:

* `validation`
* `sale`
* `kheap`

Objetivo principal a 23/02/2019:

* Criar um módulo de `parse` utilizando os módulos `sale` e `validation`.