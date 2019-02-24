#ifndef VALIDATION_H
#define VALIDATION_H

/**
 * \brief Define indicativo de que se pretende verificar a validez de uma venda.
 **/
#define VRF_SALE -1

/**
 * \brief Define indicativo de que se pretende verificar a validez de um produto.
 **/
#define VRF_PRODUCT 0

/**
 * \brief Define indicativo de que se pretende verificar a validez de um preço.
 **/
#define VRF_PRICE 1

/**
 * \brief Define indicativo de que se pretende verificar a validez de unidades.
 **/
#define VRF_UNITS 2

/**
 * \brief Define indicativo de que se pretende verificar a validez de um código promocional.
 **/
#define VRF_PROMO 3

/**
 * \brief Define indicativo de que se pretende verificar a validez de um cliente.
 **/
#define VRF_CLIENT 4

/**
 * \brief Define indicativo de que se pretende verificar a validez de um mês.
 **/
#define VRF_MONTH 5

/**
 * \brief Define indicativo de que se pretende verificar a validez de uma filial.
 **/
#define VRF_FILIAL 6

/**
 * \brief Conjunto de delimatores utilizados para tokenizar um string.
 **/
#define BASE_DELIM " \r\n"

typedef struct verifier *VRF_OBJ;

VRF_OBJ make_vrf (void);
int vrf_obj_str (VRF_OBJ,char*,int);
void destroy_vrf (VRF_OBJ);

#endif