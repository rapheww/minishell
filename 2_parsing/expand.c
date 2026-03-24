/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapheww <rapheww@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:49:08 by rchaumei          #+#    #+#             */
/*   Updated: 2026/03/24 14:27:19 by rapheww          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_echo(int *j, int *check, int *state, char **cmds_quotes)
{
	*j = 1;
	*check = 0;
	*state = 0;
	while (cmds_quotes[*j] && ft_strlen(cmds_quotes[*j]) > 1
		&& check_flag(cmds_quotes[*j]))
	{
		(*j)++;
		*check = 1;
	}
	return (0);
}

void	echo_env_var(t_expand *exp, char *cmds_quotes, t_env *env,
		t_data **data)
{
	if (cmds_quotes[exp->i] == '$')
	{
		if ((*data)->state == 1)
			exp->result = append_char(exp->result, cmds_quotes[exp->i]);
		else
		{
			(*data)->index = exp->i;
			(exp->i) += make_env_variables(cmds_quotes, *data, env,
					&exp->result);
		}
	}
	else
		exp->result = append_char(exp->result, cmds_quotes[exp->i]);
	(exp->i)++;
}

void	expand_str(t_cmds **cmds, t_expand *exp, t_env *env, t_data **data)
{
	while ((*cmds)->cmds_quotes[exp->j][exp->i])
	{
		if (exp->i == 0 && (*cmds)->cmds[exp->j]
			&& (*cmds)->cmds_quotes[exp->j][exp->i] == '$'
			&& ft_strlen((*cmds)->cmds_quotes[exp->j]) == 3)
		{
			exp->result = strjoin_free(exp->result, "&&");
			break ;
		}
		if (exp->i == 0 && (*cmds)->cmds[exp->j]
			&& ft_strlen((*cmds)->cmds[exp->j]) == 1)
		{
			exp->result = append_char(exp->result,
					(*cmds)->cmds[exp->j][exp->i]);
			break ;
		}
		if ((*cmds)->cmds_quotes[exp->j][exp->i] == '\''
			|| (*cmds)->cmds_quotes[exp->j][exp->i] == '"')
			change_state(&(*data)->state, (*cmds)->cmds_quotes, &exp->i,
				exp->j);
		if ((*cmds)->cmds_quotes[exp->j][exp->i] == '\0')
			break ;
		echo_env_var(exp, (*cmds)->cmds_quotes[exp->j], env, data);
	}
}

void	expand(t_cmds **cmds, t_env *env, t_data *data)
{
	t_expand	exp;

	exp.first = *cmds;
	while (*cmds)
	{
		if (!(*cmds)->cmds_quotes)
			*cmds = (*cmds)->next;
		else
		{
			init_echo(&exp.j, &exp.check, &data->state, (*cmds)->cmds_quotes);
			while ((*cmds)->cmds_quotes[exp.j])
			{
				exp.result = ft_strdup("");
				exp.i = 0;
				expand_str(cmds, &exp, env, &data);
				free((*cmds)->cmds[exp.j]);
				(*cmds)->cmds[exp.j] = ft_strdup(exp.result);
				free(exp.result);
				exp.j++;
			}
			*cmds = (*cmds)->next;
		}
	}
	*cmds = exp.first;
}
