#ifndef _CURRIER_
#define _CURRIER_

typedef struct currier *Currier;

Currier currier_make(void *key, void *value, void *user_data);
void currier_destroy(Currier cr);
void *uncurry_by_key(Currier cr);
void *uncurry_by_value(Currier cr);
void *uncurry_by_user(Currier cr);

#endif