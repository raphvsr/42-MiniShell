/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <raphael.vasseur@proton.me>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 19:22:28 by p0ubelle          #+#    #+#             */
/*   Updated: 2026/09/13 23:44:58 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	hline(char *line, t_env **env, int *status)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = lexer(line);
	if (!tokens)
		return ;
	cmd = NULL;
	if (parsing(&tokens, &cmd, *env, *status) && cmd)
		*status = executor(&cmd, env, *status);
	else
		*status = 2;
	free_cmd(&cmd);
	free_token(&tokens);
}

static int	startloop(t_env *env)
{
	char	*line;
	int		status;

	status = 0;
	while (1)
	{
		line = readline("p0ubelle> ");
		if (g_signal == SIGINT)
		{
			status = 130;
			g_signal = 0;
		}
		if (!line)
		{
			ft_putendl_fd("exit", 2);
			break ;
		}
		if (*line)
		{
			add_history(line);
			hline(line, &env, &status);
		}
		free(line);
	}
	return (status);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	int		status;

	(void)ac;
	(void)av;
	env = init_env(envp);
	init_signals();
	status = startloop(env);
	free_lenv(env);
	rl_clear_history();
	return (status);
}
