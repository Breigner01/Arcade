##
## EPITECH PROJECT, 2021
## nanotekspice
## File description:
## Makefile
##

CXX			?=	g++

RM			?=	rm -f

ECHO		=	/usr/bin/echo

MAKEFLAGS	+=	--no-print-directory

CXXFLAGS	+=	-Wall -Wextra -std=c++14

CPPFLAGS	=

TFLAGS		=	-lcriterion --coverage

NAME		=	a.out

SRC			=

MAIN		=	main/main.cpp

MOBJ		=	$(MAIN:.cpp=.o)

OBJ			=	$(SRC:.cpp=.o)

TSRC		=	tests/test.cpp

TOBJ		=	$(TSRC:.cpp=.o)

GCDA		+=	$(SRC:.cpp=.gcda)
GCDA		+=	$(TSRC:.cpp=.gcda)

GCNO		+=	$(SRC:.cpp=.gcno)
GCNO		+=	$(TSRC:.cpp=.gcno)

ifdef DEBUG
	CXXFLAGS += -ggdb3
endif

%.o:	%.cpp
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $< && \
	($(ECHO) -e "\033[92m[ OK ]\033[0m" $<) || \
	($(ECHO) -e "\033[91m[ NO COMPIL ]\033[0m" $<; false)

all:	$(NAME)

$(NAME):	$(OBJ) $(MOBJ)
	@$(CXX) $(MOBJ) $(OBJ) -o $(NAME)

tests_run:	CPPFLAGS	+=	--coverage

tests_run:	$(OBJ) $(TOBJ)
	@$(CXX) -o unit_test $(OBJ) $(TOBJ) $(TFLAGS)
	@./unit_test
	@gcovr -b --exclude-directories tests


clean:
	@for f in $(TOBJ); do if [ -f $$f ]; then $(ECHO) -e "\033[35m[ TU ]\033[0m" $$f; fi; done;
	@for f in $(OBJ); do if [ -f $$f ]; then $(ECHO) -e "\033[91m[ RM ]\033[0m" $$f; fi; done;
	@for f in $(MOBJ); do if [ -f $$f ]; then $(ECHO) -e "\033[91m[ RM ]\033[0m" $$f; fi; done;
	@$(RM) $(OBJ) $(MOBJ) $(TOBJ)
	@$(RM) $(GCDA)
	@$(RM) $(GCNO)

fclean: clean
	@if [ -f $(NAME) ]; then $(ECHO) -e "\033[33m[ RM ]\033[0m" $(NAME); fi;
	@$(RM) $(NAME) unit_test

re: fclean all

.PHONY: all clean fclean re tests_run