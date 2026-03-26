/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:11:21 by rchaumei          #+#    #+#             */
/*   Updated: 2026/03/26 19:53:34 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	first_is_directory(char *path)
{
	struct stat	st;

	if (!path)
		return (0);
	if (stat(path, &st) == -1)
		return (0);
	if (S_ISDIR(st.st_mode))
		return (msg(path, ": Is a directory\n", 2), 1);
	return (0);
}

void	redirect_exec_utils(t_shell *s)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	redirect_cmd(s->data);
	make_bin(s->data->cmds->cmds, s->env, s);
}

int	start_cmds(t_shell *shell)
{
	int	exit_code;

	if (shell->heredoc_int)
	{
		free_between_lines(shell);
		return (1);
	}
	if (shell->lexer)
		shell->env->exit_code = launch_cmds(shell);
	if (shell->data->check_exit == 1)
	{
		exit_code = shell->env->exit_code;
		free_shell(shell);
		exit(exit_code % 256);
	}
	return (0);
}
