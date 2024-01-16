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


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

int ft_printError (char *error)
{
    printf("Error:\n%s",error);
    return (0);
}
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
char	*ft_strdup(char *s)
{
	int		i;
	char	*result;

	i = 0;
	result = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	while (s[i] != '\0')
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
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
	end = ft_strlen((char *)s1) - 1;
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
typedef struct s_coord
{
    int x;
    int y;
} t_coord;

typedef struct s_chr
{
    int c;
    int p;
    int e;
    t_coord pCoord;
    t_coord eCoord;
} t_chr;



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
			return (0);//error
		}
	}
	return (count);
}

void ft_freeMatrix(char **matrix, int row)
{
    int i;

    i = 0;
    while (i < row)
        free(matrix[i++]);
    free(matrix);
}


int ft_getWindowSize(t_game *game, char *fileMap)
{
	int	fd;
	char *row;

	fd = open(fileMap, O_RDONLY);
	if (fd == -1)
		return (0);//error
	row = get_next_line(fd);
	game->x = ft_rowLen(row);
	free(row);
	game->y = ft_countLine(fd, game->x);
	close(fd);
	if (game->y == game->x 
    || game->y < 3 
    || game->x < 3 
    || (game->y == 3 && game->x < 5) 
    || (game->x == 3 && game->y < 5))
	    return (0);
	return (1);
}


int	ft_fillMap(t_game *game, char *fileMap)
{
	int		fd;
	int		i;
	char	*row;
	int		y;

	i = 0;
	fd = open(fileMap, O_RDONLY);
	if (fd == -1)
		return (0);//error
	y = game->y;
	while (i < y)
	{
		row = get_next_line(fd);
		if (!row)
		    return (0);//error
		game->map[i] = ft_strtrim(row, "\n");
		free(row);
		if (!game->map[i])
		{	
			ft_freeMatrix(game->map, i);
			return (0);//error
		}
		i++;
	}
	game->map[i] = NULL;
	close(fd);
	return (1);
}

int ft_checkRow(char *row, int len, int y, t_chr *chr)
{
	int i;

	i = 0;
	//printf("row: %s\n", row);
	if (row[i] != '1' || row[len-1] != '1')
	    return (0);//error
	while (row[i] != '\0')
	{
		if (row[i] != '1' && row[i] != '0' && row[i] != 'C' && row[i] != 'E' && row[i] != 'P')
			return (0);//error
		if (row[i] == 'E')
		{
		    chr->eCoord.x = i;
		    chr->eCoord.y = y;
		    chr->e++;
		}
		else if (row[i] == 'P')
		{
		    chr->pCoord.x = i;
		    chr->pCoord.y = y;
		    chr->p++;
			//printf("y: %i x: %i\n", chr->eCoord.y, chr->eCoord.x);
			//printf("row: %s\n", row);
		}
		else if (row[i] == 'C')
		    chr->c++;
		i++;
	}
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
char **ft_cpyMatrix(char **matrix, int row)
{
    char    **new;
    int     i;

    i = 0;
    new = (char **)malloc(sizeof(char *) * (row + 1));
    if (!new)
	{
		return (0);//error
	}
    while (i < row)
    {
        new[i] = ft_strdup(matrix[i]);
		//printf("new[%i] = %s\n", i, new[i]);
        if (!new[i])
		{
			ft_freeMatrix(new, i);
			return (0);//error
		}
        i++;
    }

    new[i] = NULL;

    return (new);
    
}
int isValidCordinate(t_coord coord, t_coord window)
{
    if (coord.y < 0 || coord.x < 0)
        return (0);//error
    if (coord.y >= window.y || coord.x >= window.x)
        return (0);//error
    return (1);
}






/*
int ft_addChr(t_game *game)
{
    
}
*/

void  ft_initChr(t_chr *chr)
{
	chr->c = 0;
	chr->p = 0;
	chr->e = 0;
	chr->pCoord.x = -1;
	chr->pCoord.y = -1;
	chr->eCoord.x = -1;
	chr->eCoord.y = -1;
}

void ft_printMatrix(char **matrix, int row)
{
	int i;

	i = 0;
	while (i < row)
	{
		printf("matrix[%i] = %s\n", i, matrix[i]);
		i++;
	}
}

int ft_playerToExit (char **map, t_coord start)
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

int ft_checkPlayerToExit(char **map, int y,  t_coord player)
{
	char 	**tmp;
	int 	i;
	i = 0;
	tmp = ft_cpyMatrix(map, y);
	//ft_printMatrix(tmp, y);
    if (!tmp)
    {
	    printf("ft_clone_matrix");
	    return (0);//error
	}
	ft_playerToExit(tmp, player);
	while (i < y)
	{
		if (ft_strchr(tmp[i], 'C') || ft_strchr(tmp[i], 'E'))
		{
			printf("ft_strchr(tmp[i], 'C')");
			ft_freeMatrix(tmp, y);
			return (0);//error
		}
		i++;
	}
	ft_freeMatrix(tmp, y);
	return (1);
}
int ft_checkMap(t_game *game)
{
	int i;
	t_chr chr;

	i = 0;
	if (ft_fullWall(game->map[0]) == 0 || ft_fullWall(game->map[game->y-1]) == 0)
	    return (0);//error
	ft_initChr(&chr);
	while (i < game->y)
	{
	    if (!ft_checkRow(game->map[i], game->x, i, &chr))
			return (0);//error
		i++;
	}
	//printf("ex: %i ey: %i\npx: %i py: %i\n", chr.eCoord.x, chr.eCoord.y, chr.pCoord.x, chr.pCoord.y);
	if (chr.e != 1 || chr.p != 1 || chr.c == 0)
	    return (0);//error
	if (ft_checkPlayerToExit(game->map, game->y, chr.pCoord) == 0)
	    return (0);//error
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
	printf("Main\n");
	t_game game;
	/*
	if (argc != 2)
		return (0);
	ft_getWindowSize(&game, argv[1]);
	*/
	char *argv = "testMap.ber";
	if (ft_getWindowSize(&game, argv) == 0)
	    return (ft_printError("dimensioni non valide"));//error
	printf("window: %i * %i\n", game.x, game.y);
	game.map = (char **)malloc(sizeof(char *) * (game.y + 1));
	if (!game.map)
		return (ft_printError("mappa non allacata"));//error
	else
	    printf("hey?\n");
	// game.map[game.y + 1] = NULL;
	// for (int i = 0; i < game.y+2; i++)
	// {
	// 	printf("%i\n", game.map[i] != NULL);
	// }
	// printf("%i\n", game.map[game.y + 1] == NULL);
	//free(game.map);
	/*
	if ((game.y == 3 && game.x == 5) || (game.y == 5 && game.x == 3))
	{
	    if (!ft_smallMap(&game, argv))
	        return (ft_printError("mappa non valida"));//error
	}
	else
	{
	    ft_fillMap(&game, argv);
	    if (!ft_checkMap(&game))
            return (ft_printError("mappa non valida"));//error
	}
	*/
	// int i = 0;
	// while (game.y > i)
	// {
	// 	printf("game->map[%i] = %s\n", i,game.map[i]);
	// 	i++;
	// }
	printf("map\n");
	ft_fillMap(&game, argv);
	printf("%s", &game.map[game.y]);
	if (!ft_checkMap(&game))
        return (ft_printError("mappa non valida"));//error
    else
        printf("map ok\n");
	ft_printMatrix(game.map, game.y);
	
	return 0;
}