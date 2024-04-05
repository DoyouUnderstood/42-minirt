/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:07:25 by alletond          #+#    #+#             */
/*   Updated: 2023/11/09 18:48:32 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_size(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_unsigned_putnbr(unsigned int n)
{
	int	len;

	if (n >= 10)
	{
		len = ft_unsigned_putnbr(n / 10);
		len += ft_unsigned_putnbr(n % 10);
	}
	else
	{
		ft_putchar(n + '0');
		return (1);
	}
	return (len);
}
