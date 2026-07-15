

#include "../minishell.h"

int b_unset(char **args, t_env **env_list)
{
    int i;

    i = 1;
    while (args[i]) {
        env_find(*env_list, args[i]);
    
    }
}

// ◦ unset with no options
