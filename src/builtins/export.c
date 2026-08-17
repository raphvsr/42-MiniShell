
#include "../minishell.h"

// TODO separate 25 lines functions -> norminette
// export need to validate the name (e.g USER=raph -> valid. 2USER=raph -> invalid)
static int validate(char *arg)
{
    int i;

    i = 1;
	if ((!arg || !ft_isalpha(arg[0])) && arg[0] != '_') // first letter
		return (0);
    while (arg[i] && arg[i] != '=') // for key
    {
        if (!ft_isalnum(arg[i]) && arg[i] != '_')
            return (0);
        i++;
    }
    return 1;
}



// create a temporary pointer array to sort without mooving the real one
void show_env(t_env *env_list)
{
	int i;
	int j;
	int env_len;
	t_env **tab;
	t_env *temp;

	env_len = count_env(env_list);
	if (env_len == 0)
		return ;
	if (!(tab = malloc(sizeof(t_env *) * env_len))) // t_env * = 8 bytes per slot
		return ;
	i = 0;
	while (env_list) // we fill the new array
	{
		tab[i++] = env_list;
		env_list = env_list->next;
	}
	i = 0;
	while (i < env_len)
	{
		j = i + 1;
		while (j < env_len) // we sort the new array
		{
			if (ft_strcmp(tab[i]->key, tab[j]->key) > 0)
			{
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < env_len)
	{
		if (tab[i]->value)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tab[i]->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tab[i]->value, 1);
			ft_putendl_fd("\"", 1);
		}
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putendl_fd(tab[i]->key, 1);
		}
		i++;
	}
	free(tab);
}

int b_export(char **args, t_env **env_list)
{
	int		i;
	int		cexport;
	char	*key;
	char	*value;

	if (!args[1]) // without arguments just print sorted list
		return(show_env(*env_list), 0);

	// print error for invalid key and set cexport = 1
	// but keep the loop to still export valid variables
	i = 1;
	cexport = 0;
	while (args[i])
	{
		if (!validate(args[i]))
		{
        	ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			cexport = 1;
		}
		else
		{
			key = env_key(args[i]);
			value = env_value(args[i]);
			env_add_value(env_list, key, value);
			free(key); // already ducplicated by env_add_value so we can free them
			free(value);
		}
		i++;
	}
	return (cexport);
}





