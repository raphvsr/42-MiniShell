
#include "../minishell.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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

    while (current && ft_strncmp(current->key, key, ft_strlen(key) + 1) != 0)
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

int env_add_value(t_env **env_list, char *key, char *value)
{
    t_env *new_node;

    if (env_find(*env_list, key))
    {
        if (value != NULL)
            return (env_set_value(*env_list, key, value));
        return 0;
    }
    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (1);
    new_node->key = ft_strdup(key);
    if (!new_node->key)
        return (free(new_node), 1);
    if (value)
    {
        new_node->value = ft_strdup(value);
        if (!new_node->value)
            return (free(new_node->key), free(new_node), 1);
    }
    else
        new_node->value = NULL;
    new_node->next = NULL;
    env_add_back(env_list, new_node);
    return (0);
}