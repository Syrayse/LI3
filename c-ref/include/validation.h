#ifndef VALIDATION_H
#define VALIDATION_H

#include "dbase.h"
#include "sale.h"

/**
 * \brief Define indicativo de que se pretende verificar a validez de uma venda.
 **/
#define VRF_SALE -1

/**
 * \brief Define indicativo de que se pretende verificar a validez de um produto.
 **/
#define VRF_PRODUCT 0

/**
 * \brief Define indicativo de que se pretende verificar a validez de um cliente.
 **/
#define VRF_CLIENT 1

/**
 * \brief Conjunto de delimatores utilizados para tokenizar um string.
 **/
#define BASE_DELIM " \r\n"

typedef struct verifier *VRF_OBJ;

VRF_OBJ make_vrf(void);
int vrf_obj_str(VRF_OBJ, void *, void *, char *, int);
void destroy_vrf(VRF_OBJ);
int validate_s(DBase, DBase, SALE);

#endif