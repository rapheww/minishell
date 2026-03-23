/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 21:30:48 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/23 19:18:46 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_env_variables(t_data *data, char *str, char *quotes)
{
	int	i;
	int	j;

	(void)quotes;
	i = data->index;
	if (str[i] == '$')
		i++;
	j = i;
	if (str[j] == '?')
		j++;
	else
	{
		while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
			j++;
	}
	return (ft_substr(str, i, j - i));
}

static char	*init_env_var(int *j, char *tmp, char quotes)
{
	char	*key_search;

	if (!quotes)
	{
		while (tmp[*j] && tmp[*j] != '\'' && tmp[*j] != '"')
			(*j)++;
	}
	else
	{
		while (tmp[*j] && tmp[*j] != quotes)
			(*j)++;
	}
	key_search = ft_substr(tmp, 0, *j);
	return (key_search);
}

static char	*env_var(char *tmp, t_env *env, char quotes)
{
	int		j;
	char	*key_search;
	t_env	*alt;

	j = 0;
	alt = env;
	if (!alt)
		return (NULL);
	key_search = init_env_var(&j, tmp, quotes);
	if (!key_search)
		return (NULL);
	while (alt)
	{
		if (ft_strcmp(alt->key, key_search) == 0)
			break ;
		alt = alt->next;
	}
	free(key_search);
	if (alt)
		return (alt->value);
	else
		return (NULL);
}

static void	define_quotes(char *quotes, char *oldquotes, int *len, t_data *data)
{
	*len = 0;
	if (data->state == 1)
		*quotes = '\'';
	else if (data->state == 2)
		*quotes = '"';
	else
		*quotes = '\0';
	*oldquotes = *quotes;
}

int	make_env_variables(char *str, t_data *data, t_env *env, char **result)
{
	t_env_var	var;

	define_quotes(&var.quotes, &var.oldquote, &var.len, data);
	var.tmp = get_env_variables(data, str, &var.quotes);
	if (!var.tmp)
		return (0);
	if (var.tmp[0] && var.tmp[0] == '?')
	{
		var.variable = ft_itoa(env->exit_code);
		var.len = 1;
		if (var.tmp[var.len] && var.oldquote
			&& var.tmp[var.len] == var.oldquote)
			var.len++;
	}
	else
	{
		var.val = env_var(var.tmp, env, var.quotes);
		var.variable = ft_strdup(var.val);
		while (var.tmp[var.len] && (ft_isalnum(var.tmp[var.len])
				|| var.tmp[var.len] == '_'))
			var.len++;
	}
	return (return_var(result, var));
}
