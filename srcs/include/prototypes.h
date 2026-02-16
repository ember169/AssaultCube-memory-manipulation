#ifndef PROTOTYPES_H
# define PROTOTYPES_H

void    throw_error(t_main *main, char *errmsg);
void    terminate(t_main *main);
void    gather_addresses(t_main *main, char *window);
void    offset_scan(t_main *main);
unsigned int    __stdcall hack_thread(void *arg);
void    refresh_debug_ui(t_main *main);

#endif