#include "../../minishell.h"
#include "../../../libft/libft.h"

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

void	token_type(t_token *new_token, char *s, int i)
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
		new_token->type = TOKEN_WORD; // check type & ?
}

t_token	*create_token(char *s, char quote, int start, int len)
{
	t_token	*new_token;

	printf("create : start : %d, len : %d\n", start, len);

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);

	new_token->value = ft_substr(s, start, len);   // adresse de la chaine donc on aura tout a partir de cette adresse ?         // NON CAR JE VAIS JUSQU'A LEN.
	if (quote == '\'')    // probleme ? il faut un len d'arret, et pas toute la chaine                  // exactement.
		new_token->quoted = 1;
	else if (quote == '"')
		new_token->quoted = 2;
	else
		new_token->quoted = 0;
 
	// printf("%s\n", token->value);
	new_token->next = NULL;
	token_type(new_token, s, start);
	return (new_token); ////
}
// TODO : recuperer la longuer, le debut du mot et sa fin (pour remplir structure value)


// int	token(t_token **list, char *s, int i)
// {
// 	int	len;

// 	printf("type\n");
// 	if (s[i] == s[i + 1] && s[i + 1] != '|')
// 		len = i + 2;
// 	else
// 		len = i + 1; // why i++ was infinit loop ? //wait i can do i++ when i do something = something !?

// 	add_back(list, create_token(s, 0, i, len - i)); // can put any character to idicate 'WORD', or just remove parameter quote
// 	// printf("\n======== %d ========\n", REDIR_APPEND);
// 	return (len);
// }

int	token_word(t_token **list, char *line, int i)
{
	int		start;
	char	quote;

	start = i;
	quote = 0;
	while (line[i] != ' ' && line[i] && !sym(line[i]))
	{
		// printf("----");
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			i++;
			while (line[i] != quote && line[i])
				i++;
			i++;
		}
		else
			i++;
	}
	printf("word : start: %d - len: %d\n", start, i);
	add_back(list, create_token(line, quote, start, i - start));
	quote = 0;
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
			if (line[i] == line[i + 1] && line[i + 1] != '|')
				len = i + 2;
			else
				len = i + 1;
			// printf("====%c, %c====", line[i], line[i+1]);
			add_back(&head, create_token(line, 0, i, len - i)); // can put any character to idicate 'WORD', or just remove parameter quote
			i = len;
		}
		else 
			i = token_word(&head, line, i);
	}
	return (head);
}

// int	main()
// {
// 	char	*line;
// 	t_token	*token;

// 	token = NULL;

// 	while (1)
// 	{
// 		line = readline("SHELL> ");
// 		if (!line)
// 		{
// 			printf("exit\n");
// 			break;
// 		}
// 		if (*line) // no need ?
// 		{
// 			add_history(line);
// 			token = lexer(line);
// 			if (!token)
// 				printf("NO\n");
// 			else
// 				printf("OK\n");
			
// 		}
// 		free(line);
// 	}

// 	t_token *tmp = token;
// 	while (tmp)
// 	{
// 		printf("---");
// 		printf("%s, type : %d , quoted : %d\n", tmp->value, tmp->type, tmp->quoted);
// 		tmp = tmp->next;
// 	}
// 	return 0;
// }


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