/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:46:05 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/16 19:27:44 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(const char *str, char sep)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] != sep)
		{
			words++;
			while (str[i] != sep && str[i])
				i++;
		}
		else
			i++;
	}
	return (words);
}

static void	*free_all(char **str, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static char	**write_array(char **dest, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		k = i;
		while (s[i] != c && s[i])
			i++;
		if (k >= (size_t)ft_strlen(s))
			dest[j++] = NULL;
		else
		{
			dest[j++] = ft_substr(s, k, i - k);
			if (!dest[j - 1])
				return (free_all(dest, count_words(s, c)));
		}
	}
	return (dest);
}

char	**ft_split(const char *s, char c)
{
	char	**dest;
	int		c_words;

	if (!s)
		return (NULL);
	c_words = count_words((char *)s, c);
	dest = malloc(sizeof(char *) * (c_words + 1));
	if (!dest)
		return (NULL);
	dest = write_array(dest, s, c);
	if (!dest)
		return (NULL);
	dest[c_words] = NULL;
	return (dest);
}
