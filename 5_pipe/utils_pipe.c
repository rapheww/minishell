/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:33:07 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/30 19:08:02 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_error(int error_status, t_shell *shell)
{
	unlink("infile.tmp");
	free_shell_no_env(shell);
	exit(error_status);
}

void	exit_error_full(int error_status, t_shell *shell)
{
	free_shell(shell);
	exit(error_status);
}

int	msg(char *str1, char *str2, int erno)
{
	char	*test;

	test = ft_strjoin(str1, str2);
	write(2, test, ft_strlen(test));
	free(test);
	return (erno);
}

int	msg3(char *str1, char *str2, char *str3, int erno)
{
	char	*test;
	char	*test2;

	test = ft_strjoin(str1, str2);
	test2 = ft_strjoin(test, str3);
	write(2, test2, ft_strlen(test2));
	free(test);
	free(test2);
	return (erno);
}

void	check_ending(t_cmds *cmds, t_shell *s)
{
	if (errno == EINTR)
	{
		s->heredoc_int = 1;
		return ;
	}
	ft_putstr_fd(HEREDOC, 2);
	msg(cmds->limiter, "')\n", 2);
	return ;
}
