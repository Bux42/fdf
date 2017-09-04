# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: videsvau <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/19 03:52:32 by videsvau          #+#    #+#              #
#    Updated: 2017/05/20 02:48:47 by videsvau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = gcc

FLAGS = -Wall -Wextra -Werror -framework OpenGL -framework AppKit

NAME = fdf

SOURCES = check_syntax.c\
		  draw.c\
		  matrice.c\
		  move.c\
		  display.c\
		  fdf.c\
		  parse.c\
		  memory.c\

OBJ = $(SRC:.c=.o)

all = $(NAME)

$(NAME) : $(OBJ)
	@make -C libft/
	@make -C minilibx_macos/
	@gcc -o $(NAME) $(SOURCES) $(FLAGS) libft/libft.a minilibx_macos/libmlx.a

clean :
	@rm -f $(OBJ)
	make clean -C libft/

fclean : clean
	rm -f $(NAME)
	make fclean -C libft/
	make clean -C minilibx_macos/

re : fclean $(NAME)
