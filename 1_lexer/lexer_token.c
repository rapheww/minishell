/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:54:25 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/18 14:11:04 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*create_token(t_token_type type, char *value, char *value2,
		char *value3)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	new->value_quotes = value3;
	new->first_quotes = value2;
	new->next = NULL;
	return (new);
}

void	addback_token(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	add_tokens(t_token **lexer, int *i, char *str)
{
	if (str[*i] == '|')
		return (addback_token(lexer, create_token(TOKEN_PIPE, NULL, NULL,
					NULL)), 0);
	else if (str[*i + 1] && str[*i] == '>' && str[*i + 1] == '>')
	{
		addback_token(lexer, create_token(TOKEN_APPEND, NULL, NULL, NULL));
		(*i)++;
		return (0);
	}
	else if (str[*i + 1] && str[*i] == '<' && str[*i + 1] == '<')
	{
		addback_token(lexer, create_token(TOKEN_HEREDOC, NULL, NULL, NULL));
		(*i)++;
		return (0);
	}
	else if (str[*i] == '<')
		return (addback_token(lexer, create_token(TOKEN_REDIR_IN, NULL, NULL,
					NULL)), 0);
	else if (str[*i] == '>')
		return (addback_token(lexer, create_token(TOKEN_REDIR_OUT, NULL, NULL,
					NULL)), 0);
	return (1);
}
