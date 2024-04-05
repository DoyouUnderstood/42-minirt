/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:43:41 by alletond          #+#    #+#             */
/*   Updated: 2023/11/09 18:48:11 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "../libft/libft.h"

int		ft_printf(const char *format, ...);
int		handle_conversion(char format, va_list args);
int		ft_putnbr_hex(unsigned int n, char format);
int		ft_putnbr(int n);
int		ft_unsigned_putnbr(unsigned int n);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		pointer_to_hex(void *ptr);
int		count_size(int n);
int		count_digits(unsigned long ptr);
int		handle_di(int job);
size_t	ft_strlen(const char *str);

#endif