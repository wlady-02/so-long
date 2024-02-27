/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:39:05 by marvin            #+#    #+#             */
/*   Updated: 2024/02/26 08:39:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_put_img(t_game *game, int index, int y, int x)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->textures[index], x * SIZE, y * SIZE);
}

void	ft_load_images(t_game *game)
{
	int	i;
	int	x;

	i = 0;
	while (i < game->y)
	{
		x = 0;
		while (game->map[i][x] != '\0')
		{
			if (game->map[i][x] == 'P')
				ft_put_img(game, 0, i, x);
			else if (game->map[i][x] == '1')
				ft_put_img(game, 5, i, x);
			else if (game->map[i][x] == '0')
				ft_put_img(game, 6, i, x);
			else if (game->map[i][x] == 'C')
				ft_put_img(game, 7, i, x);
			else if (game->map[i][x] == 'E')
				ft_put_img(game, 9, i, x);
			else if (game->map[i][x] == 'N')
				ft_put_img(game, 11, i, x);
			x++;
		}
		i++;
	}
}

void	ft_check_img(t_game *game, int index, char *path)
{
	int	size;
	int	i;

	size = SIZE;
	game->textures[index] = mlx_xpm_file_to_image(game->mlx,
			path, &size, &size);
	if (!game->textures[index])
	{
		i = -1;
		ft_free_matrix(game->map, game->y);
		while (++i < index)
			mlx_destroy_image(game->mlx, game->textures[i]);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		ft_error("Error\nTexture non valida", 9, game);
	}
}

void	ft_init_imgs(t_game *game)
{
	ft_check_img(game, 0, "./textures/player.xpm");
	ft_check_img(game, 1, "./textures/player2.xpm");
	ft_check_img(game, 2, "./textures/player3.xpm");
	ft_check_img(game, 3, "./textures/player4.xpm");
	ft_check_img(game, 4, "./textures/player5.xpm");
	ft_check_img(game, 5, "./textures/wall.xpm");
	ft_check_img(game, 6, "./textures/floor.xpm");
	ft_check_img(game, 7, "./textures/coll.xpm");
	ft_check_img(game, 8, "./textures/coll2.xpm");
	ft_check_img(game, 9, "./textures/exitc.xpm");
	ft_check_img(game, 10, "./textures/exito.xpm");
	ft_check_img(game, 11, "./textures/enemy.xpm");
	ft_check_img(game, 12, "./textures/enemy2.xpm");
	ft_check_img(game, 13, "./textures/enemy3.xpm");
}

int	main(int argc, char **argv)
{
	t_game	*game;

	ft_init_check(argc, argv);
	game = malloc(sizeof(t_game));
	if (!game)
		ft_error("Error\nAllocazione non riuscita", 4, game);
	ft_getwindowsize(game, argv[1]);
	game->map = (char **)malloc(sizeof(char *) * (game->y + 1));
	if (!game->map)
		ft_error("Error\nAllocazione non riuscita", 6, game);
	ft_fill_map(game, argv[1]);
	if (!ft_check_map(game))
		ft_error("Error\nMappa non valida", 8, game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->x * SIZE, game->y * SIZE,
			"so_long bonus");
	ft_init_imgs(game);
	ft_load_images(game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, ft_get_input, game);
	mlx_hook(game->win, 17, 1L << 2, ft_destroy, game);
	game->frame = 0;
	mlx_loop_hook(game->mlx, ft_animate, game);
	mlx_loop(game->mlx);
	ft_destroy(game);
}
