
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
#include "./get_next_line/get_next_line.h"

// int ft_strlen_n(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str && str[i] && str[i] != '\n')
// 		i++;
// 	return (i);
// }
// int ft_check_out (char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i] != '\0' && str[i] != '\n')
// 	{
// 		if (str[i] != 49)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }
// int ft_check_in (char *str)
// {
// 	int i;

// 	i = 0;
// 	if (str[0] != 49)
// 		return (0);
// 	while (str[i] != '\0' && str[i] != '\n')
// 		i++;
// 	if (str[i - 1] != 49)
// 		return (0);
// 	return (1);
// }
// int	ft_start_old (int fd)
// {
// 	int		i;
// 	int		len;
// 	char	*line;

// 	i = 0;
// 	line = get_next_line(fd);
// 	len = ft_strlen_n(line);
// 	max = ft_calloc
// 	if (ft_check_out(line) == 0)
// 	{
// 		printf("Error\n");
// 		free(line);
// 		return (0);
// 	}
// 	else
// 	{
// 		printf("%s", line);
// 	}
// 	while ((line = get_next_line(fd)))
// 	{
// 		if (ft_strlen_n(line) != len)
// 		{
// 			printf("Error\n");
// 			free(line);
// 			return (0);
// 		}
// 		if (ft_check_in(line) == 0)
// 		{
// 			printf("Error\n");
// 			free(line);
// 			return (0);
// 		}
// 		else
// 		{
// 			printf("%s", line);
// 		}
// 	}
// 	return (1);
// }

int	ft_line_leght(int fd)
{
	
	char	buffer[1];
	int		bytes;
	int		len;

	printf("\nfd1 dentro %i\n", fd);
	bytes = 1;
	printf("\nfd2 dentro %i\n", fd);
	buffer[0] = '\0';
	printf("\nfd3 dentro %i\n", fd);
	len = 0;
	printf("\nfd4 dentro %i\n", fd);
	while (bytes == 1)
	{
		printf("\ndio cane\n");
		bytes = read(fd, buffer, 1);
		if (buffer[0] != '\n')
			len++;
		else
			break ;
	}
	return (len);
}
int ft_count_lines(int fd, int x)
{
	char	*line;
	int 	count;

	count = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strlen(line) < x || (ft_strlen(line) == 1 && line[0] != '\n'))
		{
			free(line);
			return 0;
		}
		else
		{
			free(line);
			count++;
		}
	}
	return (line);
}
int	ft_start ()
{
	int	fd;
	int	x;
	int	y;

	fd = open("testMap.ber", O_RDONLY);
	if (fd < 0)
	{
		printf("Error\n");
		return (0);
	}
	printf ("\nfd fuori %i\n", fd);
	x = ft_line_leght(fd);
	y = ft_count_lines(fd, x);
	printf("%i * %i", x, y);
}


//cc main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c && ./a.out
int main(void) 
{
    
    ft_start();
	printf("\ngg\n");

    return 0;
}