/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kheda <kheda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 03:40:32 by kheda             #+#    #+#             */
/*   Updated: 2026/09/14 15:30:56 by kheda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env(t_env *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

int	count_env_wvalue(t_env *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		if (env_list->value)
			count++;
		env_list = env_list->next;
	}
	return (count);
}

static char	*format_env_kv(t_env *env)
{
	char	*str;

	str = malloc(ft_strlen(env->key) + ft_strlen(env->value) + 2);
	if (!str)
		return (NULL);
	ft_strcpy(str, env->key);
	ft_strcat(str, "=");
	ft_strcat(str, env->value);
	return (str);
}

static void	free_partial(char **array, int i)
{
	while (i > 0)
		free(array[--i]);
	free(array);
}

char	**env_to_array(t_env *env_list)
{
	char	**array;
	int		i;

	array = malloc(sizeof(char *) * (count_env_wvalue(env_list) + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (env_list)
	{
		if (env_list->value)
		{
			array[i] = format_env_kv(env_list);
			if (!array[i])
			{
				free_partial(array, i);
				return (NULL);
			}
			i++;
		}
		env_list = env_list->next;
	}
	array[i] = NULL;
	return (array);
}
