#ifndef APPENDER_H
#define APPENDER_H

// Information append to keys.
typedef struct appendix *APPENDER;

APPENDER make_appender();
void update_appender(APPENDER, void *);
int get_app_vendas(APPENDER);
void destroy_appender(void *);

#endif