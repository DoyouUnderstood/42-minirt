/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erabbath <erabbath@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:42:00 by alletond          #+#    #+#             */
/*   Updated: 2024/05/22 11:38:43 by erabbath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*stackcut(char *stack, int pos)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(stack) - pos;
	res = malloc(len + 1 * sizeof(char));
	i = 0;
	while (stack[i + pos])
	{
		res[i] = stack[i + pos];
		i++;
	}
	free(stack);
	res[i] = '\0';
	return (res);
}

char	*fill_stack(char *stack, int fd, int *readret)
{
	char	buffer[BUFFER_SIZE + 1];
	int		tmp;

	tmp = read(fd, buffer, BUFFER_SIZE);
	*readret = tmp;
	if (tmp == -1)
		return (stack);
	buffer[tmp] = '\0';
	stack = ft_strjesaispas(stack, buffer);
	return (stack);
}

char	*readret0(char **stack, int readret)
{
	char	*res;
	int		len;

	len = 0;
	if (readret == 0 && *stack[0] != '\0')
	{
		len = ft_strlen(*stack);
		res = ft_strndup_custom(*stack, len);
		free(*stack);
		*stack = NULL;
		return (res);
	}
	else
	{
		free(*stack);
		*stack = NULL;
		return (NULL);
	}
}

int	check_error(int fd, char **stack)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (1);
	if (!*stack)
	{
		*stack = (char *)malloc(sizeof(char));
		if (!*stack)
			return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stack;
	char		*res;
	int			readret;
	int			pos;

	if (check_error(fd, &stack))
		return (NULL);
	while (1)
	{
		pos = check_line(stack);
		if (pos == -1)
		{
			stack = fill_stack(stack, fd, &readret);
			if (readret <= 0)
				return (readret0(&stack, readret));
		}
		else
		{
			res = ft_strndup_custom(stack, pos);
			stack = stackcut(stack, pos + 1);
			return (res);
		}
	}
}
