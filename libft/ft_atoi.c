/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:14:26 by lchambos          #+#    #+#             */
/*   Updated: 2025/11/06 14:18:35 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	char	sign;
	int		result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return (sign * result);
}
