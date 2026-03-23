/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:20:17 by lchambos          #+#    #+#             */
/*   Updated: 2025/11/10 16:33:41 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_num(long num)
{
	size_t	size;

	size = 0;
	if (num < 0)
	{
		size = 1;
		num *= -1;
	}
	if (num == 0)
		size = 1;
	else
	{
		while (num > 0)
		{
			num /= 10;
			size++;
		}
	}
	return (size);
}

char	*ft_itoa(int n)
{
	size_t	size;
	long	num;
	char	*str;
	size_t	neg_num;

	size = count_num((long)n);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	num = (long)n;
	neg_num = 0;
	if (num < 0)
	{
		neg_num = 1;
		str[0] = '-';
		num *= -1;
	}
	str[size] = '\0';
	while (size > neg_num)
	{
		str[size - 1] = num % 10 + '0';
		num /= 10;
		size--;
	}
	return (str);
}
