/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 23:53:26 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/26 17:21:07 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_infile(t_data *d, t_cmds *cmds, t_shell *s)
{
	if (cmds->heredoc == 2)
	{
		d->fd_in = open("infile.tmp", O_RDONLY);
		if (d->fd_in == -1)
			exit_error_full(msg("heredoc: ", strerror(errno), 1), s);
	}
	else if (cmds->infile)
	{
		d->fd_in = open(cmds->infile, O_RDONLY, 0644);
		if (d->fd_in == -1)
			msg(strerror(errno), ": ", 1);
	}
	else
		d->fd_in = STDIN_FILENO;
}

void	open_outfile(t_data *d, t_cmds *cmds)
{
	if (cmds->append == 1)
		d->fd_out = open(cmds->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (cmds->outfile)
		d->fd_out = open(cmds->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		d->fd_out = STDOUT_FILENO;
}

// static void	loop_heredoc_empty(t_cmds *cmds)
// {
// 	char	*line;

// 	line = NULL;
// 	while (1)
// 	{
// 		line = readline("heredoc > ");
// 		if (!line)
// 			break ;
// 		if (ft_strcmp(line, cmds->limiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		free(line);
// 	}
// }

// static void	loop_heredoc(int fd_in, int fd_tmp, t_cmds *cmds, t_shell *s)
// {
// 	char	*line;

// 	(void)fd_in;
// 	line = NULL;
// 	while (1)
// 	{
// 		line = readline("heredoc > ");
// 		if (!line)
// 		{
// 			ft_putstr_fd(HEREDOC, 2);
// 			close(fd_tmp);
// 			exit_error_full(msg(cmds->limiter, "')\n", 2), s);
// 			break ;
// 		}
// 		if (ft_strcmp(line, cmds->limiter) == 0)
// 		{
// 			free(line);
// 			close(fd_tmp);
// 			exit_error_full(0, s);
// 			break ;
// 		}
// 		write(fd_tmp, line, ft_strlen(line));
// 		write(fd_tmp, "\n", 1);
// 		free(line);
// 	}
// }

// void	open_heredoc(t_cmds *cmds, t_shell *s)
// {
// 	int		fd_tmp;
// 	pid_t	pid;
// 	int		status;

// 	fd_tmp = open("infile.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd_tmp == -1)
// 		exit_error(msg("Error: ", strerror(errno), 1), s);
// 	signal(SIGINT, SIG_IGN);
// 	pid = fork();
// 	if (pid == -1)
// 		exit_error(msg("fork failed\n", "", 1), s);
// 	if (pid == 0)
// 	{
// 		heredoc_signal_handler();
// 		if (cmds->heredoc == 2)
// 			loop_heredoc(STDIN_FILENO, fd_tmp, cmds, s);
// 		else
// 			loop_heredoc_empty(cmds);
// 		close(fd_tmp);
// 		exit(0);
// 	}
// 	close(fd_tmp);
// 	waitpid(pid, &status, 0);
// 	signal(SIGINT, handler);
// 	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
// 	{
// 		s->env->exit_code = 130;
// 		s->heredoc_int = 1;
// 		return ;
// 	}
// }

void	loop_heredoc_empty(int fd_in, t_cmds *cmds)
{
	char	*line;

	line = NULL;
	while (1)
	{
		ft_putstr_fd("heredoc > ", 1);
		line = get_next_line(fd_in);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, cmds->limiter, ft_strlen(cmds->limiter)) == 0
			&& line[ft_strlen(cmds->limiter)] == '\n')
		{
			free(line);
			break ;
		}
		free(line);
	}
}

void	loop_heredoc(int fd_in, int fd_tmp, t_cmds *cmds, t_shell *s)
{
	char	*line;

	line = NULL;
	while (1)
	{
		ft_putstr_fd("heredoc > ", 2);
		line = get_next_line(fd_in);
		if (!line)
		{
			if (errno == EINTR)
			{
				s->heredoc_int = 1;
				return ;
			}
			ft_putstr_fd("\n", 2);
			ft_putstr_fd(HEREDOC, 2);
			close(fd_tmp);
			msg(cmds->limiter, "')\n", 2);
			break ;
		}
		if (ft_strncmp(line, cmds->limiter, ft_strlen(cmds->limiter)) == 0
			&& line[ft_strlen(cmds->limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd_tmp, line, ft_strlen(line));
		free(line);
	}
}

void	open_heredoc(t_cmds *cmds, t_shell *s)
{
	int	fd_tmp;

	fd_tmp = 0;
	signal(SIGINT, SIG_IGN);
	heredoc_signal_handler();
	if (cmds->heredoc == 2)
	{
		fd_tmp = open("infile.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_tmp == -1)
			exit_error(msg("Error: ", strerror(errno), 1), s);
		loop_heredoc(STDIN_FILENO, fd_tmp, cmds, s);
	}
	else
		loop_heredoc_empty(STDIN_FILENO, cmds);
	close(fd_tmp);
	signal(SIGINT, handler);
}
