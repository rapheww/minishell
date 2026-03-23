/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:57:39 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/23 13:30:53 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_lexer(t_token *lexer)
{
	t_token	*tmp;

	tmp = lexer;
	while (lexer)
	{
		tmp = lexer->next;
		if (lexer->value)
			free(lexer->value);
		if (lexer->value_quotes)
			free(lexer->value_quotes);
		if (lexer->first_quotes)
			free(lexer->first_quotes);
		free(lexer);
		lexer = tmp;
	}
}

void	free_cmds_plus(t_cmds *cmds)
{
	if (cmds->infile)
		free(cmds->infile);
	if (cmds->outfile)
		free(cmds->outfile);
	if (cmds->limiter)
		free(cmds->limiter);
}

void	free_cmds(t_cmds *cmds)
{
	t_cmds	*tmp;
	int		i;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->cmds)
		{
			i = 0;
			while (cmds->cmds[i])
				free(cmds->cmds[i++]);
			free(cmds->cmds);
		}
		if (cmds->cmds_quotes)
		{
			i = 0;
			while (cmds->cmds_quotes[i])
				free(cmds->cmds_quotes[i++]);
			free(cmds->cmds_quotes);
		}
		free_cmds_plus(cmds);
		free(cmds);
		cmds = tmp;
	}
}

void	free_between_lines(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->lexer)
	{
		free_lexer(shell->lexer);
		shell->lexer = NULL;
	}
	if (shell->data)
	{
		if (shell->data->cmds)
			free_cmds(shell->data->cmds);
		free(shell->data);
		shell->data = NULL;
	}
	unlink("infile.tmp");
}
