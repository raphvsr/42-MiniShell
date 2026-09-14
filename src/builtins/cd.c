/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <raphael.vasseur@proton.me>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 14:19:41 by rvasseur          #+#    #+#             */
/*   Updated: 2026/09/14 14:19:43 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	up_pwd(t_env **env_list, char *old_pwd)
{
	char	new_pwd[PATH_MAX];

	if (old_pwd[0] != '\0')
		env_add_value(env_list, "OLDPWD", old_pwd);
	if (getcwd(new_pwd, sizeof(new_pwd)))
		env_add_value(env_list, "PWD", new_pwd);
}

int	b_cd(char **argv, t_env **env_list)
{
	char	old_pwd[PATH_MAX];
	char	*target;
	t_env	*home;

	if (argv[1] && argv[2])
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	if (!argv[1] || ft_strncmp(argv[1], "~", 2) == 0)
	{
		home = env_find(*env_list, "HOME");
		if (!home || !home->value)
			return (write(2, "minishell: cd: HOME not set\n", 28), 1);
		target = home->value;
	}
	else
		target = argv[1];
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		old_pwd[0] = '\0';
	if (chdir(target) == -1)
		return (ft_putstr_fd("minishell: cd: ", 2), perror(target), 1);
	up_pwd(env_list, old_pwd);
	return (0);
}
