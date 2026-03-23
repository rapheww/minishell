/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:59:09 by lchambos          #+#    #+#             */
/*   Updated: 2025/11/13 15:53:35 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*dest;

	dest = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			dest = (char *)s;
		s++;
	}
	if (c == 0)
		return ((char *)s);
	if (*s == (unsigned char)c)
		dest = (char *)s;
	return (dest);
}
