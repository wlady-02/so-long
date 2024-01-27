/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:55:06 by dwilun            #+#    #+#             */
/*   Updated: 2024/01/27 16:31:31 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
	while (++i < 14)
		mlx_destroy_image(game->mlx, game->textures[i]);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(0);
}

void	ft_gameover(t_game *game)
{
	char	*str;
	int		len;

	str = ft_itoa(game->moves);
	len = ft_strlen(str);
	write(1, "You Lose!\n", 10);
	write(1, "In only ", 8);
	write(1, str, len);
	write(1, " moves!\n", 8);
	free(str);
	ft_destroy(game);
	exit(0);
}

/*
	tmp = ft_strjoin(ft_strjoin("You win!\nYou cleared the level in only ", 
		ft_itoa(game->moves))
	str = ft_strjoin(tmp, " moves!\n");
	write (1, str, ft_strlen(str));
	free(str);
*/
void	ft_victory(t_game *game)
{
	char	*str;
	int		len;

	str = ft_itoa(game->moves);
	len = ft_strlen(str);
	write(1, "You Win!\n", 10);
	write(1, "You cleared the level in only ", 30);
	write(1, str, len);
	write(1, " moves!\n", 8);
	free(str);
	ft_destroy(game);
	exit(0);
}

void	ft_error(char *str, int num, t_game *game)
{
	if (num == 1)
		perror(str);
	else if (num == 2 || num == 3 || num == 4 || num == 6)
		free(game);
	else if (num == 5)
	{
		ft_free_matrix(game->map, game->y);
		free(game);
	}
	perror(str);
	exit(num);
}
