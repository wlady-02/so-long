/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwilun <dwilun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:22:46 by dwilun            #+#    #+#             */
/*   Updated: 2024/01/20 10:14:32 by dwilun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
