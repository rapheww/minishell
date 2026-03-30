/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 23:51:05 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/09 13:19:40 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_exec(char *cmd, t_env *env)
{
	char	*full;
	char	**paths;

	if (!cmd || !*cmd || !env)
		return (NULL);
	while (env && ft_strncmp(env->key, "PATH", 5) != 0)
		env = env->next;
	if (!env)
		return (NULL);
	paths = ft_split(env->value, ':');
	if (!paths)
		return (NULL);
	full = get_path(cmd, paths);
	if (!full)
	{
		free_strs(NULL, paths);
		return (NULL);
	}
	return (full);
}

static char	*get_path(char *cmd, char **paths)
{
	char	*full;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		full = ft_strjoin(paths[i], "/");
		if (!full)
			break ;
		tmp = ft_strjoin(full, cmd);
		free(full);
		full = tmp;
		if (full && access(full, X_OK) == 0)
		{
			free_strs(NULL, paths);
			return (full);
		}
		free(full);
		i++;
	}
	return (0);
}

char	*get_cmd(char *cmd, t_shell *s)
{
	char	**cmd1;
	char	*cmd_path;

	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			exit_error_full(msg("Permission denied: ", strerror(errno), 126),
				s);
	}
	cmd1 = ft_split(cmd, ' ');
	if (!cmd1 || !cmd1[0])
	{
		free_strs(NULL, cmd1);
		exit_error_full(0, s);
	}
	cmd_path = get_exec(cmd1[0], s->env);
	free_strs(NULL, cmd1);
	return (cmd_path);
}
