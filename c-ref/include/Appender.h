/**
 * @file Appender.h
 * \brief API correspondente aos dados que devem ser anexados aos produtos na contabilidade.
 */

#ifndef __APPENDER__
#define __APPENDER__

#include "Verifier.h"

typedef struct appender *Appender;

void *Appender_make();
void Appender_destroy(void *app);
void Appender_update(void *app, void *user_data);
void Appender_iterate_overall(Appender app, void (*f_iter)(Transaction, void *), void *user_data);
void Appender_iterate_filial(Appender app, int filial, void (*f_iter)(Transaction, void *), void *user_data);

#endif