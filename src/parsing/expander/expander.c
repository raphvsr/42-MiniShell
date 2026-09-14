/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvasseur <raphael.vasseur@proton.me>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/12 16:28:02 by kheda             #+#    #+#             */
/*   Updated: 2026/09/14 16:13:07 by rvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*word(char *s, int *i)
{
	int		start;
	char	*new;

	start = *i;
	while (s[*i] && s[*i] != '$')
		(*i)++;
	new = ft_substr(s, start, *i - start);
	return (new);
}

char	*to_expand(char *s, t_env *env, int *i)
{
	char	*key;
	int		start;
	t_env	*key_env;

	start = *i;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	key = ft_substr(s, start, *i - start);
	if (!valid_env_name(key))
	{
		free(key);
		return (ft_strdup(""));
	}
	key_env = env_find(env, key);
	free(key);
	if (!key_env || !key_env->value)
		return (ft_strdup(""));
	return (ft_strdup(key_env->value));
}

char	*find_expand(char *s, t_env *env, int *i, int exit_status)
{
	char	*new;

	(*i)++;
	if (s[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(exit_status));
	}
	else if (ft_isdigit(s[*i]))
	{
		(*i)++;
		return (ft_strdup(""));
	}
	if (!s[*i] || (!ft_isalpha(s[*i]) && s[*i] != '_'))
		return (ft_strdup("$"));
	new = to_expand(s, env, i);
	return (new);
}

static char	*add_str(char *str, char *new)
{
	char	*new_str;

	new_str = ft_strjoin(str, new);
	free(str);
	free(new);
	return (new_str);
}

char	*expander(char *s, int quoted, t_env *env, int exit_status)
{
	char	*str;
	int		i;
	char	*new;

	if (quoted == 1)
		return (ft_strdup(s));
	str = ft_strdup("");
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			new = find_expand(s, env, &i, exit_status);
		else
			new = word(s, &i);
		if (!new)
			return (free(str), NULL);
		str = add_str(str, new);
		if (!str)
			return (NULL);
	}
	return (str);
}
