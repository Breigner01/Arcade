# Arcade
Arcade is a gaming platform: a program that lets the user choose a game to play and keeps a register of player scores.

## Requirements

`Build`
- C++20 compiler
- cmake 3.17

`Libraries`
- SFML
- SDL
- SDL_image
- SDL_mixer
- SDL_ttf
- NCURSES

## Build

```
mkdir build
cd build
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build .
```

## Librairies
### Graphic
We include `3` graphics lib:   
- SFML
- SDL
- NCURSES   

### GAME
We include `2` games lib:
- Nibbler
- Pacman  

## Usage
```bash
USAGE:
  ./arcade lib
  
DESCRIPTION:
  lib   the path where you can find graphics librairies (./lib/)
  
COMMAND IN GAME:
  n           next graphics
  p           previous graphics
  o           next game
  i           previous game
  
  m           menu
  r           reset the game
  echap       quit arcade
  
  RIGHT_ARROW move right
  LEFT_ARROW  move left
  UP_ARROW    move up
  DOWN_ARROW  move down
```

## Documentation

In `./doc/`

## Contributors

- [Benjamin Reigner](https://github.com/Breigner01)
- [Martin Olivier](https://github.com/tocola)
- [Coline Seguret](https://github.com/Cleopha)
