##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -std=c++17 -Wall -Wextra

NAME = arcade_ncurses.so

all: $(OBJ)
	g++ -std=c++17 -fPIC -shared NCURSES.cpp -o arcade_ncurses.so -lncurses
	g++ -std=c++17 -fPIC -shared SDL.cpp -o arcade_sdl2.so -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
	g++ -std=c++17 -fPIC -shared SFML.cpp -o arcade_sfml.so -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	mv arcade_ncurses.so ../../lib
	mv arcade_sdl2.so ../../lib
	mv arcade_sfml.so ../../lib

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all

auteur:
	echo $(USER) > auteur

.PHONY: all clean fclean re