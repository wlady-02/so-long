/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:39:53 by dwilun            #+#    #+#             */
/*   Updated: 2024/01/27 16:26:12 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_set_img_anim(t_game *game, int start, int index, char entity)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->y)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			if (game->map[y][x] == entity)
				ft_put_img(game, start + index, y, x);
			x++;
		}
		y++;
	}
}

int	ft_animate(t_game *game)
{
	static int	c = -1;
	static int	p = 0;
	static int	n = 0;

	game->frame++;
	if (game->frame == 30000)
	{
		p++;
		if (p == 4)
			p = 0;
		ft_put_img(game, p, game->player.y, game->player.x);
		c++;
		if (c == 1)
			c = -1;
		ft_set_img_anim(game, 7, c + 1, 'C');
		n++;
		if (n == 3)
			n = 0;
		ft_set_img_anim(game, 11, n, 'N');
		game->frame = 0;
	}
	return (0);
}
