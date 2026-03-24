/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapheww <rapheww@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:41:22 by rchaumei          #+#    #+#             */
/*   Updated: 2026/03/24 13:31:07 by rapheww          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	addback_cmd(t_cmds **lst, t_cmds *new)
{
	t_cmds	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static int	count_cmd(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		if (cmds)
			i++;
		cmds = cmds->next;
	}
	return (i);
}

static int	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		return (1);
	(*data)->cmds = NULL;
	(*data)->flag = 0;
	(*data)->index = 0;
	(*data)->check_exit = 0;
	(*data)->state = 0;
	(*data)->fd_in = 0;
	(*data)->fd_out = 0;
	(*data)->nb_cmd = 0;
	return (0);
}

static int	init_tmp_cmds(t_cmds **tmp)
{
	*tmp = malloc(sizeof(t_cmds));
	if (!*tmp)
		return (1);
	(*tmp)->infile = NULL;
	(*tmp)->outfile = NULL;
	(*tmp)->append = 0;
	(*tmp)->heredoc = 0;
	(*tmp)->limiter = NULL;
	(*tmp)->cmds = NULL;
	(*tmp)->cmds_quotes = NULL;
	(*tmp)->next = NULL;
	return (0);
}

t_data	*parse_lexer(t_token **lexer, t_shell **shell)
{
	t_data	*data;
	t_token	*tmp;
	t_cmds	*tmp_cmds;

	tmp = *lexer;
	if (init_data(&data) != 0)
		return (NULL);
	while (tmp)
	{
		if (init_tmp_cmds(&tmp_cmds) != 0)
			return (free(data), NULL);
		while (tmp && tmp->type != TOKEN_PIPE)
		{
			if (define_cmd(&tmp_cmds, &tmp, data, shell))
				return (free_cmds(tmp_cmds), free_cmds(data->cmds), free(data),
					NULL);
		}
		addback_cmd(&data->cmds, tmp_cmds);
		if (tmp && tmp->type == TOKEN_PIPE)
		{
			tmp = tmp->next;
			data->flag = 1;
		}
	}
	return (data->nb_cmd = count_cmd(data->cmds), data);
}
