/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kheda <kheda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 15:58:30 by kheda             #+#    #+#             */
/*   Updated: 2026/09/14 07:13:51 by kheda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_error(void)
{
	ft_putstr_fd("minishell: syntax error : unclosed quote\n", 2);
	return (0);
}

// int	sytax_error(t_token *token)
// {
	
// 	return (0); // or just void
// }
