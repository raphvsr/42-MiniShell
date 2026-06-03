

// ◦ pwd with no options

#include "../minishell.h"

int b_pwd()
{
    char curr_path[PATH_MAX]; // a changer ? 4096 ?

    if (getcwd(curr_path, sizeof(curr_path)))
    {
        ft_putstr_fd(curr_path, STDOUT_FILENO);
        write(STDOUT_FILENO, "\n", 1);
        return 0;
    }
    else
        return (ft_putstr_fd("error getting path", STDOUT_FILENO), 1);
}
