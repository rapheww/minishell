/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapheww <rapheww@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:23:03 by rchaumei          #+#    #+#             */
/*   Updated: 2026/03/24 14:31:12 by rapheww          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_flags(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i = 1;
	while (i < ft_strlen(str) - 1)
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	make_echo(char **cmds)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	while (cmds[i] && check_flags(cmds[i]))
	{
		check = 1;
		i++;
	}
	while (cmds[i])
	{
		if (!cmds[i] && cmds[i + 1])
			i++;
		if (ft_strncmp(cmds[i], "&&", ft_strlen(cmds[i])))
			ft_putstr_fd(cmds[i], 1);
		if (cmds[i][0] && cmds[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (check == 0)
		ft_putchar_fd('\n', 1);
}
