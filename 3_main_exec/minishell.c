/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 19:57:09 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/26 13:29:40 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t		g_signal;

static void	start_minishell(char *str, t_shell *shell)
{
	int	exit_code;

	add_history(str);
	shell->lexer = start_lexer(str);
	if (!shell->lexer)
		return ;
	if (check_double_token(shell->lexer))
	{
		shell->env->exit_code = 2;
		return (free_lexer_null(&shell->lexer));
	}
	shell->data = parse_lexer(&shell->lexer, &shell);
	if (!shell->data)
		return (free_between_lines(shell));
	expand(&shell->data->cmds, shell->env, shell->data);
	if (shell->heredoc_int)
	{
		free_between_lines(shell);
		return ;
	}
	if (shell->lexer)
		shell->env->exit_code = launch_cmds(shell);
	if (shell->data->check_exit == 1)
	{
		exit_code = shell->env->exit_code;
		free_shell(shell);
		exit(exit_code % 256);
	}
	free_between_lines(shell);
}

void	minishell(t_shell *shell, struct termios g_termios)
{
	char	*line_read;

	line_read = NULL;
	while (1)
	{
		shell->heredoc_int = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &g_termios);
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		line_read = readline("\e[1;96mminishell$ \033[0;39m");
		if (!line_read)
		{
			printf("exit\n");
			break ;
		}
		if (line_read && *line_read)
			start_minishell(line_read, shell);
		free(line_read);
		line_read = NULL;
		g_signal = 0;
	}
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = init_env(envp);
	shell->lexer = NULL;
	shell->data = NULL;
	shell->heredoc_int = 0;
	return (shell);
}

int	main(int ac, char **av, char **envp)
{
	t_shell			*shell;
	struct termios	g_termios;

	(void)av;
	g_signal = 0;
	if (ac != 1)
		return (ft_putstr_fd(USAGE, 2), 1);
	shell = init_shell(envp);
	shell->env->exit_code = 0;
	tcgetattr(STDIN_FILENO, &g_termios);
	minishell(shell, g_termios);
	rl_clear_history();
	free_shell(shell);
	return (0);
}
