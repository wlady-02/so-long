/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:46:39 by dwilun            #+#    #+#             */
/*   Updated: 2023/12/16 18:13:02 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
#include "./get_next_line/get_next_line.h"

typedef struct s_game
{
	int x;
	int y;
	char **map;
} t_game;

int ft_rowLen(char *row)
{
	int	i;

	i = 0;
	while (row[i] != '\n' && row[i] != '\0')
		i++;
	return (i);
}

int ft_countLine(int fd, int x)
{
	int		count;
	char	*line;
	count = 1;
	while (1)
	{
		line = get_next_line(fd);
		// printf("%s\n", line);
		// printf("%i\n", ft_strlen(line));
		// printf("%i\n", x);
		if (!line)
			break;
		if (ft_rowLen(line) == x)
		{
			count++;
			free(line);
		}
		else
		{
			free(line);
			return(0);
		}
	}
	return (count);
}


int	ft_getWindowSize(t_game *game, char *fileMap)
{
	/*
	if (fileMap == .ber)
	*/
	int	fd;
	char *row;

	fd = open(fileMap, O_RDONLY);
	if (fd == -1)
		return (0);
	row = get_next_line(fd);
	//printf("row = %s\n", row);
	game->x = ft_rowLen(row);
	free(row);
	game->y = ft_countLine(fd, game->x);
	close(fd);
}

int	ft_createMatrix (t_game *game, char *fileMap)
{
	int	fd;
	int	i;

	i = 0;
	fd = open(fileMap, O_RDONLY);
	while (game->map)
	{
		game->map[i] = get_next_line(fd);
		i++;
	}
	return (1);
}

int main(void) 
{
	//printf("main\n");
	t_game game;

	/*
	if (argc != 2)
		return (0);
	ft_getWindowSize(&game, argv[1]);
	*/
	char *argv = "testMap.ber";
	ft_getWindowSize(&game, argv);
	printf("%i * %i\n", game.x, game.y);
	game.map = (char **)malloc(sizeof(char *) * (game.y + 1));
	printf("tab");
	if (!game.map)
	{
		printf("error");
		return (0);
	}
	game.map[game.y + 1] = NULL;
	ft_createMatrix(&game, argv);
	int i = 0;
	while (game.map)
	{
		printf("game->map[%i] = %s", i,game.map[i]);
		i++;
	}
    return 0;
}




