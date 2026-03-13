# AssaultCube client memory manipulation
![Illustration](https://github.com/user-attachments/assets/018a3a5e-3c3d-4390-bbc0-f78f7fc4e218)<br>
This project is a very basic external hack for [AssaultCube](https://assault.cubers.net/), a cross-platform open source FPS released in 2008.<br>

## Description
I made this project as an introduction on memory manipulation and binary hacking. Understanding how memory works and can be compromised is key to better code practices.<br>

### Why AssaultCube
AssaultCube is a cross-platform lightweight multiplayer open-source FPS, making it one of the most famous playground for beginner-level binary hacking.

### Features
*Limited feature set as the project's goal wasnt to make a complete external hack but better understand how they are made.*

- Infinite ammo
- Infinite health
- ESP

## Instructions
*Note: The hack was buit for AC `13.0.2_LockdownEdition`. It may not work on other versions.*<br>

### Compilation
*Note: **i686-w64-mingw32-gcc is needed** to compile.*<br>
Run `make` in the root directory to generate the binary.

### Execution
Launch the game<br>
Launch `run.exe`<br>
In a game:
- `[F1]` infinite ammo toggle (ON/OFF)
- `[F2]` infinite health toggle (ON/OFF)
- `[F3]` ESP toggle (ON/OFF)

## External resources
[This forum thread](https://www.unknowncheats.me/forum/other-fps-games/724931-assaultcube-13-0-2-offsets.html) listed the latest known memory offsets. I've only used the View Matrix (`0x17DFD0`) though, some may not work. 