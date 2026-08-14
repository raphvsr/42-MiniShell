
#include "../minishell.h"


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
	if (!str[i])
		return 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		res = res * 10 + str[i] - '0';
		if ((sign == 1 && res > 9223372036854775807ULL)
			|| (sign == -1 && res > 9223372036854775808ULL))
			return (0);
		i++;
	}
	*cexit = (long long)(res * sign);
	return 1; // return 1 or 0 (err) and store the number in *cexit
	// otherwise if the user do exit -1 we dont know if its error -1
	// or just number -1
}


int b_exit(char **args, t_env **env_list, int lstatus)
{
	long long exit_code;

	write(2, "exit\n", 5);
	if(!args[1])
	{
		free_lenv(*env_list);
		exit((unsigned char)lstatus);
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

