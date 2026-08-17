/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: p0ubelle <p0ubelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 19:22:28 by p0ubelle          #+#    #+#             */
/*   Updated: 2026/08/17 16:01:02 by p0ubelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env 	*env;
	t_cmd	*command;
	char	*line;

	env = init_env(envp);
	// init_signals();
	command = NULL;
	while (1)
	{
		line = readline("p0ubelle> ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (*line) // no need ?
		{
			add_history(line);
			command = lexer(line);
			if (command && command->argv[0])
			{
				execute_builtin(command->argv, &env);
			}
			// char **args;
			// args = ft_split(line, ' ');
			// if (command->argv && command->argv[0])
			// {
			// 	execute_builtin(command->argv, &env);
			// }

		}
		free(line);
	}
	free_lenv(env);
	return 0;
}
