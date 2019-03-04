#ifndef APPENDER_H
#define APPENDER_H

// Information append to keys.
typedef struct appendix *APPENDER;

APPENDER make_appender();
void update_appender(void *);
int get_app_vendas(APPENDER);
void destroy_appender(APPENDER);

#endif