/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 09:39:49 by dwilun            #+#    #+#             */
/*   Updated: 2024/01/27 10:13:04 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
	{
		printf("s1: %s\n", s1);
		return (-1);
	}
	if (n <= 0)
		return (0);
	while (i < n && s1[i] == s2[i] && (s1[i] || s2[i]))
		i++;
	printf("s1: %c\n", s1[i]);
	if (i == n)
		return ((unsigned char)s1[i - 1] - (unsigned char)s2[i - 1]);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		count;
	char	*strt;

	start = 0;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]) != NULL)
		start++;
	end = ft_strlen((char *)s1) - 1;
	while (end > start && ft_strchr(set, s1[end]) != NULL)
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

char	**ft_cpymatrix(char **matrix, int row)
{
	char	**new;
	int		i;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (row + 1));
	if (!new)
	{
		return (0);
	}
	while (i < row)
	{
		new[i] = ft_strdup(matrix[i]);
		if (!new[i])
		{
			ft_free_matrix(new, i);
			return (0);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	*ft_itoa(int num)
{
	char	*str;
	int		i;
	int		n;

	n = num;
	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	while (i > 0)
	{
		str[i - 1] = num % 10 + '0';
		num /= 10;
		i--;
	}
	return (str);
}
