# Summary LI3

Correr na pasta `~/c-ref/src/` o comando `make program` irá compilar automaticamente todos os módulos, desde que estes possuam o interface corretamente definido. A importação da _glib_ é feita de modo automático pelo _Makefile_. Todos os ficheiros objeto(__.o__) são armazenados na diretoria `~/c-ref/src/obj/`. Todos os ficheiros header (__.h__) devem ser armazenados na diretoria `~/c-ref/include/` de forma a permitir o correto funcionamento da _Makefile_.

Na versão corrente encontram-se definidos e testados os seguintes módulos:

* `validation`
* `sale`
* `kheap` -> talvez alterar funcionamento interno.
* `parse` -> este módulo foi removido pelo branch `RR/efficiency_up`, que atualizou o módulo `validation` de forma a realizar as funções do antigo módulo `parse`.

### OBJETIVOS E NOTAS DE APOIO TÉCNICO

##### Benchmarking a 25/02/2019 da verificação semântica de todos os registos de vendas.

### PROJECT'S CHECKPOINTS

### NOTAS SOBRE O PRIMEIRO BOLETIM PEDIDO (`LI3_BRP_1`).

## DONE

### REFERÊNCIAS

https://developer.gnome.org/glib/stable/glib-Hash-Tables.html
