/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 21:28:42 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/30 23:42:31 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_atoi(char *str)
{
	long	result;

	result = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		if (result > INT_MAX)
			return (0);
		str++;
	}
	return (1);
}

static int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (!check_atoi(str))
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	make_exit(char **str, t_data **data)
{
	if ((*data)->flag == 0)
		ft_putstr_fd("exit\n", 1);
	if (!str[1])
	{
		(*data)->check_exit = 1;
		return (close((*data)->fd_in), close((*data)->fd_out), 0);
	}
	if (str_isdigit(str[1]) && str[2])
		return (ft_putstr_fd("exit: too many arguments\n", 1), 1);
	if (!str_isdigit(str[1]))
	{
		(*data)->check_exit = 1;
		return (msg3("exit: ", str[1], ": numeric argument required", 2));
	}
	(*data)->check_exit = 1;
	return (close((*data)->fd_in), close((*data)->fd_out), ft_atoi(str[1]));
}
