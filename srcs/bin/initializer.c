#include "../include/libs.h"

static void    initialize_structures(t_main *main)
{
    memset(main, 0, sizeof(t_main));
    printf("[x] Initialized all structures.\n");
    return ;
}

static void  get_process_infos(t_main *main, char *window)
{
    main->process.hwindow = FindWindowA(NULL, window);
    if (!main->process.hwindow)
        throw_error(main, "[!] Error getting window handle\n");
    GetWindowThreadProcessId(main->process.hwindow, &main->process.pid);
    if (!main->process.pid)
        throw_error(main, "[!] Error getting PID\n");
    main->process.hprocess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, main->process.pid);
    if (!main->process.hprocess)
        throw_error(main, "[!] Error getting process handle\n");
    printf("[x] Grabbed following infos:\n\
    > hwindow: %p\n\
    > pid: %lu\n\
    > hprocess: %p\n", main->process.hwindow, main->process.pid, main->process.hprocess);
}

static void    get_module_base_address(t_main *main)
{
    HANDLE              snapshot;
    MODULEENTRY32       module;
    int                 res;

    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, main->process.pid);
    module.dwSize = sizeof(MODULEENTRY32);
    if (Module32First(snapshot, &module))
    {
        while (strcmp("ac_client.exe", module.szModule) != 0 && res != 0)
            res = Module32Next(snapshot, &module);
    }
    main->process.base_addr = (uintptr_t)module.modBaseAddr;
    printf("    > Base module address: %p\n", (void *)main->process.base_addr);
    CloseHandle(snapshot);
}

static void    get_player_addresses(t_main *main)
{
    uint32_t    static_ptr;
    SIZE_T      lp_byte_read;
    int         buf;

    // PLAYER BASE
    static_ptr = main->process.base_addr + 0x17E0A8;
    ReadProcessMemory(main->process.hprocess, (LPCVOID)static_ptr, &main->player.base_addr,\
     4, &lp_byte_read);
    printf("    > Player base: 0x%X\n", main->player.base_addr);
    if (main->player.base_addr == 0)
        throw_error(main, "[!] Error getting player base address\n");

    // PLAYER DATA (BASE ADDR + OFFSETS)
    // ammo (0x140)
    main->player.ammo_addr = main->player.base_addr + 0x140;
    ReadProcessMemory(main->process.hprocess, (LPCVOID)main->player.ammo_addr, &buf,\
     4, NULL);
    printf("    > Ammo address (%d left): 0x%X\n", buf, main->player.ammo_addr);
    // health TODO (0xF8)
}

void    gather_addresses(t_main *main, char *window)
{
    initialize_structures(main);
    get_process_infos(main, window);
    get_module_base_address(main);
    get_player_addresses(main);
    printf("[x] Everything has been gathered successfully.\n");
}