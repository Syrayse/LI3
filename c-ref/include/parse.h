#ifndef PARSE_H
#define PARSE_H

/**
 * \brief Define indicativo da flag de parse de um produto.
 **/
#define PRS_PRODUCT -1

/**
 * \brief Define indicativo da flag de parse de uma venda.
 **/
#define PRS_SALE 0

/**
 * \brief Define indicativo da flag de parse de um cliente.
 **/
#define PRS_CLIENT 1

typedef struct parser *PRS_OBJ;

PRS_OBJ make_prs (void);
int prs_obj_str (PRS_OBJ,void*,char*,int);
void destroy_prs (PRS_OBJ);

#endif