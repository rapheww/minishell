/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:06:38 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/22 18:09:17 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	env_set_var(t_env **env, char *key, char *value, int append)
{
	t_env	*tmp;
	char	*kdup;
	char	*vdup;

	tmp = find_env(*env, key);
	if (tmp && append == 2)
		return (0);
	if (tmp)
		return (env_update_existing(tmp, value, append));
	kdup = ft_strdup(key);
	if (!kdup)
		return (1);
	if (value)
	{
		vdup = ft_strdup(value);
		if (!vdup)
			return (free(kdup), 1);
	}
	else
		vdup = NULL;
	return (env_addback(env, env_new(kdup, vdup)));
}

static int	assign_key_value(char *arg, char *eq, char **key, char **value)
{
	*key = ft_substr(arg, 0, eq - arg);
	if (!*key)
		return (1);
	*value = ft_strdup(eq + 1);
	if (!*value)
		return (free(*key), 1);
	return (0);
}

static int	assign_key_value_append(char *arg, char *eq, char **key,
		char **value)
{
	*key = ft_substr(arg, 0, eq - arg - 1);
	if (!*key)
		return (1);
	*value = ft_strdup(eq + 1);
	if (!*value)
		return (free(*key), 1);
	return (0);
}

static int	parse_export_arg(char *arg, char **key, char **value, int *append)
{
	char	*eq;

	*key = NULL;
	*value = NULL;
	*append = 0;
	eq = ft_strchr(arg, '=');
	if (eq && eq != arg && *(eq - 1) == '+')
		return ((*append = 1), assign_key_value_append(arg, eq, key, value));
	if (eq)
		return (assign_key_value(arg, eq, key, value));
	*append = 2;
	*key = ft_strdup(arg);
	if (!*key)
		return (1);
	return (0);
}

int	make_export_var(t_env **env, char **args)
{
	int		i;
	char	*key;
	char	*value;
	int		append;

	i = 1;
	while (args[i])
	{
		if (parse_export_arg(args[i], &key, &value, &append) == 1)
			return (1);
		if (!is_valid_word(key))
			ft_putstr_fd("export: not a valid identifier\n", 2);
		else
		{
			if (env_set_var(env, key, value, append) == 1)
				return (1);
		}
		if (key)
			free(key);
		if (value)
			free(value);
		i++;
	}
	return (0);
}
