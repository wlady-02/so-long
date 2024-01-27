/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:46:39 by dwilun            #+#    #+#             */
/*   Updated: 2024/01/27 16:35:18 by dwilun           ###   ########.fr       */
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
		ft_error("Error\nTexture non valida", 6, game);
	}
}

void	ft_init_imgs(t_game *game)
{
	ft_check_img(game, 0, "./textures/babbo.xpm");
	ft_check_img(game, 1, "./textures/bab2.xpm");
	ft_check_img(game, 2, "./textures/bab3.xpm");
	ft_check_img(game, 3, "./textures/bab4.xpm");
	ft_check_img(game, 4, "./textures/bab5.xpm");
	ft_check_img(game, 5, "./textures/tree.xpm");
	ft_check_img(game, 6, "./textures/floor.xpm");
	ft_check_img(game, 7, "./textures/bimbo.xpm");
	ft_check_img(game, 8, "./textures/bim2.xpm");
	ft_check_img(game, 9, "./textures/exitc.xpm");
	ft_check_img(game, 10, "./textures/exito.xpm");
	ft_check_img(game, 11, "./textures/pula.xpm");
	ft_check_img(game, 12, "./textures/pul2.xpm");
	ft_check_img(game, 13, "./textures/pul3.xpm");
}

//int main(int argc, char **argv)
int main()
{
	t_game	*game;

	/*
	if (argc != 2)
		return (0);
	ft_getwindowsize(&game, argv[1]);
	*/
	char *argv = "./map/42.ber";
	game = malloc(sizeof(t_game));
	if (!game)
		ft_error("Error\nAllocazione non riuscita", 1, game);
	ft_getwindowsize(game, argv);
	game->map = (char **)malloc(sizeof(char *) * (game->y + 1));
	if (!game->map)
		ft_error("Error\nAllocazione non riuscita", 3, game);
	ft_fill_map(game, argv);
	if (!ft_check_map(game))
		ft_error("Error\nMappa non valida", 5, game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->x*SIZE, game->y*SIZE, "so_long");
	ft_init_imgs(game);
	ft_load_images(game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, ft_get_input, game);
	mlx_hook(game->win, 17, 1L << 2, ft_destroy, game);
	game->frame = 0;
	mlx_loop_hook(game->mlx, ft_animate, game);
	mlx_loop(game->mlx);
	ft_destroy(game);
}
