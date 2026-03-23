/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:30:27 by lchambos          #+#    #+#             */
/*   Updated: 2025/11/07 18:19:28 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *p, int value, size_t len)
{
	unsigned char	*dest;

	dest = p;
	while (len > 0)
	{
		*dest = (unsigned char)value;
		dest++;
		len--;
	}
	return (p);
}
