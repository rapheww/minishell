/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 20:49:05 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/16 23:29:47 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (cmd[0] == '$')
		return (1);
	if (!strcmp(cmd, "echo") && ft_strlen(cmd) == 4)
		return (1);
	else if (!strcmp(cmd, "cd") && ft_strlen(cmd) == 2)
		return (1);
	else if (!strcmp(cmd, "pwd") && ft_strlen(cmd) == 3)
		return (1);
	else if (!strcmp(cmd, "export") && ft_strlen(cmd) == 6)
		return (1);
	else if (!strcmp(cmd, "unset") && ft_strlen(cmd) == 5)
		return (1);
	else if (!strcmp(cmd, "env") && ft_strlen(cmd) == 3)
		return (1);
	else if (!strcmp(cmd, "exit") && ft_strlen(cmd) == 4)
		return (1);
	return (0);
}

static char	*env_line(t_env *node)
{
	char	*line;
	int		len;

	if (node->value)
	{
		len = ft_strlen(node->key) + 1 + ft_strlen(node->value) + 1;
		line = malloc(sizeof(char) * len);
		if (!line)
			return (NULL);
		ft_strlcpy(line, node->key, len);
		ft_strlcat(line, "=", len);
		ft_strlcat(line, node->value, len);
	}
	else
		line = ft_strdup(node->key);
	return (line);
}

char	**dup_env(t_env *env, char *str)
{
	int		i;
	char	**new_env;
	t_env	*tmp;
	char	*line;

	new_env = malloc(sizeof(char *) * (env_getsize(env) + 1));
	if (!new_env)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (!str || ft_strncmp(tmp->key, str, ft_strlen(str)))
		{
			line = env_line(tmp);
			if (!line)
				return (NULL);
			new_env[i++] = line;
		}
		tmp = tmp->next;
	}
	new_env[i] = NULL;
	return (new_env);
}
