/**
 * @file set.h
 * \brief Interface de todos os metódos que permitem a interação com instâncias da classe `Set`.
 * 
 * Esta classe permite que dada uma chave exista uma correspondência unívoca à mesma ou ao valor anexado a esta.
 */

#ifndef SET_H
#define SET_H

#include <glib.h>

/**
 * \brief Tipo opaco representativo de uma instância da classe `Set`.
 */
typedef struct set *Set;

/**
 * \brief Redefine uma função que deve ser usada como atualizador de um elemento.
 */
typedef void (*f_update)(gpointer, gpointer);

/**
 * \brief Redefine uma função que deve ser usada como criadora da instância pretendida.
 */
typedef gpointer (*f_maker)();

/**
 * \brief Cria e inicializa uma instância da classe `Set`.
 * 
 * Esta função atualmente recebe só paramêtros como funções,
 * este parametros correspondem às diferentes propriedades das chaves e valores existentes.
 * 
 * Para além de funções de igualdade, mapeamento e libertação de memória, podem ser
 * também passadas como argumento funções que permitem criar e atualizar valores associados a chaves.
 * 
 * A função do tipo `f_maker` define de que forma são criados os valores anexados a cada chave,
 * de tal forma que quando se pretende inserir uma chave que não existe no _set_, para além de adicionada
 * a chave é também adicionado como seu valor anexado, o resultado da chamar a função `f_maker`.
 * 
 * A função do tipo `f_update` permite definir como se pretende que o valor anexado a cada chave
 * seja atualizado quando se adiciona mais informação sobre a chave.
 * 
 * A únicas funções essenciais ao funcionamento interno do `Set` são os dois primeiros argumentos,
 * se estes não forem passados então o conjunto retornado é NULL. Todos os outros paramêtros, exceto
 * os dois primeiros podem ser passados como NULL.
 * 
 * @param hash_f Função de _hash_ que deve ser aplicada às chaves.
 * @param key_equal_f Função que testa se duas chaves são iguais.
 * @param ffkey Função que define como deve ser libertada a memória associada às chaves.
 * @param ffvalue Função que define como deve ser libertada a memória associada os valores das chaves.
 * @param fm Função que permite criar em memória novos valores.
 * @param fu Função que permite atualizar os valores de cada chave.
 * 
 * @returns A instância criada, ou NULL caso não sejam passadas funções de _hash_ e de igualdade.
 */
Set set_make(GHashFunc hash_f, GEqualFunc key_equal_f, GFreeFunc ffkey, GFreeFunc ffvalue, f_maker fm, f_update fu);

/**
 * \brief Permite libertar a memória associada à instància da classe `Set`.
 * 
 * Para além de libertar a memória associada à instância, são também libertadas
 * as chaves e valores segundo as funções de destruição passadas como argumento
 * aquando da criação do `Set`.
 * 
 * @param set Conjunto que se pretende libertar.
 */
void set_destroy(Set set);

/**
 * \brief Permite adicionar uma chave ao conjunto, e para além disso atualizar o valor anexado à chave.
 * 
 * Esta função permite adicionar uma certa chave a um conjunto, e para além disso, dependendo das funções de update
 * fornecidas aquando da criação do conjunto, é também atualizado o valor associado àquela chave.
 * 
 * @param set Conjunto no qual se pretende adicionar.
 * @param key Chave de acesso ao conjunto.
 * @param user_data Informação utilizada na atualização do valor anexado à chaves respectiva. Se for passado NULL então não é efetuado nenhum update.
 * 
 * @returns 1 caso a chave já exista, 0 caso contrário.
 */
int set_add(Set set, gpointer key, gpointer user_data);

/**
 * \brief Remove e liberta a respectiva memória associada a uma chave no conjunto.
 * 
 * @param set Conjunto a considerar.
 * @param key Chave de acesso ao conjunto.
 * 
 * @returns 1 se a chave for encontrada a libertada, 0 caso contrário.
 */
int set_remove(Set set, gpointer key);

/**
 * \brief Aplica uma função a todas as chaves e respectivos valores no conjunto.
 * 
 * @param set Conjunto a considerar.
 * @param fe Função que será aplicada a todos os elementos do conjunto.
 * @param user_data Informação adicional, útil à função de iteração.
 */
void set_foreach(Set set, GHFunc fe, gpointer user_data);

/**
 * \brief Verifica se uma certa chave existe no conjunto
 * 
 * @param set Conjunto a considerar.
 * @param ket Chave de acesso ao conjunto.
 * 
 * @returns 1 caso a chave exista no conjunto, 0 caso contrário.
 */
int set_contains(Set set, gpointer key);

/**
 * \brief Calcula o número de elementos no conjunto.
 * 
 * @param set Conjunto a considerar.
 * 
 * @returns O número de elementos no conjunto.
 */
int set_size(Set set);

/**
 * \brief Indica o valor anexado a uma certa chave no conjunto.
 * 
 * @param set Conjunto a considerar.
 * @param key Chave de acesso ao conjunto.
 * 
 * @returns O valor associado à chave, ou NULL caso a chave não exista no conjunto ou a chave não possua valores associados.
 */
gpointer set_lookup(Set set, gpointer key);

#endif