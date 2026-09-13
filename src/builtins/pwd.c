/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <raphael.vasseur@proton.me>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 23:56:45 by rvasseur          #+#    #+#             */
/*   Updated: 2026/09/12 23:57:14 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_pwd(void)
{
	char	curr_path[PATH_MAX];

	if (getcwd(curr_path, sizeof(curr_path)))
	{
		ft_putstr_fd(curr_path, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	return (perror("minishell: pwd"), 1);
}
