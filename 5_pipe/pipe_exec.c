/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:20:02 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/23 17:26:38 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child_subproc(t_cmds *cmds, t_data *d, int prev_fd)
{
	if (cmds->infile || cmds->heredoc)
	{
		dup2(d->fd_in, STDIN_FILENO);
		close(d->fd_in);
	}
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmds->outfile)
	{
		dup2(d->fd_out, STDOUT_FILENO);
		close(d->fd_out);
	}
	else if (cmds->next)
	{
		close(d->pipe[0]);
		dup2(d->pipe[1], STDOUT_FILENO);
		close(d->pipe[1]);
	}
}

static void	child_proc(t_cmds *cmds, t_shell *s, int prev_fd)
{
	int		built;
	char	**envp;
	char	*path;

	child_subproc(cmds, s->data, prev_fd);
	if (!cmds->cmds || !cmds->cmds[0])
		exit_error_full(0, s);
	built = make_built_in(cmds, s->data, s->env);
	if (!built)
		exit_error_full(0, s);
	envp = dup_env(s->env, NULL);
	if (!envp)
		exit_error_full(1, s);
	path = get_cmd(cmds->cmds[0], s);
	if (!path)
		exit_error_full(msg(cmds->cmds[0], ": command not found\n", 127), s);
	execve(path, cmds->cmds, envp);
	free_strs(path, envp);
	exit_error_full(1, s);
}

static int	parent_proc(t_data *d, int last_pid)
{
	int	status;
	int	exit_status;

	exit_status = 0;
	d->pid = wait(&status);
	while (d->pid > 0)
	{
		if (d->pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = 128 + WTERMSIG(status);
		}
		d->pid = wait(&status);
	}
	unlink("infile.tmp");
	return (exit_status);
}

static void	handle_proc(t_cmds **cmds, t_shell *s, int *prev_fd)
{
	if (s->data->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		open_infile(s->data, *cmds, s);
		open_outfile(s->data, *cmds);
		child_proc(*cmds, s, *prev_fd);
	}
	if (*prev_fd != s->data->fd_in)
		close(*prev_fd);
	if ((*cmds)->next)
	{
		close(s->data->pipe[1]);
		*prev_fd = s->data->pipe[0];
	}
	*cmds = (*cmds)->next;
}

int	pipe_main(t_cmds *cmds, t_shell *s)
{
	int	prev_fd;
	int	exit_status;
	int	last_pid;

	prev_fd = s->data->fd_in;
	while (cmds)
	{
		if (cmds->next && pipe(s->data->pipe) == -1)
			exit_error(1, s);
		s->data->pid = fork();
		last_pid = s->data->pid;
		g_signal = s->data->pid;
		if (s->data->pid == -1)
			exit_error(1, s);
		handle_proc(&cmds, s, &prev_fd);
	}
	exit_status = parent_proc(s->data, last_pid);
	return (exit_status);
}
