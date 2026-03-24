/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapheww <rapheww@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 23:53:26 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/24 13:33:49 by rapheww          ###   ########.fr       */
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

void	loop_heredoc(int fd_in, int fd_tmp, t_cmds *cmds)
{
	char	*line;

	line = NULL;
	while (1)
	{
		ft_putstr_fd("heredoc > ", 1);
		line = get_next_line(fd_in);
		if (!line)
		{
			if (errno == EINTR)
				return ;
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
	int					fd_tmp;
	struct sigaction	sa;
	struct sigaction	old_sa;

	fd_tmp = 0;
	sa.sa_handler = heredoc_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, &old_sa);
	if (cmds->heredoc == 2)
	{
		fd_tmp = open("infile.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_tmp == -1)
			exit_error(msg("Error: ", strerror(errno), 1), s);
		loop_heredoc(STDIN_FILENO, fd_tmp, cmds);
	}
	else
		loop_heredoc_empty(STDIN_FILENO, cmds);
	close(fd_tmp);
}
