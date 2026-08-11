

// ◦ echo with option -n


#include "../minishell.h"

int b_echo(char **args)
{
    int i;
    int n_flag;
	int j;

    i = 1;
    n_flag = 0;
    while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break;
        n_flag = 1;
		i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if (args[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (!n_flag)
        write(STDOUT_FILENO, "\n", 1);
    return 0;
}

