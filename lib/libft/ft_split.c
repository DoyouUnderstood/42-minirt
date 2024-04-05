/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:05:57 by alletond          #+#    #+#             */
/*   Updated: 2023/10/10 19:13:34 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_word_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	**free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static char	*next_word(char **ps, char c)
{
	size_t	len;
	char	*s;
	char	*word;

	len = 0;
	s = *ps;
	while (*s == c)
		s++;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, len + 1);
	*ps = s + len;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_count;
	char	**split;
	size_t	i;

	if (!s)
		return (NULL);
	word_count = get_word_count(s, c);
	split = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		split[i] = next_word((char **)&s, c);
		if (!split[i])
			return (free_split(split));
		i++;
	}
	split[word_count] = NULL;
	return (split);
}

/*
void	display_split_array(char **arr)
{
	int	i;

	if (!arr)
	{
		printf("Le tableau est NULL\n");
		return ;
	}
	i = 0;
	while (arr[i])
	{
		printf("Mot %d : %s\n", i, arr[i]);
		i++;
	}
}

int	main(void)
{
	char	**result;
	char	str[] = "Bonjour, comment allez-vous aujourd'hui ?";
	char	delimiter;
	int		i;

	delimiter = ' ';
	result = ft_split(str, delimiter);
	display_split_array(result);
	// Libérer la mémoire allouée
	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}
*/
