# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/20 13:52:57 by lkaser            #+#    #+#              #
#    Updated: 2017/11/17 14:33:39 by lkaser           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
LIST = buffer line hook matrix vector fdf

SRC = $(addsuffix .c, $(LIST))
OBJ = $(addsuffix .o, $(LIST))

CFLAGS = -O3 -Wall -Wextra -Werror -I libft/includes -I libmlx

all: $(NAME) 

$(NAME): $(OBJ)
	make -C libft
	make -C libmlx
	gcc $(CFLAGS) -L libft -L libmlx -lmlx -framework OpenGL -framework AppKit -lft $(SRC) -o $(NAME)

lib:
	make -C libft
	make -C libmlx

clean:
	make -C libft clean
	make -C libmlx clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	make -C libmlx fclean
	rm -f $(NAME)

re:	fclean all

.PHONY: clean fclean all re
