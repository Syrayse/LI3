/**
 * @file Accounting.h
 * \brief Interface de metódos públicos que permitem a interação com instâncias da classe `Accounting`.
 * 
 * Esta classe tem como objetivo tratar das contas do serviço SVG.
 */

#ifndef ACCOUNTING_H
#define ACCOUNTING_H

#include "Verifier.h"
#include "statinfo.h"

typedef struct accounting *Accounting;

Accounting Accounting_make();
void Accounting_destroy(Accounting a);
void Accounting_update(Accounting a, Transaction t);
void Accounting_add_product(Accounting a, char *product);
int Accounting_n_trans_range(Accounting a, int init, int end);
double Accounting_n_cash_range(Accounting A, int init, int end);
StatInfo Accounting_get_statinfo(Accounting a, char *product);

#endif