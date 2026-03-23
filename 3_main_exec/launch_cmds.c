/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 13:09:49 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/23 17:57:17 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	make_built_in(t_cmds *cmds, t_data *data, t_env *env)
{
	char	**str;

	str = cmds->cmds;
	if (!ft_strncmp(str[0], "unset", 5) && ft_strlen(str[0]) == 5)
		return (make_unset(&env, str));
	if (!ft_strncmp(str[0], "pwd", 3) && ft_strlen(str[0]) == 3)
		return (make_pwd());
	if (!ft_strncmp(str[0], "exit", 4) && ft_strlen(str[0]) == 4)
		return (make_exit(cmds->cmds, &data));
	if (str[0][0] == '$')
		return (ft_putstr_fd(str[0], 1),
			ft_putstr_fd(": command not found\n", 1), 127);
	if (!ft_strncmp(str[0], "echo", 4))
		return (make_echo(cmds->cmds), 0);
	if (!ft_strncmp(str[0], "export", 6) && ft_strlen(str[0]) == 6)
	{
		if (str[1])
			return (make_export_var(&env, str));
		return (make_export(env));
	}
	if (!ft_strncmp(str[0], "env", 3) && ft_strlen(str[0]) == 3)
		return (make_env(env), 0);
	if (!ft_strncmp(str[0], "cd", 2) && ft_strlen(str[0]) == 2)
		return (make_cd(env, str));
	return (1);
}

static int	check_infile(int fd, t_data *data)
{
	if (data->cmds->heredoc == 2)
	{
		fd = open("infile.tmp", O_RDONLY);
		if (fd == -1)
			return (1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (data->cmds->infile)
	{
		fd = open(data->cmds->infile, O_RDONLY);
		if (fd == -1)
			return (1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

static int	redirect_cmd(t_data *data)
{
	int	fd;

	fd = 0;
	if (check_infile(fd, data))
		return (1);
	if (data->cmds->outfile)
	{
		if (data->cmds->append)
			fd = open(data->cmds->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(data->cmds->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			return (1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

static int	redirect_exec(t_shell *s)
{
	pid_t	pid;
	int		exit_code;
	int		status;

	pid = fork();
	exit_code = 0;
	g_signal = pid;
	if (pid == -1)
		exit_error(1, s);
	if (pid == 0)
	{
		redirect_cmd(s->data);
		make_bin(s->data->cmds->cmds, s->env, s);
	}
	wait(&status);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_code = 128 + WTERMSIG(status);
	unlink("infile.tmp");
	return (exit_code);
}

int	launch_cmds(t_shell *s)
{
	int	exit_code;

	if (!s->data->cmds)
		return (0);
	if (s->data->flag == 1)
		return (pipe_main(s->data->cmds, s));
	if (is_builtin(s->data->cmds->cmds[0]))
	{
		s->data->fd_in = dup(STDIN_FILENO);
		s->data->fd_out = dup(STDOUT_FILENO);
		if (redirect_cmd(s->data))
			return (1);
		exit_code = make_built_in(s->data->cmds, s->data, s->env);
		dup2(s->data->fd_in, STDIN_FILENO);
		dup2(s->data->fd_out, STDOUT_FILENO);
		close(s->data->fd_in);
		close(s->data->fd_out);
		return (exit_code);
	}
	return (redirect_exec(s));
}
