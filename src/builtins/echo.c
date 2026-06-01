

// ◦ echo with option -n


#include "../minishell.h"

int b_echo(char **args)
{
    int i;
    int n_flag;

    i = 1;
    n_flag = 0;
    while (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
    {
        i++;
        n_flag = 1;
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

