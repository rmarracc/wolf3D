# wolf3D
Wolfenstein3D-like labyrinth explorer

## Installation

### Clone

- Clone this repo using `git clone https://github.com/rmarracc/wolf3D`

### Build

- Simply build the program with `make` in the cloned folder

## Usage

- Execute the program with `./wolf3d [map]`
You can find the map files in the map folder, but you can also generate yours using `./generator [x] [y] [pal] [density] [px] [py] [borders] > [path]`, you can also generate and use directly a map with `./generator [x] [y] [pal] [density] [px] [py] [borders] | ./wolf3d /dev/stdin`

### Generator options

- x : map x size (min : 10, max : 2000)
- y : map y size (min : 10, max : 2000)
- pal : map texture pack (between 1 and 8)
- density : map wall density, the lower it is, the more wall the map has (between 256 and 1)
- px : player x position
- py : player y position
- border : 1 if the map has borders, 0 if it hasn't

### Texture packs

- 1 : Basic texture pack
- 2 : Forest texture pack
- 3 : Volcano texture pack
- 4 : Desert texture pack
- 5 : Snow mountain texture pack
- 6 : Moon texture pack
- 7 : City texture pack
- 8 : Japanese cherry bloosom texture pack

## Controls

- Move with WASD
- Rotate the player with right and left arrows
- Enable/Disable the minimap with M
- Dash with Shift

## Pictures

https://postimg.cc/gallery/cybhe5ao/

## Known bugs

- Aliased minimap
- Minimap blink while holding M button
- One excedent ground pixel at x = 0 and y = 0 on the minimap
- Missing minimap colors with texture 8

## Work distribution

cpoirier :

- (Optimised) Raycasting render engine
- Ground reflection effect
- Skybox
- Texture mapping

me (rmarracc) :

- Parsing
- Generator
- Commands and collisions
- Minimap
