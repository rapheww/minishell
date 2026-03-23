/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:37:03 by lchambos          #+#    #+#             */
/*   Updated: 2025/11/13 13:53:56 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t length)
{
	int	i;

	i = 0;
	while (length && s1[i] && s2[i] && (s1[i] == s2[i]))
	{
		i++;
		length--;
	}
	if (length == 0)
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
