/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:20:22 by lchambos          #+#    #+#             */
/*   Updated: 2025/11/06 14:13:16 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	if (to_find[0] == '\0')
		return ((char *)src);
	i = 0;
	if ((!src || !to_find) && len == 0)
		return (0);
	while (i < len && src[i])
	{
		j = 0;
		while (to_find[j] && src[i + j] == to_find[j]
			&& i + j < len && src[i + j])
			j++;
		if (to_find[j] == '\0')
			return ((char *)src + i);
		i++;
	}
	return (0);
}
