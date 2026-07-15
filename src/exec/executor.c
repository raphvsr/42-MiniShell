
#include "../minishell.h"

int execute_builtin(char **args, t_env **env_list)
{
    if (ft_strncmp(args[0], "echo", 5) == 0)
        return (b_echo(args));
    if (ft_strncmp(args[0], "cd", 3) == 0)
        return (b_cd(args, env_list));
    if (ft_strncmp(args[0], "pwd", 4) == 0)
        return (b_pwd());
    if (ft_strncmp(args[0], "export", 7) == 0)
        return (b_export(args, env_list));
    if (ft_strncmp(args[0], "unset", 6) == 0)
        return (b_unset(args, env_list));
    if (ft_strncmp(args[0], "env", 4) == 0)
        return (b_env(env_list));
    if (ft_strncmp(args[0], "exit", 5) == 0)
        return (b_exit(args, env_list));
    return (-1); // not a buildin
}