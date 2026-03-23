/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 21:28:42 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/22 17:51:34 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	make_exit(char **str, t_data **data)
{
	int	i;

	if ((*data)->flag == 0)
		ft_putstr_fd("exit\n", 1);
	if (!str[1])
		return ((*data)->check_exit = 1, close((*data)->fd_in),
			close((*data)->fd_out), 0);
	if (str[2])
		return (ft_putstr_fd("exit: too many arguments\n", 1), 1);
	i = 0;
	while (str[1][i])
	{
		if (!ft_isdigit(str[1][i]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(str[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			(*data)->check_exit = 1;
			return (2);
		}
		i++;
	}
	(*data)->check_exit = 1;
	return (close((*data)->fd_in), close((*data)->fd_out), ft_atoi(str[1]));
}
