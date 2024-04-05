/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:27:48 by alletond          #+#    #+#             */
/*   Updated: 2023/11/09 18:47:09 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_di(int job)
{
	int		i;
	char	*res;

	if (job == -2147483648)
	{
		ft_putstr("-2147483648");
		return (11);
	}
	res = ft_itoa(job);
	i = 0;
	if (!res)
	{
		return (0);
	}
	while (res[i])
	{
		ft_putchar(res[i]);
		i++;
	}
	free(res);
	return (i);
}

int	ft_putnbr_hex(unsigned int n, char format)
{
	const char	*hex_digits_lowercase = "0123456789abcdef";
	const char	*hex_digits_uppercase = "0123456789ABCDEF";
	const char	*chosen_digits;
	int			len;

	len = count_digits(n);
	if (format == 'x')
		chosen_digits = hex_digits_lowercase;
	else
		chosen_digits = hex_digits_uppercase;
	if (n >= 16)
	{
		ft_putnbr_hex(n / 16, format);
		ft_putnbr_hex(n % 16, format);
	}
	else
	{
		ft_putchar(chosen_digits[n]);
	}
	return (len);
}

int	handle_conversion(char format, va_list args)
{
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'd' || format == 'i')
		return (handle_di(va_arg(args, int)));
	else if (format == 'p')
		return (pointer_to_hex(va_arg(args, void *)));
	else if (format == 'x' || format == 'X')
		return (ft_putnbr_hex(va_arg(args, unsigned int), format));
	else if (format == 'u')
		return (ft_unsigned_putnbr(va_arg(args, unsigned int)));
	else if (format == '%')
		return (ft_putchar('%'));
	else
		return (ft_putchar(format));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += handle_conversion(format[i], args);
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}

// int	main(void)
// {
// 	int	i;
// 	int	j;

// 	i = ft_printf("%s\n", "salut");
// 	j = printf("%s\n", "salut");
// 	printf("i = %d\n, j = %d\n", i, j);
// 	return (0);
// }