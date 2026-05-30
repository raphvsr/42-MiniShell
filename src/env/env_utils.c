
#include "../minishell.h"

// env_key -> part before '='
// env_value -> part after '='

// example -> SHELL=/usr/bin/bash     
// env_key = SHELL  
// env_value = /usr/bin/bash


char *env_key(char *env_str)
{
    int i;

    i = 0;
    while (env_str[i] && env_str[i] != '=')
        i++;
    return (ft_substr(env_str, 0, i)); // stop at first '='
}

char *env_value(char *env_str)
{
    int i;

    i = 0;
    while (env_str[i] && env_str[i] != '=')
        i++;
    // if no '=' -> value is NULL
    if (env_str[i] == '\0')
        return (NULL);
    // +1 to skip '='
    return (ft_strdup(env_str + i + 1));
}

t_env *env_node(char *env_str)
{
    t_env *new_node;

    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (NULL);
    new_node->key = env_key(env_str);
    new_node->value = env_value(env_str);
    new_node->next = NULL;
    
    // if strdup or substr failed :
    if (!new_node->key)
    {
        free(new_node->value);
        free(new_node);
        return (NULL);
    }
    return (new_node);
}

void env_add_back(t_env **env_list, t_env *new_node)
{
    t_env *temp;

    if (!*env_list)
    {
        *env_list = new_node;
        return ;
    }
    temp = *env_list;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
}

t_env *init_env(char **envp)
{
    t_env   *env_list;
    t_env   *new_node;
    int     i;

    env_list = NULL;
    i = 0;
    while (envp[i])
    {
        new_node = env_node(envp[i]);
        if (!new_node)
        {
            // free_env_list(env_list); 
            return (NULL);
        }
        env_add_back(&env_list, new_node);
        i++;
    }
    return (env_list);
}