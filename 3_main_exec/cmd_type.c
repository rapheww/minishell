/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 22:54:04 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/24 22:54:39 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_env(char **env)
{
	char	**path;

	if (!env)
		return (NULL);
	while (*env)
	{
		if (ft_strncmp(*env, "PATH", 4) == 0)
			break ;
		env++;
	}
	if (*env)
	{
		path = ft_split(*env + 5, ':');
		if (!path)
			return (free_strs(NULL, path), NULL);
	}
	else
		path = NULL;
	return (path);
}

static char	*get_cmd_path(char **cmd, char **path)
{
	char	*command;
	char	*tmp;
	int		i;

	i = 0;
	if (access(cmd[0], X_OK) == 0)
		return (cmd[0]);
	while (path[i])
	{
		command = ft_strjoin(path[i], "/");
		if (!command)
			return (NULL);
		tmp = ft_strjoin(command, cmd[0]);
		free(command);
		if (!tmp)
			return (NULL);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

static void	handle_cmd_error(char *cmd_name, char **path, char **envp,
		t_shell *shell)
{
	free_strs(NULL, path);
	free_strs(NULL, envp);
	if (cmd_name[0] == '.' && cmd_name[1] == '/')
		exit_error_full(msg(cmd_name, ": Permission denied\n", 126), shell);
	else
		exit_error_full(msg(cmd_name, ": command not found\n", 127), shell);
}

static void	execute_cmd(char *cmd_path, char **cmd, char **envp, t_shell *shell)
{
	execve(cmd_path, cmd, envp);
	free_strs(cmd_path, NULL);
	free_strs(NULL, envp);
	exit_error_full(1, shell);
}

void	make_bin(char **cmd, t_env *env, t_shell *shell)
{
	char	*cmd_path;
	char	**path;
	char	**envp;

	envp = dup_env(env, NULL);
	if (!envp)
		return ;
	path = get_env(envp);
	if (!path && access(cmd[0], X_OK) != 0)
	{
		free_strs(NULL, path);
		free_strs(NULL, envp);
		exit_error_full(msg(cmd[0], ": No such file or directory\n", 127),
			shell);
	}
	cmd_path = get_cmd_path(cmd, path);
	if (!cmd_path)
		handle_cmd_error(cmd[0], path, envp, shell);
	execute_cmd(cmd_path, cmd, envp, shell);
}
