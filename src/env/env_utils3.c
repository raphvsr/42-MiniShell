
#include "../minishell.h"

int count_env(t_env *env_list)
{
	int count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

int count_env_wvalue(t_env *env_list)
{
	int count;

	count = 0;
	while (env_list)
	{
		if (env_list->value)
			count++;
		env_list = env_list->next;
	}
	return (count);
}

char **env_to_array(t_env *env_list)
{
	char **array;
	int i;
	int env_len;

	env_len = count_env_wvalue(env_list);
	array = malloc(sizeof(char *) * (env_len + 1));
	if (!array)
		return NULL;
	i = 0;
	while (env_list)
	{
		if (env_list->value)
		{
			array[i] = malloc (ft_strlen(env_list->key) + ft_strlen(env_list->value) + 2); // +1 for '=' +1 for '\0'
			if (!array[i])
			{
				while (i > 0)
					free(array[--i]);
				free(array);
				return NULL;
			}
			ft_strcpy(array[i], env_list->key);
			ft_strcat(array[i], "=");
			ft_strcat(array[i], env_list->value);
			i++;
		}
		env_list = env_list->next;
	}
	array[i] = NULL;
	return (array);
}










