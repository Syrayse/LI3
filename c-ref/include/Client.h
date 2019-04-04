/**
 * @file Product.h
 * \brief Define a interface de metódos aplicáveis em instâncias da classe `Product`.
 * 
 * Esta interface visa facilitar a comunicação com entidades externa que pretendam obter informação
 * de um instância de `Product`. Este módulo está especificamente desenhado de forma a facilitar a sua integração
 * em tabelas de hash, através de metódos `product_hash` e `product_equal`.
 */
#ifndef __CLIENT_ADT__
#define __CLIENT_ADT__

#include <glib.h>

/**
 * \brief Define o tamanho de um código de cliente.
 */
#define CLIENT_LEN 5

/**
 * \brief Tipo opaco representativo da classe `Product`.
 */
typedef struct client *Client;

/**
 * \brief Permite criar uma instância da classe `Client`.
 * 
 * @param client_code O código associado a um certo `Client`.
 * 
 * @returns Um nova instância.
 */
Client client_make(char *client_code);

/**
 * \brief Destrói uma instância da classe `Client`.
 * 
 * @param c Instância a destruir.
 */
void client_destroy(Client c);

/**
 * \brief Permite criar uma instância que é uma cópia exata de outra instância.
 * 
 * @param c Instância que se pretende copiar.
 * 
 * @returns Instância cópia.
 */
Client client_clone(Client c);

/**
 * \brief Obtem uma cópia do código associado à instância.
 * 
 * @param c instância a considerar.
 * 
 * @returns Cópia do código associado à instância.
 */
char *client_get_code(Client c);

/**
 * \brief Calcula o _hash code_ de uma instância da classe `Client`.
 * 
 * @param v Instância a considerar.
 * 
 * @returns _Hash code_ calculado.
 */
guint client_hash(gconstpointer v);

/**
 * \brief Verifica se duas instâncias são iguais.
 * 
 * @param v1 Primeira instância a considerar.
 * @param v2 Segunda instância a considerar.
 * 
 * @returns`TRUE` se as instâncias forem iguais, `FALSE` caso contrário.
 */
gboolean client_equal(gconstpointer v1, gconstpointer v2);

#endif