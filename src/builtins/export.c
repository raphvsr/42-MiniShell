

// ◦ export with no options


#include "../minishell.h"

// export need to validate the name (e.g USER=raph -> valid. 2USER=raph -> invalid)

int is_valid_export(char *arg)
{
    int i;

    i = 0;
    if (!arg)
        return (0);
    if ((!ft_isalpha(arg[0]) && arg[0] != '_'))
        return (0);
    while (arg[i] && arg[i] != '=') 
    {
        if (!ft_isalnum(arg[i]) && arg[i] != '_')
            return (0);
        i++;
    }
    return 1;
}

int b_export(char *arg, t_env **env_list)
{
    if (!is_valid_export(arg))
        return 0;
    
}