

// env with no options 
// should not print if no value with key

#include "../minishell.h"

int b_env(t_env **env_list)
{
    t_env *current;

    if (!env_list)
        return (1);
    current = *env_list;
    while (current)
    {
        if (current->key && current->value)
        {
            ft_putstr_fd(current->key, STDOUT_FILENO);
            write(STDOUT_FILENO, "=", 1);
            ft_putstr_fd(current->value, STDOUT_FILENO);
            write(STDOUT_FILENO, "\n", 1);
        }
        current = current->next;
    }
    return (0);
}
