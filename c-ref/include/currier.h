#ifndef CURRIER_H
#define CURRIER_H

typedef struct currier *Currier;

Currier currier_make(void *key, void *value, void *user_data);
void currier_destroy(void *c);
void *uncurry_by_key(Currier c);
void *uncurry_by_value(Currier c);
void *uncurry_by_user(Currier c);

#endif