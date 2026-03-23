/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 14:07:57 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/20 00:13:22 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_getsize(t_env *env)
{
	int		n;
	t_env	*tmp;

	n = 0;
	tmp = env;
	while (tmp)
	{
		n++;
		tmp = tmp->next;
	}
	return (n);
}

t_env	*env_new(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

int	env_addback(t_env **env, t_env *new)
{
	t_env	*last;

	if (!new)
		return (1);
	if (!*env)
	{
		*env = new;
		return (0);
	}
	last = *env;
	while (last->next)
		last = last->next;
	last->next = new;
	return (0);
}

static int	split_envp(char *str, char **key, char **value)
{
	char	*mid;

	if (!str)
		return (1);
	mid = ft_strchr(str, '=');
	if (!mid)
	{
		*key = ft_strdup(str);
		if (!*key)
			return (1);
		*value = NULL;
		return (0);
	}
	*key = ft_substr(str, 0, mid - str);
	if (!*key)
		return (1);
	*value = ft_strdup(mid + 1);
	if (!*value)
		return (free_strs(*key, NULL), 1);
	return (0);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	char	*key;
	char	*value;

	env = NULL;
	while (*envp)
	{
		if (split_envp(*envp, &key, &value) != 0)
			return (NULL);
		if (env_addback(&env, env_new(key, value)) != 0)
			return (free_env(env), NULL);
		envp++;
	}
	return (env);
}
