/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 09:49:55 by dwilun            #+#    #+#             */
/*   Updated: 2024/01/27 10:18:07 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	ft_move_player(t_game *game, int x, int y)
{
	if (game->map[game->player.y + y][game->player.x + x] == '1')
		return ;
	else if (game->map[game->player.y + y][game->player.x + x] == 'C')
	{
		game->map[game->player.y + y][game->player.x + x] = '0';
		game->collectible--;
	}
	else if (game->map[game->player.y + y][game->player.x + x] == 'E' &&
			game->collectible == 0)
	{
		ft_victory(game);
		return ;
	}
	ft_put_img(game, 2, game->player.y, game->player.x);
	game->player.y += y;
	game->player.x += x;
	ft_put_img(game, 0, game->player.y, game->player.x);
	if (game->map[game->player.y + (y * -1)][game->player.x + (x * -1)] == 'E'
		&& game->collectible != 0)
		ft_put_img(game, 4, game->player.y + (y * -1),
			game->player.x + (x * -1));
	game->moves++;
	ft_printmoves(game);
}

int	ft_get_input(int keycode, t_game *game)
{
	if (keycode == ESC)
		ft_destroy(game);
	else if (keycode == W || keycode == UP)
		ft_move_player(game, 0, -1);
	else if (keycode == A || keycode == LF)
		ft_move_player(game, -1, 0);
	else if (keycode == D || keycode == RG)
		ft_move_player(game, 1, 0);
	else if (keycode == S || keycode == DW)
		ft_move_player(game, 0, 1);
	if (game->collectible == 0)
		ft_put_img(game, 5, game->exit.y, game->exit.x);
	return (1);
}
