/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:48:08 by rchaumei          #+#    #+#             */
/*   Updated: 2026/03/23 20:37:50 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*token_value(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return ("|");
	else if (type == TOKEN_REDIR_IN)
		return ("<");
	else if (type == TOKEN_REDIR_OUT)
		return (">");
	else if (type == TOKEN_HEREDOC)
		return ("<<");
	else if (type == TOKEN_APPEND)
		return (">>");
	else
		return (NULL);
}

int	check_double_token(t_token *lexer)
{
	if (lexer && lexer->type == TOKEN_PIPE)
		return (printf("syntax error near unexpected token `|'\n"), 1);
	while (lexer)
	{
		if (lexer->type == TOKEN_PIPE && (lexer->next == NULL
				|| lexer->next->type == TOKEN_PIPE))
			return (printf("syntax error near unexpected token `|'\n"), 1);
		if (lexer && lexer->next)
		{
			if (lexer->type != TOKEN_WORD && lexer->type != TOKEN_PIPE
				&& lexer->next->type != TOKEN_WORD)
				return (printf("syntax error near unexpected token `%s'\n",
						token_value(lexer->next->type)), 1);
		}
		if (lexer && lexer->next == NULL && lexer->type != TOKEN_WORD
			&& lexer->type != TOKEN_PIPE)
			return (printf("syntax error near unexpected token `newline'\n"),
				1);
		lexer = lexer->next;
	}
	return (0);
}

int	return_var(char **result, t_env_var var)
{
	char	*old;

	free(var.tmp);
	old = *result;
	if (!var.variable)
		*result = ft_strjoin(old, "");
	else
	{
		*result = ft_strjoin(old, var.variable);
		free(var.variable);
	}
	free(old);
	return (var.len);
}
