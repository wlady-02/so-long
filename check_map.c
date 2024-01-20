/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 10:42:58 by dwilun            #+#    #+#             */
/*   Updated: 2024/01/20 16:42:25 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_playerToExit (char **map, t_coord start)
{
	if (map[start.y][start.x] == '1' || map[start.y][start.x] == 'X')
        return (0);//error
	map[start.y][start.x] = 'X';
	ft_playerToExit(map, (t_coord){start.x + 1, start.y});
	ft_playerToExit(map, (t_coord){start.x - 1, start.y});
	ft_playerToExit(map, (t_coord){start.x, start.y + 1});
	ft_playerToExit(map, (t_coord){start.x, start.y - 1});
    return (0);//error
}

int	ft_checkPlayerToExit(char **map, int y, t_coord player)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_cpyMatrix(map, y);
	if (!tmp)
		return (0);//error
	//ft_printMatrix(tmp, y);
	if (!tmp)
		return (0);//error
	ft_playerToExit(tmp, player);
	while (i < y)
	{
		if (ft_strchr(tmp[i], 'C') || ft_strchr(tmp[i], 'E'))
		{
			ft_freeMatrix(tmp);
			return (0);//error
		}
		i++;
	}
	ft_freeMatrix(tmp);
	return (1);
}

int ft_fullWall(char *row)
{
	int i;

	i = 0;
	while (row[i] != '\0')
	{
		if (row[i] != '1')
		    return (0);//error
		i++;
	}
	return (1);
}

int ft_checkRow(char *row, int len, int y, t_chr *chr)
{
	int	i;

	i = 0;
	if (row[i] != '1' || row[len - 1] != '1')
		return (0);//error
	while (row[i] != '\0')
	{
		if (row[i] != '1' && row[i] != '0' && row[i] != 'C'
			&& row[i] != 'E' && row[i] != 'P')
			return (0);//error
		if (row[i] == 'P')
		{
			chr->pcoord.x = i;
			chr->pcoord.y = y;
			chr->p++;
		}
		else if (row[i] == 'E')
		{
			chr->ecoord.x = i;
			chr->ecoord.y = y;
			chr->e++;
		}
		else if (row[i] == 'C')
			chr->c++;
		i++;
	}
	return (1);
}

int	ft_checkMap(t_game *game)
{
	t_chr	chr;

	chr.i = 0;
	chr.c = 0;
	chr.p = 0;
	chr.e = 0;
	chr.pcoord.x = -1;
	chr.pcoord.y = -1;
	if (ft_fullWall(game->map[0]) == 0 ||
		ft_fullWall(game->map[game->y - 1]) == 0)
		return (0);//error
	while (chr.i < game->y)
	{
		if (!ft_checkRow(game->map[chr.i], game->x, chr.i, &chr))
			return (0);//error
		chr.i++;
	}
	if (chr.e != 1 || chr.p != 1 || chr.c == 0)
	    return (0);//error
	game->collectible = chr.c;
	game->player = chr.pcoord;
	game->exit = chr.ecoord;
	if (ft_checkPlayerToExit(game->map, game->y, chr.pcoord) == 0)
	    return (0);//error
	return (1);
}
