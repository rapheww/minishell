/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:07:59 by lchambos          #+#    #+#             */
/*   Updated: 2025/11/15 16:50:05 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*tmp2;

	if (!dest && !src)
		return (0);
	tmp = (unsigned char *)dest;
	tmp2 = (unsigned char *)src;
	if (dest <= src)
	{
		while (n--)
			*tmp++ = *tmp2++;
	}
	else
	{
		while (n--)
			tmp[n] = tmp2[n];
	}
	return (dest);
}
