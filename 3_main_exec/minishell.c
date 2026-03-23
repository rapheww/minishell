/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 19:57:09 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/23 18:19:21 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t		g_signal;

void	handler(int num)
{
	printf("\n");
	(void)num;
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_signal == 0)
		rl_redisplay();
	return ;
}

static void	start_minishell(char *str, t_shell *shell)
{
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
	{
		if (shell->lexer)
			return (free_lexer_null(&shell->lexer));
	}
	expand(&shell->data->cmds, shell->env, shell->data);
	if (shell->lexer)
		shell->env->exit_code = launch_cmds(shell);
	if (shell->data->check_exit == 1)
	{
		free_shell(shell);
		exit(0);
	}
	free_between_lines(shell);
}

void	minishell(t_shell *shell)
{
	char	*line_read;

	line_read = NULL;
	while (1)
	{
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
	return (shell);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	(void)av;
	g_signal = 0;
	if (ac != 1)
		return (ft_putstr_fd(USAGE, 2), 1);
	shell = init_shell(envp);
	shell->env->exit_code = 0;
	minishell(shell);
	rl_clear_history();
	free_shell(shell);
	return (0);
}
