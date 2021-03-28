##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -std=c++17 -Wall -Wextra

all: $(OBJ)
	g++ -std=c++17 -fPIC -shared Snake.cpp -o arcade_nibbler.so
	g++ -std=c++17 -fPIC -shared Pacman.cpp -o arcade_pacman.so
	mv arcade_nibbler.so ../../lib
	mv arcade_pacman.so ../../lib

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all

auteur:
	echo $(USER) > auteur

.PHONY: all clean fclean re