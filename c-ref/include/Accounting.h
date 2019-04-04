/**
 * @file Accounting.h
 * \brief Interface de metódos públicos que permitem a interação com instâncias da classe `Accounting`.
 * 
 * Esta classe tem como objetivo tratar das contas do serviço SVG.
 */

#ifndef ACCOUNTING_H
#define ACCOUNTING_H

typedef struct accounting *Accounting;

Accounting Accounting_make();
void Accounting_destroy(Accounting a);
void Accounting_update(Accounting a, char *product, int month, int filial, int units, int promo, double spent);
int Accounting_n_trans_range(Accounting a, int init, int end);
double Accounting_n_cash_range(Accounting a, int init, int end);
int Accounting_get_global_stats(Accounting a, char *product, int month, int *trans_vec, int *spent_vec);
int Accounting_get_per_filial_stats(Accounting a, char *product, int month, int **trans_vec, int **spent_vec);

#endif