
#include "../minishell.h"
#include <stdlib.h>
#include <time.h>

t_env *env_find(t_env *env_list, char *key)
  {
      while (env_list)
      {
          if (ft_strncmp(env_list->key, key, ft_strlen(key) + 1) == 0)
              return (env_list);
          env_list = env_list->next;
      }
      return (NULL);
  }


int env_set_value(t_env *env_list, char *key, char *value)
{
    t_env *node;
    char  *new_value;

    node = env_find(env_list, key);
    if (!node)
        return (1);
    new_value = ft_strdup(value);
    if (!new_value)
        return (1);
    free(node->value);
    node->value = new_value;
    return (0);
}

int env_rm_value(t_env **env_list, char *key)
{
    t_env  *current;
    t_env  *previous;
    
    current = *env_list;
    previous = NULL;

    while (current->key != key)
    {
        previous = current;
        current = current->next;
    }
    if (current == NULL)
        return 0;
    if (previous == NULL)
        *env_list = current->next;
    else
        previous->next = current->next;
    free(current->key);
    free(current->value);
    free(current);
    
    
    return (0);
}