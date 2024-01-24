/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 09:39:49 by dwilun            #+#    #+#             */
/*   Updated: 2024/01/20 15:58:30 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	ft_freeMatrix(char **matrix, int row)
{
	int i;

	i = -1;
	while (++i < row)
		free(matrix[i]);
	free(matrix);
}

char	**ft_cpyMatrix(char **matrix, int row)
{
	char	**new;
	int		i;

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