/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:26:52 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/26 15:29:51 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_strs(char *str, char **strs)
{
	int	i;

	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	if (strs != NULL)
	{
		i = 0;
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
		strs = NULL;
	}
}

void	free_lexer_null(t_token **lexer)
{
	t_token	*tmp;

	if (!lexer || !*lexer)
		return ;
	while (*lexer)
	{
		tmp = (*lexer)->next;
		if ((*lexer)->value)
			free((*lexer)->value);
		if ((*lexer)->value_quotes)
			free((*lexer)->value_quotes);
		if ((*lexer)->first_quotes)
			free((*lexer)->first_quotes);
		free(*lexer);
		*lexer = tmp;
	}
	*lexer = NULL;
}

void	free_shell_no_env(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->data)
	{
		if (shell->data->cmds)
			free_cmds(shell->data->cmds);
		free(shell->data);
		shell->data = NULL;
	}
	if (shell->lexer)
	{
		free_lexer(shell->lexer);
		shell->lexer = NULL;
	}
	free(shell);
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->data)
	{
		if (shell->data->cmds)
			free_cmds(shell->data->cmds);
		free(shell->data);
		shell->data = NULL;
	}
	if (shell->lexer)
	{
		free_lexer(shell->lexer);
		shell->lexer = NULL;
	}
	if (shell->env)
	{
		free_env(shell->env);
		shell->env = NULL;
	}
	free(shell);
}
