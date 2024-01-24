/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 09:46:46 by dwilun            #+#    #+#             */
/*   Updated: 2024/01/20 16:42:02 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "./minilibx/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define SIZE 64
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100

# define UP 65362
# define LF 65361
# define RG 65363
# define DW 65364

# define ABS(value) (value < 0) * -1 * value + value * (value > 0)

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_chr
{
	int		c;
	int		p;
	int		e;
	int		i;
	t_coord	pcoord;
	t_coord	ecoord;
}	t_chr;

typedef struct s_game
{
	int		x;
	int		y;
	char	**map;
	void	*mlx;
	void	*win;
	void	*textures[6];
	int		collectible;
	int		moves;
	t_coord	player;
	t_coord	exit;
}	t_game;


void	ft_freeMatrix(char **matrix, int row);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *str, int start, int len);
int		ft_fillMap(t_game *game, char *fileMap);
int		ft_checkMap(t_game *game);
int		ft_checkRow(char *row, int len, t_chr *chr, int flag);
int		ft_fullWall(char *row);
char	**ft_cpyMatrix(char **matrix, int row);
int		ft_playerToExit(char **map, t_coord start);
int		ft_checkPlayerToExit(char **map, int y, t_coord player);
char	*ft_strtrim(char const *s1, char const *set);

int		ft_getWindowSize(t_game *game, char *fileMap);
void	ft_printMatrix(char **matrix, int row);

char	*get_next_line(int fd);
char	*ft_readline(int fd, char *buffer, char *fcontent);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
int		ft_strlen(char *str);
char	*ft_freecontent(char *fcontent);
char	*ft_extractline(char *fcontent);
#endif