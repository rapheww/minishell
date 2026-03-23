/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:06:27 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/18 16:09:43 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_space_tab(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
}

void	change_tmp(char **tmp, int state)
{
	if (state == 1 && *tmp == NULL)
		*tmp = ft_strdup("'");
	else if (state == 2 && *tmp == NULL)
		*tmp = ft_strdup("\"");
}

char	*init_read(int *j, int *state, char **tmp, char *str)
{
	char	*buffer;

	*j = 0;
	*state = 0;
	*tmp = NULL;
	buffer = malloc(sizeof(char) * (ft_strlen(str) + 1));
	return (buffer);
}
