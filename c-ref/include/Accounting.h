#ifndef ACCOUNTING_H
#define ACCOUNTING_H

#include "util.h"
#include "transaction.h"
#include "statinfo.h"

typedef struct accounting *Accounting;

Accounting Accounting_make();
void Accounting_destroy(Accounting a);
void Accounting_add(Accounting a, Transaction t);
int Accounting_n_trans(Accounting a);
int Accounting_n_trans_month(Accounting a, int month);
int Accounting_n_trans_range(Accounting a, int init, int end);
double Accounting_t_cash(Accounting a);
double Accounting_t_cash_month(Accounting a, int month);
double Accounting_n_cash_range(Accounting A, int init, int end);
void Accounting_iter(Accounting a, gID *id_arr, int N, void (*f_iter)(Transaction, void *), void *user_data);
StatInfo Accounting_get_statinfo(Accounting a, gID *id_arr, int N);
gID Accounting_get_next_id(Accounting a);

#endif