/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kheda <kheda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 01:09:10 by kheda             #+#    #+#             */
/*   Updated: 2026/09/14 15:31:54 by kheda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_warn(char *msg1, char *cmd, char *msg2)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(msg2, 2);
}

void	err_exit(char *cmd, char *msg, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(msg, 2);
	exit(code);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}
