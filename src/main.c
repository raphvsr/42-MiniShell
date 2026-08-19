/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <rvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 19:22:28 by p0ubelle          #+#    #+#             */
/*   Updated: 2026/08/19 15:25:54 by rvasseur         ###   ########.fr       */
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
			printf("____result parsing____\n");
			command = lexer(line);
			if (command && command->argv[0])
			{
				printf("_____result exec_____\n");
				executor(command->argv, &env, &command);
				printf("\n\n\n");
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
