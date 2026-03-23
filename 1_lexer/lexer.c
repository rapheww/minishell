/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 17:46:18 by rchaumei          #+#    #+#             */
/*   Updated: 2026/03/23 16:09:45 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	read_word(char *str, int *i, char **token_value,
		char **first_quotes)
{
	int		j;
	char	*buffer;
	int		state;
	char	*tmp;

	buffer = init_read(&j, &state, &tmp, str);
	if (!buffer)
		return (-1);
	while (str[*i])
	{
		if (check_word(buffer, &state, &j, str[*i]) == 1)
		{
			(*i)--;
			break ;
		}
		change_tmp(&tmp, state);
		(*i)++;
	}
	if (state != 0)
		return (free(buffer), free(tmp), -1);
	buffer[j] = '\0';
	*token_value = buffer;
	*first_quotes = tmp;
	return (0);
}

static int	read_word_quotes(char *str, int i, char **quotes)
{
	int		j;
	char	*buffer;
	int		state;
	char	*tmp;

	j = 0;
	state = 0;
	tmp = NULL;
	buffer = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!buffer)
		return (-1);
	while (str[i])
	{
		if (check_word_quotes(buffer, &state, &j, str[i]) == 1)
			break ;
		i++;
	}
	if (state != 0)
		return (free(buffer), free(tmp), -1);
	buffer[j] = '\0';
	*quotes = buffer;
	return (0);
}

static int	handle_operator(t_token **lexer, char *str, int *i)
{
	if (str[*i] == '|')
		addback_token(lexer, create_token(TOKEN_PIPE, NULL, NULL, NULL));
	else if (str[*i + 1] && str[*i] == '>' && str[*i + 1] == '>')
	{
		addback_token(lexer, create_token(TOKEN_APPEND, NULL, NULL, NULL));
		(*i)++;
	}
	else if (str[*i + 1] && str[*i] == '<' && str[*i + 1] == '<')
	{
		addback_token(lexer, create_token(TOKEN_HEREDOC, NULL, NULL, NULL));
		(*i)++;
	}
	else if (str[*i] == '<')
		addback_token(lexer, create_token(TOKEN_REDIR_IN, NULL, NULL, NULL));
	else if (str[*i] == '>')
		addback_token(lexer, create_token(TOKEN_REDIR_OUT, NULL, NULL, NULL));
	else
		return (0);
	return (1);
}

int	check_lexer(t_token **lexer, char **token_value, char *str, int *i)
{
	char	*quotes;
	char	*first_quotes;

	if (handle_operator(lexer, str, i))
		return (0);
	if (read_word_quotes(str, *i, &quotes) == -1)
	{
		printf("Lexer error: unclosed quote\n");
		return (1);
	}
	if (read_word(str, i, token_value, &first_quotes) != 0)
	{
		printf("Lexer error: unclosed quote\n");
		return (1);
	}
	addback_token(lexer, create_token(TOKEN_WORD, *token_value, first_quotes,
			quotes));
	return (0);
}

t_token	*start_lexer(char *str)
{
	int		i;
	t_token	*lexer;
	char	*token_value;

	i = 0;
	lexer = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		skip_space_tab(str, &i);
		if (!str[i])
			break ;
		if (check_lexer(&lexer, &token_value, str, &i))
			return (free_lexer(lexer), NULL);
		if (!str[i])
			break ;
		i++;
	}
	return (lexer);
}
