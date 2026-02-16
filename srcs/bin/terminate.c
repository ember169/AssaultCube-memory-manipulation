#include "../include/libs.h"

void    throw_error(t_main *main, char *errmsg)
{
    write(2, errmsg, strlen(errmsg));
    terminate(main);
}

void    terminate(t_main *main)
{
    CloseHandle(main->process.hwindow);
    CloseHandle(main->process.hprocess);
    if (main->ent.bots)
        free(main->ent.bots);
    printf("[i] Clean exit...\n");
    exit(1);
}