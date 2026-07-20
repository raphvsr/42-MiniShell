

#include "../minishell.h"

int b_unset(char **args, t_env **env_list)
{
    int i;

    i = 1;
    while (args[i]) {
        env_rm_value(env_list, args[i]);
        i++;
    }
    return 0;
}