
#include "../minishell.h"

void free_lenv(t_env *env_list)
{
    t_env *temp;

    while (env_list)
    {
        temp = env_list->next;
        free(env_list->key);
        free(env_list->value);
        free(env_list);
        env_list = temp;
    }
}