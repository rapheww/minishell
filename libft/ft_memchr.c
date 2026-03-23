/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:38:59 by lchambos          #+#    #+#             */
/*   Updated: 2025/11/12 13:19:57 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)str;
	while (n--)
	{
		if (*tmp == (unsigned char)c)
			return (tmp);
		tmp++;
	}
	return (0);
}
