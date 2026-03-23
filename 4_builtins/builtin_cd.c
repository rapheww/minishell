/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchambos <lchambos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 21:22:11 by lchambos          #+#    #+#             */
/*   Updated: 2026/03/23 13:24:20 by lchambos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	change_oldpwd(t_env *env)
{
	t_env	*tmp;
	char	buffer[BUFSIZ];

	tmp = find_env(env, "OLDPWD");
	if (!tmp)
		return ;
	if (!getcwd(buffer, BUFSIZ))
		return ;
	free(tmp->value);
	tmp->value = strdup(buffer);
}

static void	change_pwd(t_env *env, int use_home)
{
	t_env	*tmp;
	t_env	*home;
	char	buffer[BUFSIZ];

	tmp = find_env(env, "PWD");
	home = find_env(env, "HOME");
	if (!tmp)
		return ;
	if (!getcwd(buffer, BUFSIZ))
		return ;
	free(tmp->value);
	tmp->value = NULL;
	if (use_home)
	{
		if (home && home->value)
			tmp->value = strdup(home->value);
		else
			tmp->value = strdup(buffer);
	}
	else
		tmp->value = strdup(buffer);
}

int	make_cd(t_env *env, char **str)
{
	t_env	*home;
	char	*home_path;

	if (str[1] && str[2])
		return (msg("cd: too many arguments\n", str[1], 127));
	change_oldpwd(env);
	if (!str[1] || str[1][0] == '\0')
	{
		change_pwd(env, 1);
		home = find_env(env, "HOME");
		if (home && home->value)
			home_path = home->value;
		else
			home_path = ".";
		if (chdir(home_path) != 0)
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
		return (0);
	}
	if (chdir(str[1]) == -1)
		return (msg("cd: no such file or directory: %s\n", str[1], 127));
	change_pwd(env, 0);
	return (0);
}
