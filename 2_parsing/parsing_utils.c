/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:31:18 by rchaumei          #+#    #+#             */
/*   Updated: 2026/03/25 00:45:11 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	define_heredoc(t_cmds **tmp_cmds, t_token **tmp, t_shell **shell)
{
	(*tmp) = (*tmp)->next;
	if (!(*tmp))
		return (1);
	(*tmp_cmds)->limiter = ft_strdup((*tmp)->value);
	if (!(*tmp_cmds)->limiter)
		return (1);
	(*tmp_cmds)->heredoc = 2;
	open_heredoc(*tmp_cmds, *shell);
	if ((*shell)->heredoc_int)
		return (1);
	(*tmp) = (*tmp)->next;
	return (0);
}

int	check_flag(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	change_state(int *state, char **cmds_quotes, int *i, int j)
{
	while (cmds_quotes[j][*i])
	{
		if (cmds_quotes[j][*i] == '\'' && *state == 0)
			*state = 1;
		else if (cmds_quotes[j][*i] == '"' && *state == 0)
			*state = 2;
		else if (cmds_quotes[j][*i] == '\'' && *state == 1)
			*state = 0;
		else if (cmds_quotes[j][*i] == '"' && *state == 2)
			*state = 0;
		else
			break ;
		(*i)++;
	}
}

char	*strjoin_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
		return (NULL);
	free(s1);
	return (res);
}

char	*append_char(char *res, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (strjoin_free(res, tmp));
}
