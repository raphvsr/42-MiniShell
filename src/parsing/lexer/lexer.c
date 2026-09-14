/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kheda <kheda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 02:46:26 by kheda             #+#    #+#             */
/*   Updated: 2026/09/14 15:31:44 by kheda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../../libft/libft.h"

static void	token_type(t_token *new_token, char *s, int i)
{
	if (s[i] == '|')
		new_token->type = TOKEN_PIPE;
	else if (s[i] == '>' && s[i + 1] == '>')
		new_token->type = REDIR_APPEND;
	else if (s[i] == '<' && s[i + 1] == '<')
		new_token->type = REDIR_HEREDOC;
	else if (s[i] == '<')
		new_token->type = REDIR_IN;
	else if (s[i] == '>')
		new_token->type = REDIR_OUT;
	else
		new_token->type = TOKEN_WORD;
}

static t_token	*create_token(char *s, char quote, int start, int len)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_substr(s, start, len);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	if (quote == '\'')
		new_token->quoted = 1;
	else if (quote == '"')
		new_token->quoted = 2;
	else
		new_token->quoted = 0;
	new_token->next = NULL;
	token_type(new_token, s, start);
	return (new_token);
}

static int	token(t_token **list, char *s, int *i)
{
	t_token	*new;
	int		len;

	if (s[*i] == s[*i + 1] && s[*i + 1] != '|')
		len = *i + 2;
	else
		len = *i + 1;
	new = create_token(s, 0, *i, len - *i);
	if (!new)
		return (0);
	add_back(list, new);
	*i = len;
	return (1);
}

static int	token_word(t_token **list, char *line, int *i)
{
	t_token	*new;
	int		start;
	char	quote;

	start = *i;
	quote = 0;
	while (line[*i] != ' ' && line[*i] && !sym(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			quote = line[*i];
			if (!find_end_quote(line, i))
				return (quote_error());  /*ERREUR MESSAGE (unclosed quote) */
		}
		else
			(*i)++;
	}
	new = create_token(line, quote, start, *i - start);
	if (!new)
		return (0);
	add_back(list, new);
	return (1);
}

t_token	*lexer(char *line)
{
	t_token	*head;
	int		i;

	head = NULL;
	i = 0;
	while (line[i])
	{
		while ((line[i] == ' ' || line[i] == '\t') && line[i])
			i++;
		if (line[i] == '\0')
			break ;
		if (sym(line[i]) && line[i] != ' ' && line[i] != '\t')
		{
			if (!token(&head, line, &i))
				return (free_token(&head), NULL);
		}
		else
		{
			if (!token_word(&head, line, &i))
				return (free_token(&head), NULL);
		}
	}
	return (head);
}

int	main()
{
	char	*line;
	t_token	*token;

	token = NULL;

	while (1)
	{
		line = readline("SHELL> ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (*line) // no need ?
		{
			add_history(line);
			token = lexer(line);
			if (!token)
				printf("NO\n");
			else
				printf("OK\n");

		}
		free(line);
	}

	t_token *tmp = token;
	while (tmp)
	{
		printf("---");
		printf("%s, type : %d , quoted : %d\n", tmp->value, tmp->type, tmp->quoted);
		tmp = tmp->next;
	}
	return 0;
}


//cc lexer.c ../../../libft/libft.a  ../parsing_utils.c lexer_utils.c -lreadline

// TEST : //
// echo"hi" -> 1
// "echo \"hi\" | grep" -> 1
// "echo\"hi\"" -> 1
// echo abc"def"ghi -> 2
// echo "hi" | grep -> 4
// echo "hi -> ne devrait pas marcher
//echo hello echo "hello" 'world' | OR << OR >> OR >
//echo "nevermind" || grep "never mind"
// echo 'sd' d's -> ca doit marcher ?

// TODO : \ (backslash) or ; (semicolon)
// TODO : || -> cree une erreur


// > eww -> marche
// | dhfj -> NO
// >> eww -> marche
// << df -> marche
// < -> NO
// echo 'sd' d's -> NO
// "      " -> OK
// echo || hello -> OK
