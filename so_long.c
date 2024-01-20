/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:46:39 by dwilun            #+#    #+#             */
/*   Updated: 2024/01/20 17:21:14 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
//funzioni tmp
int	ft_printError(char *error)
{
    printf("Error:\n%s",error);
    return (0);
}

void	ft_error(char *str, int num)
{
	perror(str);
	exit(num);
}

void	ft_printMatrix(char **matrix, int row)
{
	int	i;

	i = 0;
	while (i < row)
	{
		printf("matrix[%i] = %s\n", i, matrix[i]);
		i++;
	}
}
//funzioni tmp

// funzioni da spostare
void  ft_put_img(t_game *game, int index, int y, int x)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->textures[index], x * SIZE, y * SIZE);
}
int	ft_load_images(t_game *game)
{
	int	i;
	int	x;

	i = 0;
	while (i < game->y)
	{
		//ft_put_row(&game, i);
		x = 0;
		while (game->map[i][x] != '\0')
		{
			if (game->map[i][x] == 'P')
				ft_put_img(game, 0, i, x);
			else if (game->map[i][x] == '1')
				ft_put_img(game, 1, i, x);
			else if (game->map[i][x] == '0')
				ft_put_img(game, 2, i, x);
			else if (game->map[i][x] == 'C')
				ft_put_img(game, 3, i, x);
			else if (game->map[i][x] == 'E')
				ft_put_img(game, 4, i, x);
			x++;
		}
		i++;
	}
	return (0);
}
int	ft_checkImg(t_game *game, int index, char *path)
{
	int	size;

	size = SIZE;
	game->textures[index] = mlx_xpm_file_to_image(game->mlx,
			path, &size, &size);
	if (!game->textures[index])
		return (0);
	return (1);
}
int	ft_initImgs(t_game *game)
{
	if (ft_checkImg(game, 0, "./textures/babbo.xpm") == 0)
		return (ft_printError("textures non valide"));
	if (ft_checkImg(game, 1, "./textures/tree.xpm") == 0)
		return (ft_printError("textures non valide"));
	if (ft_checkImg(game, 2, "./textures/floor.xpm") == 0)
		return (ft_printError("textures non valide"));
	if (ft_checkImg(game, 3, "./textures/bimbo.xpm") == 0)
		return (ft_printError("textures non valide"));
	if (ft_checkImg(game, 4, "./textures/exitc.xpm") == 0)
		return (ft_printError("textures non valide"));
	if (ft_checkImg(game, 5, "./textures/exito.xpm") == 0)
		return (ft_printError("textures non valide"));
	return (0);
}

// funzioni da spostare
char	*ft_itoa(int num)
{
	char	*str;
	int		i;
	int		n;

	n = num;
	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	while (i > 0)
	{
		str[i - 1] = num % 10 + '0';
		num /= 10;
		i--;
	}
	return (str);
}
void	ft_printmoves(t_game *game)
{
	char	*str;
	int		len;

	str = ft_itoa(game->moves);
	len = ft_strlen(str);
	write(1, str, len);
	write(1, " move(s)\n", 9);
	free(str);
}

void ft_move_up(t_game *game)
{
	printf("up\n");
	if (game->map[game->player.y - 1][game->player.x] == '1')
		return ;
	else if (game->map[game->player.y - 1][game->player.x] == 'C')
	{
		game->map[game->player.y - 1][game->player.x] = '0';
		game->collectible--;
	}
	else if (game->map[game->player.y - 1][game->player.x] == 'E' &&
			game->collectible == 0)
		{
			printf("Victory");
			return ;
		}
	ft_put_img(game, 2, game->player.y, game->player.x);
	game->player.y--;
	ft_put_img(game, 0, game->player.y, game->player.x);
	if (game->map[game->player.y + 1][game->player.x] == 'E'
		&& game->collectible != 0)
		{
			ft_put_img(game, 4, game->player.y, game->player.x);
			printf("stronzo");
		}
	game->moves++;
	ft_printmoves(game);
}
void ft_move_left(t_game *game)
{
	printf("left\n");
	if (game->map[game->player.y][game->player.x - 1] == '1')
		return ;
	else if (game->map[game->player.y][game->player.x - 1] == 'C')
	{
		game->map[game->player.y][game->player.x - 1] = '0';
		game->collectible--;
	}
	else if (game->map[game->player.y][game->player.x - 1] == 'E' &&
			game->collectible == 0)
		{
			printf("Victory");
			return ;
		}
	ft_put_img(game, 2, game->player.y, game->player.x);
	game->player.x--;
	ft_put_img(game, 0, game->player.y, game->player.x);
	if (game->map[game->player.y][game->player.x + 1] == 'E'
		&& game->collectible != 0)
		{
			ft_put_img(game, 4, game->player.y, game->player.x);
			printf("stronzo");
		}
	game->moves++;
	ft_printmoves(game);
}
void ft_move_right(t_game *game)
{
	printf("right\n");
	if (game->map[game->player.y][game->player.x + 1] == '1')
		return ;
	else if (game->map[game->player.y][game->player.x + 1] == 'C')
	{
		game->map[game->player.y][game->player.x + 1] = '0';
		game->collectible--;
	}
	else if (game->map[game->player.y][game->player.x + 1] == 'E' &&
			game->collectible == 0)
		{
			printf("Victory");
			return ;
		}
	ft_put_img(game, 2, game->player.y, game->player.x);
	game->player.x++;
	ft_put_img(game, 0, game->player.y, game->player.x);
	if (game->map[game->player.y][game->player.x - 1] == 'E'
		&& game->collectible != 0)
		{
			ft_put_img(game, 4, game->player.y, game->player.x);
			printf("stronzo");
		}
	else
	{
		printf("%c\n", game->map[game->player.y][game->player.x - 1]);
	}
	game->moves++;
	ft_printmoves(game);
}
void ft_move_down(t_game *game)
{
	printf("down\n");
	if (game->map[game->player.y + 1][game->player.x] == '1')
		return ;
	else if (game->map[game->player.y + 1][game->player.x] == 'C')
	{
		game->map[game->player.y + 1][game->player.x] = '0';
		game->collectible--;
	}
	else if (game->map[game->player.y + 1][game->player.x] == 'E' &&
			game->collectible == 0)
		{
			printf("Victory");
			return ;
		}
	ft_put_img(game, 2, game->player.y, game->player.x);
	game->player.y++;
	ft_put_img(game, 0, game->player.y, game->player.x);
	if (game->map[game->player.y - 1][game->player.x] == 'E'
		&& game->collectible != 0)
		{
			ft_put_img(game, 4, game->player.y, game->player.x);
			printf("stronzo");
		}
		
	game->moves++;
	ft_printmoves(game);
}

int	ft_destroy(t_game *game)
{
	int	i;

	i = 0;
	ft_freeMatrix(game->map);
	while (i < 6)
		mlx_destroy_image(game->mlx, game->textures[i++]);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(0);
}
int	ft_getInput(int keycode, t_game *game)
{
	if (keycode == ESC)
		ft_destroy(game);
	else if (keycode == W)
		ft_move_up(game);
	else if (keycode == A)
		ft_move_left(game);
	else if (keycode == D)
		ft_move_right(game);
	else if (keycode == S)
		ft_move_down(game);
	return (0);
}
// funzioni da spostare

//int main(int argc, char **argv)
int main()
{
	t_game	*game;
	/*
	if (argc != 2)
		return (0);
	ft_getWindowSize(&game, argv[1]);
	*/
	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_printError("game non allocato"));//error
	char *argv = "testMap.ber";
	if (ft_getWindowSize(game, argv) == 0)
		return (ft_printError("dimensioni non valide"));//error
	game->map = (char **)malloc(sizeof(char *) * (game->y + 1));
	if (!game->map)
		return (ft_printError("mappa non allacata"));//error
	ft_fillMap(game, argv);
	if (!ft_checkMap(game))
		return (ft_printError("mappa non valida"));//error
	ft_printMatrix(game->map, game->y);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->x*SIZE, game->y*SIZE, "so_long");
	ft_initImgs(game);
	ft_load_images(game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, ft_getInput, game);
	mlx_hook(game->win, 17, 1L << 2, ft_destroy, game);
	mlx_loop(game->mlx);
	ft_destroy(game);
}
