

// env with no options 
// should not print if no value with key

#include "../minishell.h"
#include <unistd.h>

void b_env(t_env *env_list)
{
    if (!env_list)
        return ;
    while (env_list)
    {
        if (env_list->key && env_list->value)
        {
            ft_putstr_fd(env_list->key, STDOUT_FILENO);
            write(STDOUT_FILENO, "=", 1);
            ft_putstr_fd(env_list->value, STDOUT_FILENO);
            write(STDOUT_FILENO, "\n", 1);
        }
        env_list=env_list->next;
    }
}