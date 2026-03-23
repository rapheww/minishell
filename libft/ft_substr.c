/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:52:12 by lchambos          #+#    #+#             */
/*   Updated: 2025/11/12 14:49:38 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	i = 0;
	while (i < len && start < (size_t)ft_strlen(s) && s[start + i])
		i++;
	j = 0;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	while (j < i && start < (size_t)ft_strlen(s))
	{
		dest[j] = s[start + j];
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
