/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:41:21 by alletond          #+#    #+#             */
/*   Updated: 2023/10/09 16:43:52 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, int n)
{
	int		i;
	char	*str_s1;
	char	*str_s2;

	i = 0;
	str_s1 = (char *)s1;
	str_s2 = (char *)s2;
	if (n == 0)
		return (0);
	while ((i < n - 1) && (str_s1[i] == str_s2[i]))
		i++;
	return ((unsigned char)str_s1[i] - (unsigned char)str_s2[i]);
}
