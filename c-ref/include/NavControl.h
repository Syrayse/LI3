#ifndef __CONTROL_NAVIGATOR__
#define __CONTROL_NAVIGATOR__

typedef void (*f_print)(void *);

typedef struct nav_control *NavControl;

NavControl NavControl_make();
void NavControl_destroy(NavControl nc);
void NavControl_change_dict(NavControl nc, void **dict, void *user_data, int size, f_print fp_elem, f_print fp_user);
int NavControl_next_page(NavControl nc);
int NavControl_previous_page(NavControl nc);

#endif