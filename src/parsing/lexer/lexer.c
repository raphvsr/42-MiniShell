#include "../../minishell.h"
#include "../../../libft/libft.h"

void	free_token(t_token **list)
{
	t_token *tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp->value);
		free(tmp);
	}
	printf("=");
}

void	add_back(t_token **list, t_token *new)
{
	t_token *current;

	if (!list || !new)
		return;
	if (!*list)
	{
		*list = new;
		return;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new;
}

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

static t_token	*create_token(t_token **list, char *s, char quote, int start, int len)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);

	new_token->value = ft_substr(s, start, len);
	if (!new_token->value)
		return (free_token(list), NULL);  //free_tokens ??? FREE
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

static int	token(t_token **list, char *s, int i)
{
	int	len;
	t_token *new;

	printf("type\n");
	if (s[i] == s[i + 1] && s[i + 1] != '|')
		len = i + 2;
	else
		len = i + 1;

	new = create_token(list, s, 0, i, len - i);
	if (!new)
		return (0);
	add_back(list, new);
	// printf("\n======== %d ========\n", REDIR_APPEND);
	return (len);
}

static int	token_word(t_token **list, char *line, int i)
{
	int		start;
	char	quote;
	t_token	*new;

	start = i;
	quote = 0;
	while (line[i] != ' ' && line[i] && !sym(line[i]))
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			i++;
			while (line[i] != quote && line[i])
				i++;
			if (!line[i])
				return (0); //ERREUR MESSAGE (unclosed quote)
			i++;
		}
		else
			i++;
	}
	printf("word : start: %d - len: %d\n", start, i);
	if (!(new = create_token(list, line, quote, start, i - start)))
		return (0);
	add_back(list, new);
	// quote = 0; // maybe no need, bcz the function will restart with quote = 0 on top
	return (i);
}

t_token	*lexer(char *line)
{
	t_token	*head;
	int		i;
	int		len;

	head = NULL; // no need?
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' && line[i])
			i++;
		if (line[i] == '\0')
			break ;
		if (sym(line[i]) && line[i] != ' ')
		{
			if (!(i = token(&head, line, i)))
				return (free_token(&head), NULL); // free here ?        // MESSAGE ERREUR //FREE
		}
		else 
		{
			i = token_word(&head, line, i);
			if (!i)
				return (free_token(&head), NULL); //free here ? or in main     // MESSAGE ERREUR //FREE
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


// to compile separately
//cc lexer.c ../../../libft/libft.a  ../parsing_utils.c -lreadline

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

// TODO : check if free is done, and on a good place
// TODO : check if symbol is as the first command, should not do anything (did, check again to be sure)
// TODO : \ (backslash) or ; (semicolon)
// TODO : || -> cree une erreur
// TODO : head->type == TOKEN_PIPE || head->type == REDIR_IN)  // check any symbol // PARSING


// > eww -> marche
// | dhfj -> NO
// >> eww -> marche
// << df -> marche
// < -> NO
// echo 'sd' d's -> NO
// "      " -> ca doit marcher ? apparement oui