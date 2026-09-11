
#include "minishell.h"

static int	digit_loop(const char *str, int *i, int sign, unsigned long long *res)
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

static int validate(const char *str, long long *cexit)
{
	unsigned long long res = 0;
	int i = 0;
	int sign = 1;

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
	return 1;
}


int b_exit(char **args, t_env **env_list, int last_status)
{
	long long exit_code;

	write(2, "exit\n", 5);
	if(!args[1])
	{
		free_lenv(*env_list);
		rl_clear_history();
		exit((unsigned char)last_status);
	}

	if (!validate(args[1], &exit_code))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		free_lenv(*env_list);
		exit(2); // even if not valide we exit with 2
	}

	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1); // if >1 arguments we dont leave shell
	}
	free_lenv(*env_list);
	exit((unsigned char)exit_code);
	return (0);
}



