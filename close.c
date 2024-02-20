/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:55:06 by dwilun            #+#    #+#             */
/*   Updated: 2024/01/27 11:34:46 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_matrix(char **matrix, int row)
{
	int	i;

	i = -1;
	while (++i < row)
		free(matrix[i]);
	free(matrix);
}

int	ft_destroy(t_game *game)
{
	int	i;

	i = -1;
	ft_free_matrix(game->map, game->y);
	while (++i < 6)
		mlx_destroy_image(game->mlx, game->textures[i]);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(0);
}

void	ft_victory(t_game *game)
{
	char	*str;
	int		len;

	str = ft_itoa(game->moves);
	len = ft_strlen(str);
	write(1, "You win!\n", 9);
	write(1, "You cleared the level in only ", 30);
	write(1, str, len);
	write(1, " moves!\n", 8);
	free(str);
	ft_destroy(game);
}

void	ft_error(char *str, int num, t_game *game)
{
	if (num == 5 || num == 6 || num == 7 || num == 9)
		free(game);
	else if (num == 8)
	{
		ft_free_matrix(game->map, game->y);
		free(game);
	}
	perror(str);
	exit(num);
}

void	ft_init_check(int argc, char **argv, t_game *game)
{
	int	fd;
	int	len;

	if (argc != 2)
		ft_error("Error\nNumero di argomenti non valido", 1, game);
	len = ft_strlen(argv[1]);
	while (len >= 0)
	{
		if (argv[1][len] == '.')
		{
			if (argv[1][len + 1] != 'b'
				&& argv[1][len + 2] != 'e' && argv[1][len + 3] != 'r')
				ft_error("Error\nEstensione non valida", 2, game);
			len = -100;
			break ;
		}
		len--;
	}
	if (len != -100)
		ft_error("Error\nInput non valido", 2, game);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_error("Error\nFile non valido", 3, game);
	close(fd);
}
