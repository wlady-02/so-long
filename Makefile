NAME = so_long
MLX_DIR = ./minilibx
MLX = $(MLX_DIR)/libmlx.a
MLXFLAGS = -lX11 -lXext -lm
CC = cc -g -Wall -Wextra -Werror
SRC = so_long.c so_long_utils.c  ./get_next_line/get_next_line.c \
./get_next_line/get_next_line_utils.c \
	get_map.c check_map.c
OBJ = $(SRC:.c=.o)
FT_PRINTF = printf

all: $(NAME)

$(NAME): $(OBJ)
	@make all -C $(FT_PRINTF)
	@make all -C $(MLX_DIR)
	@$(CC) $(OBJ) printf/libftprintf.a $(MLX) $(MLXFLAGS) -o $(NAME)
	@echo "Compiled "$(NAME)" successfully!"

%.o: %.c
	@$(CC) -c $< -o $@

bonus : all

clean:
	@make clean -C $(FT_PRINTF)
	@rm -f $(OBJ)
	@echo "Cleaned objects successfully!"
    
fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(FT_PRINTF)
	@make clean -C $(MLX_DIR)
	@echo "Cleaned "$(NAME)" successfully!"
    
re: fclean all
	make re -C $(FT_PRINTF)
val:
	valgrind --leak-check=full --show-leak-kinds=all ./so_long $(file)
replay:
	@rm -f $(NAME)
	@$(CC) $(SRC) ft_printf/libftprintf.a $(MLX) $(MLXFLAGS) -o $(NAME)
	@echo "Let's  gooo!!"
  
.PHONY: all clean fclean bonus re replay