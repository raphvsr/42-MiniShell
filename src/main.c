/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <rvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 19:22:28 by p0ubelle          #+#    #+#             */
/*   Updated: 2026/08/29 19:39:56 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env 	*env;
	t_token	*tokens;
	char	*line;
	int		status = 0; // FIXME: temp

	env = init_env(envp);

	init_signals();
	tokens = NULL;
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
			tokens = lexer(line);
			(void)tokens;
			// Once parser is implemented:
			// command = parser(tokens);
			// if (command && command->argv[0])
			// 	status = executor(&command, &env);
		}
		free(line);
	}
	free_lenv(env);
	return (status);
}
