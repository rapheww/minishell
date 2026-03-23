/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:11:08 by rchaumei          #+#    #+#             */
/*   Updated: 2026/03/18 14:10:58 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_states(int state, char *buffer, char *tmp)
{
	if (state != 0)
	{
		free(buffer);
		free(tmp);
		return (-1);
	}
	return (0);
}

void	check_quotes(int state, char **tmp, int *i)
{
	if (state == 1 && *tmp == NULL)
		*tmp = ft_strdup("'");
	else if (state == 2 && *tmp == NULL)
		*tmp = ft_strdup("\"");
	(*i)++;
}

int	check_word(char *buffer, int *state, int *j, char c)
{
	if (*state == 0 && ((c == ' ' || c == '\t') || is_separator(c)))
		return (1);
	if (c == '\'' && *state == 0)
		*state = 1;
	else if (c == '\'' && *state == 1)
		*state = 0;
	else if (c == '"' && *state == 0)
		*state = 2;
	else if (c == '"' && *state == 2)
		*state = 0;
	else
		buffer[(*j)++] = c;
	return (0);
}

int	check_word_quotes(char *buffer, int *state, int *j, char c)
{
	if (*state == 0 && ((c == ' ' || c == '\t') || is_separator(c)))
		return (1);
	if (c == '\'' && *state == 0)
		*state = 1;
	else if (c == '\'' && *state == 1)
		*state = 0;
	else if (c == '"' && *state == 0)
		*state = 2;
	else if (c == '"' && *state == 2)
		*state = 0;
	buffer[(*j)++] = c;
	return (0);
}

int	is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}
