/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <raphael.vasseur@proton.me>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 01:07:45 by rvasseur          #+#    #+#             */
/*   Updated: 2026/09/11 01:07:49 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_unset(char **args, t_env **env_list)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	ret = 0;
	while (args[++i])
	{
		j = 0;
		if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
			j = -1;
		while (j >= 0 && args[i][++j])
			if (!ft_isalnum(args[i][j]) && args[i][j] != '_')
				j = -1;
		if (j == -1 && ++ret)
			err_warn("unset: `", args[i], "': not a valid identifier");
		else
			env_rm_value(env_list, args[i]);
	}
	return (ret != 0);
}
