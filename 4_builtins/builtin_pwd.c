/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchaumei <rchaumei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 21:23:16 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/18 15:56:18 by rchaumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	make_pwd(void)
{
	char	buffer[BUFSIZ];

	if (!getcwd(buffer, BUFSIZ))
	{
		printf("Cannot get current working directory path");
		return (127);
	}
	return (printf("Current working directory: %s\n", buffer), 0);
}
