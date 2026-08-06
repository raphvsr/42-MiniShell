/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p0ubelle <p0ubelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 19:22:28 by p0ubelle          #+#    #+#             */
/*   Updated: 2026/08/06 19:26:07 by p0ubelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

int	b_echo(char **args);

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("p0ubelle> ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (*line)
			add_history(line);
		free(line);
	}
	return 0;
}
