/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p0ubelle <p0ubelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 19:22:28 by p0ubelle          #+#    #+#             */
/*   Updated: 2026/08/15 08:03:10 by p0ubelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_env *env = init_env(envp);
	char	*line;

	init_signals();

	while (1)
	{
		line = readline("p0ubelle> ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (*line)
		{
			add_history(line);
			char **args;
			args = ft_split(line, ' ');
			if (args && args[0])
			{
				execute_builtin(args, &env);
			}
		}
		free(line);
	}
	return 0;
}
