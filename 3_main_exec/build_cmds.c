/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:59:08 by rchaumei          #+#    #+#             */
/*   Updated: 2026/03/19 23:55:18 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**build_cmd(t_token *token)
{
	int		count;
	t_token	*tmp;
	char	**cmd;
	int		i;

	count = 0;
	tmp = token;
	while (tmp && tmp->type == TOKEN_WORD)
	{
		count++;
		tmp = tmp->next;
	}
	cmd = malloc(sizeof(char *) * (count + 1));
	if (!cmd)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		cmd[i] = ft_strdup(token->value);
		if (!cmd[i])
			return (free_strs(NULL, cmd), NULL);
		token = token->next;
	}
	cmd[count] = NULL;
	return (cmd);
}

char	**build_cmd_quotes(t_token *token)
{
	int		count;
	t_token	*tmp;
	char	**cmd;
	int		i;

	count = 0;
	tmp = token;
	while (tmp && tmp->type == TOKEN_WORD)
	{
		count++;
		tmp = tmp->next;
	}
	cmd = malloc(sizeof(char *) * (count + 1));
	if (!cmd)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		cmd[i] = ft_strdup(token->value_quotes);
		if (!cmd[i])
			return (free_strs(NULL, cmd), NULL);
		token = token->next;
	}
	cmd[count] = NULL;
	return (cmd);
}
