/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:21:12 by marvin            #+#    #+#             */
/*   Updated: 2024/02/26 21:21:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"

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
	void	*textures[14];
	int		collectible;
	int		moves;
	t_coord	player;
	t_coord	exit;
	int		frame;
}	t_game;

void	ft_error(char *str, int num, t_game *game);
void	ft_put_img(t_game *game, int index, int y, int x);
int		ft_get_input(int keycode, t_game *game);
void	ft_victory(t_game *game);
void	ft_gameover(t_game *game);
int		ft_destroy(t_game *game);
void	ft_free_matrix(char **matrix, int row);
char	*ft_itoa(int num);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *str, int start, int len);
void	ft_fill_map(t_game *game, char *fileMap);
int		ft_check_map(t_game *game);
int		ft_check_row(char *row, int len, t_chr *chr, int flag);
char	**ft_cpymatrix(char **matrix, int row);
int		ft_player_to_exit(char **map, t_coord start);
int		ft_check_exit(char **map, int y, t_coord player);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_init_check(int argc, char **argv);
void	ft_getwindowsize(t_game *game, char *fileMap);
void	ft_printMatrix(char **matrix, int row);
int		ft_animate(t_game *game);
void	ft_endgame(t_game *game, int victory);

char	*get_next_line(int fd);
char	*ft_readline(int fd, char *buffer, char *fcontent);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
int		ft_strlen(char *str);
char	*ft_freecontent(char *fcontent);
char	*ft_extractline(char *fcontent);

#endif