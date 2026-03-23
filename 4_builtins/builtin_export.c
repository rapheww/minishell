/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 21:24:46 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/22 18:09:23 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_word(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	env_update_existing(t_env *tmp, char *value, int append)
{
	char	*new_val;

	new_val = NULL;
	if (append == 1)
	{
		if (tmp->value)
			new_val = ft_strjoin(tmp->value, value);
		else if (value)
			new_val = ft_strdup(value);
	}
	else if (value)
		new_val = ft_strdup(value);
	if (value && !new_val)
		return (1);
	free(tmp->value);
	tmp->value = new_val;
	return (0);
}

t_env	*find_env(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	swap_env(char **new_env, int i)
{
	int		j;
	char	*tmp;

	j = -1;
	while (new_env[++j])
	{
		if (ft_strcmp(new_env[i], new_env[j]) < 0)
		{
			tmp = new_env[i];
			new_env[i] = new_env[j];
			new_env[j] = tmp;
		}
	}
}

int	make_export(t_env *env)
{
	char	**new_env;
	char	*var;
	int		i;

	i = 0;
	new_env = dup_env(env, NULL);
	if (!new_env)
		return (1);
	while (new_env[++i])
		swap_env(new_env, i);
	i = -1;
	while (new_env[++i])
	{
		var = ft_strchr(new_env[i], '=');
		if (var)
			printf("export %.*s=\"%s\"\n", (int)(var - new_env[i]), new_env[i],
				var + 1);
		else
			printf("export %s\n", new_env[i]);
	}
	free_strs(NULL, new_env);
	return (0);
}
