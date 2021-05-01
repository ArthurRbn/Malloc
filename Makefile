##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

SRC		=		malloc.c		\
				realloc.c		\
				free.c			\
				utils.c			\
				calloc.c		\
				reallocarray.c	\

RM		=		rm -fr

NAME	=		libmy_malloc.so

OBJ		=		$(SRC:.c=.o)

CFLAGS	=		-c -Wall -Werror -Wextra -fpic

LFLAGS  =		-shared

$(NAME):	$(OBJ)
			gcc $(CFLAGS) $(SRC)
			gcc $(LFLAGS) -o $(NAME) $(OBJ)

all:		$(NAME)

clean:
			@$(RM) *~
			@$(RM) *.o

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all