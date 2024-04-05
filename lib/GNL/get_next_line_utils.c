/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:43:11 by alletond          #+#    #+#             */
/*   Updated: 2023/11/09 18:45:49 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjesaispas(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	res = malloc((sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	len = 0;
	i = 0;
	while (s1[i])
		res[len++] = s1[i++];
	i = 0;
	while (s2[i])
		res[len++] = s2[i++];
	res[len] = '\0';
	free(s1);
	s1 = NULL;
	return (res);
}

char	*ft_strndup_custom(const char *s, size_t pos)
{
	char	*res;
	size_t	i;

	res = malloc(sizeof(char) * pos + 2);
	i = 0;
	while (i <= pos)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
