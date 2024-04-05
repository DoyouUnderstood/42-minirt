/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:42:40 by alletond          #+#    #+#             */
/*   Updated: 2023/10/16 11:20:57 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	count_digits(unsigned long ptr)
{
	int	count;

	count = 0;
	while (ptr >= 16)
	{
		ptr = ptr / 16;
		count++;
	}
	return (count + 1);
}

int	pointer_to_hex(void *ptr)
{
	char			*hex_chars;
	unsigned long	num;
	char			str[17];
	size_t			len;
	size_t			val_ret;

	hex_chars = "0123456789abcdef";
	num = (unsigned long)ptr;
	len = count_digits(num);
	val_ret = len;
	str[len] = '\0';
	while (len--)
	{
		str[len] = hex_chars[num % 16];
		num /= 16;
	}
	ft_putstr("0x");
	ft_putstr(str);
	return (val_ret + 2);
}
