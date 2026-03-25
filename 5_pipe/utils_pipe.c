/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:33:07 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/25 00:09:58 by lchambos         ###   ########.fr       */
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
	unlink("infile.tmp");
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

// static void heredoc_handler(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	exit(130);
// }

// void	heredoc_signal_handler(void)
// {
// 	struct sigaction	sa;

// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_handler = heredoc_handler;
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGTSTP, SIG_IGN);
// }
