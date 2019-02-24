#ifndef VALIDATION_H
#define VALIDATION_H

#define VRF_SALE -1
#define VRF_PRODUCT 0
#define VRF_PRICE 1
#define VRF_UNITS 2
#define VRF_PROMO 3
#define VRF_CLIENT 4
#define VRF_MONTH 5
#define VRF_FILIAL 6

typedef struct verifier *VRF_OBJ;

VRF_OBJ make_vrf (void);
int vrf_obj_str (VRF_OBJ,char*,int);
void destroy_vrf (VRF_OBJ);

#endif