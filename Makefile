##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

SRC		+=	src/main.cpp
SRC		+=	src/Parsing.cpp
SRC		+=	src/Core.cpp

OBJ 	= 	$(SRC:.cpp=.o)

NAME 	= 	arcade

CXXFLAGS = -std=c++17 -Wall -Wextra

CPPFLAGS = -iquote include

CXX = g++

all :	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) -ldl
	rm src/*.o

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all