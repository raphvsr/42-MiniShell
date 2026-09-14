/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <raphael.vasseur@proton.me>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 18:22:41 by rvasseur          #+#    #+#             */
/*   Updated: 2026/09/14 20:00:04 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	digit_loop(const char *str, int *i, int sign,
	unsigned long long *res)
{
	unsigned long long	limit;
	int					digit;

	if (sign == 1)
		limit = (unsigned long long)LLONG_MAX;
	else
		limit = (unsigned long long)LLONG_MAX + 1;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		digit = str[*i] - '0';
		if (*res > (limit - digit) / 10)
			return (0);
		*res = *res * 10 + digit;
		(*i)++;
	}
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' ')
		(*i)++;
	return (str[*i] == '\0');
}

static int	validate(const char *str, long long *cexit)
{
	unsigned long long	res;
	int					i;
	int					sign;

	res = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i] || str[i] < '0' || str[i] > '9')
		return (0);
	if (!digit_loop(str, &i, sign, &res))
		return (0);
	*cexit = (long long)(res * sign);
	return (1);
}

static void	clean_exit(t_env *env, char *err_arg, int code)
{
	write(2, "exit\n", 5);
	if (err_arg)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(err_arg, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	free_lenv(env);
	rl_clear_history();
	exit((unsigned char)code);
}

int	b_exit(char **args, t_env **env_list, int last_status)
{
	long long	exit_code;

	if (!args[1])
		clean_exit(*env_list, NULL, last_status);
	if (!validate(args[1], &exit_code))
		clean_exit(*env_list, args[1], 2);
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (2);
	}
	clean_exit(*env_list, NULL, (int)exit_code);
	return (0);
}
