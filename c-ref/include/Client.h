/**
 * @file Client.h
 * \brief Define a interface de metódos aplicáveis em instâncias da classe `Client`.
 * 
 * Esta interface visa facilitar a comunicação com entidades externa que pretendam obter informação
 * de um instância de `Client`. Este módulo está especificamente desenhado de forma a facilitar a sua integração
 * em tabelas de hash, através de metódos `client_hash` e `client_equal`.
 */
#ifndef __CLIENT_ADT__
#define __CLIENT_ADT__

#include <glib.h>

/**
 * \brief Tipo opaco representativo de uma instância da classe `Client`.
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

/**
 * \brief Em vez de passar como argumento um client passa-se um tipo abstrato de dados que representa este.
 * 
 * Está função é utilizada unicamente para evitar warnings do compilador.
 *
 * @param v Tipo abstrato de dados que representa o client
 */
void wrapclient_destroy(gpointer v);

#endif