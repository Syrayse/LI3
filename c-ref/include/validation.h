#ifndef VALIDATION_H
#define VALIDATION_H

#define VRF_CLIENT 0
#define VRF_PRODUCT 1
#define VRF_SALE 2

typedef struct verifier *VRF_OBJ;

VRF_OBJ make_vrf (void);
int vrf_obj_str (VRF_OBJ,char*,int);
void destroy_vrf (VRF_OBJ);

#endif