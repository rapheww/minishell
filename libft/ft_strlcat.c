/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:18:00 by lchambos          #+#    #+#             */
/*   Updated: 2025/11/12 14:59:19 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	slen;
	size_t	dlen;
	size_t	i;
	size_t	freespace;

	slen = ft_strlen(src);
	dlen = ft_strlen(dest);
	i = 0;
	freespace = n - dlen - 1;
	if (dlen >= n)
		return (n + slen);
	while (src[i] && freespace--)
	{
		dest[dlen + i] = src[i];
		i++;
	}
	dest[dlen + i] = '\0';
	return (dlen + slen);
}
