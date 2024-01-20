/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 09:43:39 by dwilun            #+#    #+#             */
/*   Updated: 2024/01/20 16:35:42 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_fillMap(t_game *game, char *fileMap)
{
	int		fd;
	int		i;
	char	*row;

	i = 0;
	fd = open(fileMap, O_RDONLY);
	while (i < game->y)
	{
		row = get_next_line(fd);
		if (!row)
		    return (0);//error
		game->map[i] = ft_strtrim(row, "\n");
		free(row);
		if (!game->map[i])
		{
			ft_freeMatrix(game->map);
			return (0);//error
		}
		i++;
	}
	game->map[i] = NULL;
	close(fd);
	return (1);
}

int	ft_rowLen(char *row)
{
	int	i;

	i = 0;
	while (row[i] != '\n' && row[i] != '\0')
		i++;
	return (i);
}

int	ft_countLine(int fd, int x)
{
	int		count;
	char	*line;

	count = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_rowLen(line) == x)
		{
			count++;
			free(line);
		}
		else
		{
			free(line);
			return (0);//error
		}
	}
	return (count);
}

int	ft_getWindowSize(t_game *game, char *fileMap)
{
	int		fd;
	char	*row;

	fd = open(fileMap, O_RDONLY);
	row = get_next_line(fd);
	game->x = ft_rowLen(row);
	free(row);
	game->y = ft_countLine(fd, game->x);
	close(fd);
	if (game->y == game->x || game->y < 3
		|| game->x < 3
		|| (game->y == 3 && game->x < 5)
		|| (game->x == 3 && game->y < 5))
		return (0);
	return (1);
}
