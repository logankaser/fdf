# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/20 13:52:57 by lkaser            #+#    #+#              #
#    Updated: 2017/11/03 17:00:53 by lkaser           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
LIST = buffer draw hook fdf

SRC = $(addsuffix .c, $(LIST))
OBJ = $(addsuffix .o, $(LIST))

CFLAGS = -O3 -Wall -Wextra -Werror -I libft/includes -I libmlx

all: $(NAME) 

$(NAME): $(OBJ)
	make -C libft
	make -C libmlx
	gcc $(CFLAGS) -L libft -L libmlx -lmlx -framework OpenGL -framework AppKit -lft $(SRC) -o $(NAME)

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