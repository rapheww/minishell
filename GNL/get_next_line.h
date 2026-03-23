/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:29:11 by lchambos          #+#    #+#             */
/*   Updated: 2026/02/28 15:09:52 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		ft_strlen2(const char *str);

char	*ft_strchr2(const char *s, int c);

char	*ft_strcpy2(char *dest, char *src);

char	*ft_strjoin2(char *s1, char *s2);

char	*stock_remain(char *buffer);

char	*read_lines(int fd, char *buffer);

char	*get_next_line(int fd);

#endif
