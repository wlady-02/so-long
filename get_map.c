/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 09:43:39 by dwilun            #+#    #+#             */
/*   Updated: 2024/01/27 10:24:45 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_fill_map(t_game *game, char *fileMap)
{
	int		fd;
	int		i;
	char	*row;

	i = -1;
	fd = open(fileMap, O_RDONLY);
	while (++i < game->y)
	{
		row = get_next_line(fd);
		if (!row)
			break ;
		game->map[i] = ft_strtrim(row, "\n");
		free(row);
		if (!game->map[i])
			break ;
	}
	if (i < game->y)
	{
		ft_free_matrix(game->map, i);
		ft_error("Error\nAllocazione non riuscita", 7, game);
	}
	game->map[i] = NULL;
	close(fd);
}

int	ft_rowlen(char *row)
{
	int	i;

	i = 0;
	while (row[i] != '\n' && row[i] != '\0')
		i++;
	return (i);
}

int	ft_countline(int fd, int x)
{
	int		count;
	char	*line;

	count = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_rowlen(line) == x)
		{
			count++;
			free(line);
		}
		else
		{
			free(line);
			return (0);
		}
	}
	return (count);
}

void	ft_getwindowsize(t_game *game, char *fileMap)
{
	int		fd;
	char	*row;

	fd = open(fileMap, O_RDONLY);
	row = get_next_line(fd);
	game->x = ft_rowlen(row);
	free(row);
	game->y = ft_countline(fd, game->x);
	close(fd);
	if (game->y == game->x || game->y < 3
		|| game->x < 3
		|| (game->y == 3 && game->x < 5)
		|| (game->x == 3 && game->y < 5))
		ft_error("Error\nDimensioni mappa non valide", 5, game);
}
