/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:51:01 by rchaumei          #+#    #+#             */
/*   Updated: 2026/03/23 17:57:49 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	define_infile(t_cmds **tmp_cmds, t_token **tmp, t_shell **shell)
{
	if (!tmp || !(*tmp))
		return (0);
	if ((*tmp)->type == TOKEN_REDIR_IN)
	{
		(*tmp) = (*tmp)->next;
		if (!(*tmp))
			return (1);
		if (access((*tmp)->value, R_OK) != 0)
			return (printf("%s: No such file or directory\n", (*tmp)->value),
				1);
		if ((*tmp_cmds)->infile)
			free((*tmp_cmds)->infile);
		(*tmp_cmds)->infile = ft_strdup((*tmp)->value);
		if (!(*tmp_cmds)->infile)
			return (1);
		if ((*tmp_cmds)->heredoc == 2)
			(*tmp_cmds)->heredoc = 1;
		(*tmp) = (*tmp)->next;
	}
	else if ((*tmp)->type == TOKEN_HEREDOC)
		if (define_heredoc(tmp_cmds, tmp, shell))
			return (1);
	return (0);
}

static int	define_outfile(t_cmds **tmp_cmds, t_token **tmp, t_data *data)
{
	(*tmp) = (*tmp)->next;
	if (!(*tmp))
		return (1);
	data->fd_out = open((*tmp)->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_out == -1)
		return (printf("%s: No such file or directory\n", (*tmp)->value), 1);
	close(data->fd_out);
	if ((*tmp_cmds)->outfile)
		free((*tmp_cmds)->outfile);
	(*tmp_cmds)->outfile = ft_strdup((*tmp)->value);
	if (!(*tmp_cmds)->outfile)
		return (1);
	(*tmp_cmds)->append = 0;
	(*tmp) = (*tmp)->next;
	return (0);
}

static int	define_append(t_cmds **tmp_cmds, t_token **tmp, t_data *data)
{
	(*tmp) = (*tmp)->next;
	if (!(*tmp))
		return (1);
	data->fd_out = open((*tmp)->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->fd_out == -1)
		return (printf("%s: No such file or directory\n", (*tmp)->value), 1);
	close(data->fd_out);
	if ((*tmp_cmds)->outfile)
		free((*tmp_cmds)->outfile);
	(*tmp_cmds)->outfile = ft_strdup((*tmp)->value);
	if (!(*tmp_cmds)->outfile)
		return (1);
	(*tmp_cmds)->append = 1;
	(*tmp) = (*tmp)->next;
	return (0);
}

static int	define_word_outfile(t_cmds **tmp_cmds, t_token **tmp, t_data *data)
{
	if ((*tmp) && (*tmp)->type == TOKEN_WORD)
	{
		(*tmp_cmds)->cmds = build_cmd((*tmp));
		(*tmp_cmds)->cmds_quotes = build_cmd_quotes((*tmp));
		(*tmp_cmds)->next = NULL;
		while ((*tmp) && (*tmp)->type == TOKEN_WORD)
			(*tmp) = (*tmp)->next;
	}
	else if ((*tmp) && (*tmp)->type == TOKEN_REDIR_OUT)
	{
		if (define_outfile(tmp_cmds, tmp, data))
			return (1);
	}
	else if ((*tmp) && (*tmp)->type == TOKEN_APPEND)
	{
		if (define_append(tmp_cmds, tmp, data))
			return (1);
	}
	return (0);
}

int	define_cmd(t_cmds **tmp_cmds, t_token **tmp, t_data *data, t_shell **shell)
{
	if ((*tmp) && ((*tmp)->type == TOKEN_REDIR_IN
			|| (*tmp)->type == TOKEN_HEREDOC))
	{
		if (define_infile(tmp_cmds, tmp, shell))
		{
			(*shell)->env->exit_code = 1;
			return (1);
		}
	}
	else if ((*tmp) && ((*tmp)->type == TOKEN_WORD
			|| (*tmp)->type == TOKEN_REDIR_OUT || (*tmp)->type == TOKEN_APPEND))
	{
		if (define_word_outfile(tmp_cmds, tmp, data))
			return (1);
	}
	return (0);
}
