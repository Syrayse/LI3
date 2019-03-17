#ifndef SPEC_INFO_H
#define SPEC_INFO_H

typedef struct specific_info *SpecInfo;

SpecInfo specinfo_make(int flag);
void specinfo_destroy(SpecInfo si);
void specinfo_update(SpecInfo si, void *e);
int specinfo_get_promo_fil(SpecInfo si, int filial);
int specinfo_get_no_promo_fil(SpecInfo si, int filial);
int specinfo_get_units_month(SpecInfo si, int month);
double specinfo_get_cost(SpecInfo si);

#endif