# Lift Off: Beyond Glaxium

## Build

### Prerequisites

- freeglut3(-dev)
- libsdl1.2(-dev)
- libsdl-mixer1.2(-dev)
- libsdl-image1.2(-dev)

### Compilation

./configure && make

## Command line options

```liftoff -l```

Low quality mode. Half resolution for background texture, disables mip-mapping and multisampling and reduces the number of background stars and particles to 50%.

```liftoff -m[2|4|8|16]```

Enables multisampling at 2, 4, 8 or 16 samples. If not specified, the highest multisampling mode available on your hardware will be used. Note that multisampling is disabled in low quality mode ("-l").

```liftoff -s```

Write debugging information to "stdout.txt" (Windows only).

```liftoff -h```

Show command line parameters (Linux only).

## Controls

- JOYSTICKS and GAMEPADS are supported.
- MOUSE works only for menus.
- CURSOR KEYS or W/A/S/D will move your ship.
- CTRL will let your ship fire it's little guns.
- ESCAPE quits the game at any time.
- F12 toggles displaying current frame rate.
- CTRL+C can be used as "boss key".

