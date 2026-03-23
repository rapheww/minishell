/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 21:26:20 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/18 14:57:38 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_node(t_env **env, char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (strcmp(curr->key, key) == 0)
		{
			if (prev == NULL)
				*env = curr->next;
			else
				prev->next = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	make_unset(t_env **env, char **str)
{
	int	i;

	i = 1;
	if (!str || !(*str))
		return (127);
	while (str[i])
	{
		remove_node(env, str[i]);
		i++;
	}
	return (0);
}
