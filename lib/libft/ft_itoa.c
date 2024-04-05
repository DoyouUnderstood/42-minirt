/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:36:50 by alletond          #+#    #+#             */
/*   Updated: 2023/10/10 16:23:12 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		is_neg;
	int		size;

	is_neg = (n < 0);
	size = count_size(n);
	res = (char *)malloc(size + 1);
	if (!res)
		return (NULL);
	res[size] = '\0';
	if (n == 0)
		res[0] = '0';
	while (n != 0)
	{
		size--;
		if (is_neg)
			res[size] = '0' - (n % 10);
		else
			res[size] = '0' + (n % 10);
		n /= 10;
	}
	if (is_neg)
		res[0] = '-';
	return (res);
}

/*
int	main(void)
{
	printf("result : %s\n", ft_itoa(-1999));
	printf("result : %s\n", ft_itoa(758934));
	printf("result : %s\n", ft_itoa(0));
	printf("result : %s\n", ft_itoa(-0));
	printf("result : %s\n", ft_itoa(-483098));
	printf("result : %s\n", ft_itoa(1));
	return (0);
}
*/
