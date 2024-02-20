# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/27 12:09:59 by dwilun            #+#    #+#              #
#    Updated: 2024/01/27 12:42:51 by dwilun           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCS = so_long.c so_long_utils.c  \
	./get_next_line/get_next_line.c \
	./get_next_line/get_next_line_utils.c \
	get_map.c \
	check_map.c \
	move.c \
	close.c

BSRCS = ./bonus/so_long_bonus.c \
		./bonus/so_long_utils_bonus.c  \
		./bonus/get_next_line/get_next_line_bonus.c \
		./bonus/get_next_line/get_next_line_utils_bonus.c \
		./bonus/get_map_bonus.c \
		./bonus/check_map_bonus.c \
		./bonus/move_bonus.c \
		./bonus/close_bonus.c \
		./bonus/animate_bonus.c

OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)
MLX = "https://github.com/42Paris/minilibx-linux.git"
MLX_DIR = minilibx-linux
FLAGS = -Lminilibx-linux -lmlx -lX11 -lXext
all: $(MLX_DIR) $(NAME)
$(MLX_DIR):
	@git clone $(MLX)
	@cd $(MLX_DIR) && ./configure

$(NAME): $(OBJS)
	cc -g -Wall -Wextra -Werror $(OBJS) $(FLAGS) -o $(NAME)

bonus: $(MLX_DIR) $(BOBJS)
	cc -Wall -Wextra -Werror $(BOBJS) $(FLAGS) -o $(NAME)

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all