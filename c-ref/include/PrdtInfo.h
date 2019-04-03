#ifndef _PRDTINFO_
#define _PRDTINFO_

typedef struct prdtinfo * PrdtInfo;

void *prdtinfo_make();
void prdtinfo_destroy(void *e);
void prdtinfo_update(void *e, void *user_data);
double prdtinfo_total_spent(PrdtInfo pi);
int prdtinfo_month_units(PrdtInfo pi, int month);

#endif