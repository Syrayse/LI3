#ifndef UTIL_H
#define UTIL_H

/**
 * \brief Indexador dos códigos promocionais.
 **/
#define indP(a) ((a) == ('N') ? 0 : 1)

enum utils
{
    N_MONTHS = 12,
    N_FILIAIS = 3,
    N_PROMOS = 2,
    PROD_LEN = 6,
    CLT_LEN = 5,
    N_LETTER = 26,
    N_TRANS_ARGS = 7,
    PROD_ID = 0,
    CLT_ID = 1
};

/**
 * \brief Verifica se x se encontra entre dois limites.
 **/
#define is_between(x, min, max) ((x >= min) && (x <= max))

/**
 * \brief Mínimo entre dois números.
 **/
#define min(a, b) ((a) < (b) ? (a) : (b))

/**
 * \brief Maximo entre dois números.
 **/
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef void (*freefunc)(void *);

typedef int (*fcompare)(const void *, const void *);

typedef int (*Predicate)(const void *, const void *);

typedef struct currier *Currier;

typedef unsigned int gID;

typedef unsigned char UChar;

void is_null(void *a);
int mystrcmp(const void *a, const void *b);
int conv_str(const void *key);
Currier currier_make(void *key, void *value);
void currier_destroy(void *c);
void *uncurry_by_key(void *c);
void *uncurry_by_value(void *c);
int compare_quants(const void *a, const void *b);
void foreach_add_g_currier(void *key, void *value, void *user_data);

#endif