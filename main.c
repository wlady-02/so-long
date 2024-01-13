/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 16:46:39 by dwilun            #+#    #+#             */
/*   Updated: 2024/01/13 13:53:43 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
#include "./get_next_line/get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		//printf("ft_strlen : %c\n", str[i]);
		i++;
	}
	
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*tmp;
	unsigned char	*zerotmp;
	long long		result;
	int				i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	result = (long long)nmemb * (long long)size;
	if (result > 4294967295)
		return (NULL);
	tmp = (void *)malloc(nmemb * size);
	if (tmp == NULL)
		return (NULL);
	zerotmp = (unsigned char *)tmp;
	i = 0;
	while (i < result)
		zerotmp[i++] = '\0';
	return (tmp);
}
char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while ((unsigned char)s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((unsigned char)s[i] == (unsigned char)c)
		return ((char *)s + i);
	else
		return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	l1;
	size_t	l2;
	char	*strj;

	i = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	strj = ft_calloc((l1 + l2 + 1), sizeof(char));
	if (!strj)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		strj[i] = s1[i];
		i++;
	}
	l2 = 0;
	while (s2 && s2[l2] != '\0')
	{
		strj[i + l2] = s2[l2];
		l2++;
	}
	return (strj);
}

char	*ft_freecontent(char *fcontent)
{
	char	*tmp;
	int		start;
	int		size;

	start = 0;
	if (fcontent == NULL)
		return (NULL);
	while (fcontent[start] != '\n' && fcontent[start] != '\0')
		start++;
	if (fcontent[start] == '\0')
	{
		free (fcontent);
		return (NULL);
	}
	size = start + 1;
	while (fcontent[size] != '\0')
		size++;
	tmp = ft_calloc(size - start + 1, sizeof(char));
	if (tmp == NULL)
		return (NULL);
	size = 0;
	while (fcontent[start + 1] != '\0')
		tmp[size++] = fcontent[(start++) + 1];
	free(fcontent);
	return (tmp);
}

char	*ft_extractline(char *fcontent)
{
	char	*line;
	int		start;
	int		i;

	i = 0;
	start = 0;
	if (fcontent == NULL || fcontent[0] == '\0')
		return (NULL);
	while (fcontent[start] != '\n' && fcontent[start] != '\0')
		start++;
	line = ft_calloc(start + 1 + (fcontent[start] == '\n'), sizeof(char));
	if (line == NULL)
		return (NULL);
	if (fcontent[start] == '\n')
		start++;
	while (i < start && fcontent[i] != '\0')
	{
		line[i] = fcontent[i];
		i++;
	}
	return (line);
}

char	*ft_readline(int fd, char *buffer, char *fcontent)
{
	int		bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!fcontent)
			fcontent = ft_calloc(2, sizeof(char));
		tmp = fcontent;
		fcontent = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (fcontent);
}

char	*get_next_line(int fd)
{
	static char	*fcontent;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (ft_strchr(fcontent, '\n') == NULL)
		fcontent = ft_readline(fd, buffer, fcontent);
	free(buffer);
	line = ft_extractline(fcontent);
	if (!line)
	{
		free(fcontent);
		fcontent = NULL;
		return (NULL);
	}
	fcontent = ft_freecontent(fcontent);
	return (line);
}

static int	ft_checkchr(char const *s, char const c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		count;
	char	*strt;

	start = 0;
	while (s1[start] != '\0' && ft_checkchr(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && ft_checkchr(set, s1[end]))
		end--;
	strt = (char *)malloc(sizeof(char) * (end - start) + 2);
	if (!strt)
		return (NULL);
	count = 0;
	while (start <= end)
	{
		strt[count] = s1[start];
		start++;
		count++;
	}
	strt[count] = '\0';
	return (strt);
}



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
			printf("count: %i\n", count);
			free(line);
		}
		else
		{
			free(line);
			break;
		}
	}
	printf("final count: %i\n", count);
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
	return 1;
}

int	ft_fillMap(t_game *game, char *fileMap)
{
	int		fd;
	int		i;
	char	*row;
	int		y;

	i = 0;
	fd = open(fileMap, O_RDONLY);
	y = game->y;
	printf("y: %i\n", y);
	printf("fd: %i\n", fd);
	while (i < y)
	{
		row = get_next_line(fd);
		game->map[i] = ft_strtrim(row, "\n");
		printf("%s\n", game->map[i]);
		free(row);
		i++;
	}
	close(fd);
	return (1);
}
int ft_checkRow(char *row)
{
	int i;

	i = 0;
	while (row[i] != '\0')
	{
		if (row[i] != '1' && row[i] != '0' && row[i] != 'C' && row[i] != 'E' && row[i] != 'P')
			return (0);
		i++;
	}
	return (1);
}
ft_fullWall(char *row)
{
	int i;

	i = 0;
	while (row[i] != '\0')
	{
		if (row[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int ft_checkPlayerToExit (char **map, int x, int y)
{
	int i;
	int j;
	int p_x;
	int p_y;
	int e_x;
	int e_y;
	int now_x;
	int now_y;

	i = 0;
	while (i < y)
	{
		if (ft_strchr(map[i], 'E'))
		{
			e_x = ft_strchr(map[i], 'E') - map[i];
			e_y = i;
		}
		if (ft_strchr(map[i], 'P'))
		{
			p_x = ft_strchr(map[i], 'P') - map[i];
			p_y = i;
		}
		i++;
	}
	printf("p_x: %i\n", p_x);
	printf("p_y: %i\n", p_y);
	printf("e_x: %i\n", e_x);
	printf("e_y: %i\n", e_y);
	now_x = p_x;
	now_y = p_y;
	if (map[now_y+1][now_x] == '1' && map[now_y-1][now_x] == '1' && map[now_y][now_x-1] == '1' && map[now_y][now_x+1] == '1')
		return (0);
	while (1)
	{
		if (map[now_y+1][now_x] == 'E')
		{
			printf("%c\n",map[now_y+1][now_x]);
			break;
		}
		if (map[now_y-1][now_x] == 'E')
		{
			printf("%c\n",map[now_y-1][now_x]);
			break;
		}

		if (map[now_y][now_x-1] == 'E')
		{
			printf("%c\n",map[now_y][now_x-1]);
			break;
		}
		if (map[now_y][now_x] == 'E')
		{
			printf("%c\n",map[now_y][now_x+1]);
			break;
		}
		if (map[now_y+1][now_x] != '1')
			map[now_y+1][now_x] = 'P';
		if (map[now_y-1][now_x] != '1')
			map[now_y-1][now_x] = 'P';
		
		if (map[now_y][now_x-1] != '1')
			map[now_y][now_x-1] = 'P';
		if (map[now_y][now_x+1] != '1')
			map[now_y][now_x+1] = 'P';
		i = 0;
		while (y > i)
		{
			printf("game->map[%i] = %s\n", i,map[i]);
			i++;
		}
		break;
	}
	return (0);
}

int ft_checkMap(t_game *game)
{
	int x;
	int y;
	int i;
	int e;
	int p;
	int c;

	x = game->x;
	y = game->y;
	i = 0;
	c = 0;
	e = 0;
	p = 0;
	if (ft_fullWall(game->map[0]) == 0 || ft_fullWall(game->map[y - 1]) == 0)
		return (0);
	while (i < y)
	{
		if (ft_strchr(game->map[i], 'E'))
			e++;
		if (ft_strchr(game->map[i], 'P'))
			p++;
		if (ft_strchr(game->map[i], 'C'))
			c++;
		if (game->map[i][0] != '1' || game->map[i][x - 1] != '1' || !ft_checkRow(game->map[i]))
		{
			printf("error\n");
			return (0);
		}
		i++;
	}
	if (e != 1 || p != 1 || c == 0)
		return (0);

	if (ft_checkPlayerToExit(game->map, game->x, game->y) == 0)
		return (0);
	return (1);
}
// int main() 
// {
// 	//printf("main\n");
// 	//t_game game;
// 	/*
// 	if (argc != 2)
// 		return (0);
// 	ft_getWindowSize(&game, argv[1]);
// 	*/
// 	//char *argv = "testMap.ber";
// 	//ft_getWindowSize(&game, argv);
// 	//printf("window: %i * %i\n", game.x, game.y);
// 	printf('wtf');
// 	//game.map = (char **)malloc(sizeof(char *) * (game.y + 1));
// 	/*
// 	printf("tab");
// 	if (!game.map)
// 	{
// 		printf("error");
// 		return (0);
// 	}
// 	else 
// 		printf('ciao');
// 	game.map[game.y + 1] = NULL;
// 	ft_createMatrix(&game, argv);
// 	int i = 0;
// 	while (game.map)
// 	{
// 		printf("game->map[%i] = %s", i,game.map[i]);
// 		i++;
// 	}
//     return 0;
// 	*/
// }


//int main(int argc, char **argv)
int main()
{
	printf("main\n");
	t_game game;
	/*
	if (argc != 2)
		return (0);
	ft_getWindowSize(&game, argv[1]);
	*/
	char *argv = "testMap.ber";
	ft_getWindowSize(&game, argv);
	printf("window: %i * %i\n", game.x, game.y);
	game.map = (char **)malloc(sizeof(char *) * (game.y + 1));
	if (!game.map)
	{
		printf("error");
		return (0);
	}
	else
		printf("ok\n");
	// game.map[game.y + 1] = NULL;
	// for (int i = 0; i < game.y+2; i++)
	// {
	// 	printf("%i\n", game.map[i] != NULL);
	// }
	// printf("%i\n", game.map[game.y + 1] == NULL);
	//free(game.map);
	ft_fillMap(&game, argv);
	// int i = 0;
	// while (game.y > i)
	// {
	// 	printf("game->map[%i] = %s\n", i,game.map[i]);
	// 	i++;
	// }

	if (ft_checkMap(&game))
		printf("map ok\n");
	else
		printf("map ko\n");
	return 0;
}

