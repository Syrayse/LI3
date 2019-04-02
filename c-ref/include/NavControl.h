/**
 * @file NavControl.h
 * \brief Define a interface dos metódos públicos associados à class `NavControl`.
 * 
 * Através desta classe é possivél transversar informação de uma forma mais dinâmica
 * seguindo a ideia de páginas, sendo possivél passar uma página para trás ou para a frente.
 * 
 * De forma a ser utilizavél é preciso passar um dicionário do qual vai ser feita a leitura dinâmica, e como se pretende
 * que este seja imprimido. Depois disso este é tratado de como um livro de trata-se estando limitado a um número
 * fixo de entradas por cada página.
 */

#ifndef __CONTROL_NAVIGATOR__
#define __CONTROL_NAVIGATOR__

/**
 * \brief Typedef para simplificar a escrita de uma função que tem a capacidade de impressão.
 */
typedef void (*f_print)(void *);

typedef struct nav_control *NavControl;

NavControl NavControl_make();
void NavControl_destroy(NavControl nc);
void NavControl_change_dict(NavControl nc, void **dict, void *user_data, int size, f_print fp_elem, f_print fp_user);
int NavControl_next_page(NavControl nc);
int NavControl_previous_page(NavControl nc);

#endif