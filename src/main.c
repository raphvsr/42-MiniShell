/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kheda <kheda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 19:22:28 by p0ubelle          #+#    #+#             */
/*   Updated: 2026/09/14 06:18:20 by kheda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_token	*tokens;
	t_cmd	*cmd;
	char	*line;
	int		status;

	status = 0;
	(void)ac;
	(void)av;
	env = init_env(envp);
	init_signals();
	tokens = NULL;
	while (1)
	{
		line = readline("p0ubelle> ");
		if (!line)
		{
			ft_putendl_fd("exit", 2);
			break ;
		}
		if (*line)
		{
			add_history(line);
			tokens = lexer(line);
			if (tokens)
			{
				cmd = NULL;
				if (parsing(&tokens, &cmd) && cmd)
					status = executor(&cmd, &env, status);
				free_cmd(&cmd);
				free_token(&tokens);
			}
		}
		free(line);
	}
	free_lenv(env);
	rl_clear_history();
	return (status);
}
