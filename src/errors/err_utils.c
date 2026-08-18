
#include "minishell.h"

void err_exit(char *cmd, char *msg, int code)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putendl_fd(msg, 2);
    exit(code);
}
