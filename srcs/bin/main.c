#include "../include/libs.h"

int main(void)
{
    t_main  main;

    gather_addresses(&main, "AssaultCube");
    infinite_ammo(&main);
    terminate(&main);
    return (0);
}

