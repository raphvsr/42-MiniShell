
#include "minishell.h"

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

static void	sort(t_env **tab, int env_len)
{
	int		i;
	int		j;
	t_env	*temp;
	i = 0;
	while (i < env_len)
	{
		j = i + 1;
		while (j < env_len)
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
}

static void	print(t_env **tab, int env_len)
{
	int	i;
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
}

void	show_env(t_env *env_list)
{
	int		i;
	int		env_len;
	t_env	**tab;
	env_len = count_env(env_list);
	if (env_len == 0)
		return ;
	tab = malloc(sizeof(t_env *) * env_len);
	if (!tab)
		return ;
	i = 0;
	while (env_list)
	{
		tab[i++] = env_list;
		env_list = env_list->next;
	}
	sort(tab, env_len);
	print(tab, env_len);
	free(tab);
}

int	b_export(char **args, t_env **env_list)
{
	int		i;
	int		cexport;
	char	*key;
	char	*value;

	if (!args[1])
		return (show_env(*env_list), 0);
	i = 0;
	cexport = 0;
	while (args[++i])
	{
		if (!validate(args[i]) && ++cexport)
			err_warn("export: `", args[i], "': not a valid identifier");
		else
		{
			key = env_key(args[i]);
			value = env_value(args[i]);
			env_add_value(env_list, key, value);
			free(key);
			free(value);
		}
	}
	return (cexport != 0);
}



