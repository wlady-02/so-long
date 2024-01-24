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
			ft_freeMatrix(tmp, i);
			return (0);//error
		}
		i++;
	}
	ft_freeMatrix(tmp, i);
	return (1);
}

int ex_ft_fullWall(char *row)
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

void ft_addEntities(char entity, t_chr *chr, int x, int y)
{
    if (entity == 'P')
    {
        chr->pcoord.x = x;
        chr->pcoord.y = y;
        chr->p++;
    }
    else if (entity == 'E')
    {
        chr->ecoord.x = x;
        chr->ecoord.y = y;
        chr->e++;
    }
    else if (entity == 'C')
        chr->c++;
}

int ft_checkRow(char *row, int len, t_chr *chr, int flag)
{
	int	i;

	i = 0;
	if (row[0] != '1' || row[len - 1] != '1')
		return (0);//error
	while (row[++i] != '\0' && i < len - 1)
	{
	    if (flag == 1 && row[i] != '1')
	        return (0);
	    if (flag == 1)
	        continue ;
	    if (row[i] == 'C' || row[i] == 'E' || row[i] == 'P')
		    ft_addEntities(row[i], chr, i, chr->i);
		else if (row[i] != '1' && row[i] != '0')
			return (0);//error
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
	if (!ft_checkRow(game->map[0], game->x, &chr, 1) ||
	    !ft_checkRow(game->map[game->y - 1], game->x, &chr, 1))
	    return (0);
	while (++chr.i < game->y - 1)
	{
		if (!ft_checkRow(game->map[chr.i], game->x, &chr, 0))
			return (0);//error
	}
	if (chr.e != 1 || chr.p != 1 || chr.c == 0)
	    return (0);//error
	game->collectible = chr.c;
	game->player = chr.pcoord;
	game->exit = chr.ecoord;
	if (ft_checkPlayerToExit(game->map, game->y, game->player) == 0)
	    return (0);//error
	return (1);
}
