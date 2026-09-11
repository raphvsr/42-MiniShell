/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kheda <kheda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 02:45:59 by kheda             #+#    #+#             */
/*   Updated: 2026/09/11 02:46:01 by kheda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../../libft/libft.h"

static int	add_redirs(t_redir **head, t_token **tmp)
{
	t_redir	*redirs;

	while (*tmp && (*tmp)->type != TOKEN_WORD && (*tmp)->type != TOKEN_PIPE)
	{
		if (!(*tmp)->next || (*tmp)->next->type != TOKEN_WORD) // >> > NO AND >> < NO AND > > NO AND < < NO, so protected.
			return (free_redirs(*head), 0); // ERREUR SYNTAXE
		redirs = malloc(sizeof(t_redir));
		if (!redirs)
			return (free_redirs(*head), 0); // ERREUR SYNTAXE
		redirs->type = (*tmp)->type;
		redirs->was_quoted = (*tmp)->next->quoted;
		redirs->file = clean_token((*tmp)->next);
		redirs->heredoc_fd = -1;
		redirs->next = NULL;
		add_back_redir(head, redirs);
		*tmp = (*tmp)->next->next;
	}
	return (1);
}

static char	**fill_argv(t_token **tmp)
{
	char	**argv;
	int			i;
	int			len;
	char		*s;

	len = count_word_token(*tmp); //test if word len = 0 ?
	argv = malloc(sizeof(char *) * (len + 1));
	if (!argv)
		return (NULL);

	i = 0;
	while (i < len && *tmp)
	{
		s = clean_token(*tmp);
		if (!s)
		{
			argv[i] = NULL;
			return (free_argv(argv), NULL);
		}
		argv[i] = s;
		*tmp = (*tmp)->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

static t_cmd *create_cmd(t_token **tmp)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);

	command->argv = fill_argv(tmp);
	if (!(command)->argv)
	{
		free(command);
		command = NULL;
		return(NULL);
	}
	if (!add_redirs(&command->redirs , tmp))
	{
		free_argv(command->argv);
		free(command);
		command = NULL;
		return (NULL);
	}
	command->next = NULL;
	return (command);
}

int parsing(t_token **tokens, t_cmd **head)
{
	t_token		*tmp;
	t_cmd	*new_cmd;

	if (!tokens || (*tokens)->type == TOKEN_PIPE)
		return (0);

	tmp = *tokens;
	while (tmp)
	{
		new_cmd = create_cmd(&tmp);
		if (!new_cmd)
			return (free_cmd(head), 0);
		add_back_cmd(head, new_cmd);
		if (tmp && tmp->type == TOKEN_PIPE)
		{
			if (!(tmp->next) || tmp->next->type == TOKEN_PIPE)
				return (free_cmd(head), 0);
			tmp = tmp->next;
		}
	}
	return (1);
}


int	main()
{
	char	*line;
	t_token	*token;
	t_cmd	*cmd;

	token = NULL;
	cmd = NULL;
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
			{	printf("NO\n"); continue;}
			else
				printf("OK\n");
			
			if (!parsing(&token, &cmd))
				printf("BAD\n");
			else
				printf("GOOD\n");
		}
		free(line);
	}

	t_cmd *tmp = cmd;
	int i;
	while (tmp)
	{
		printf("~\n");
		i = 0;
		while (tmp->argv[i])
		{
			printf("argv : %s\n", tmp->argv[i]);
			i++;
		}
		while (tmp->redirs)
		{
			printf("|redir| type : %d | file : %s | quoted? : %d | heredoc_fd : %d\n", tmp->redirs->type, tmp->redirs->file, tmp->redirs->was_quoted, tmp->redirs->heredoc_fd);
			tmp->redirs = tmp->redirs->next;
		}
		tmp = tmp->next;
	}
		// printf("argv : %s\n", tmp->argv[2]);

	return 0;
}

// cc parser_utils.c parser.c ../../../libft/libft.a  ../lexer/lexer.c ../lexer/lexer_utils.c ../parsing_utils.c -lreadline 




// Ce type de commande ne passera pas ! :)
// lexer git:(main) ✗ echo"world"
// zsh: command not found: echoworld
// echo"hi"|grep'i' IMPOSSIBLE

// TESTER (donc espace apres echo invalide, donc lexer est correct)
//  "echo" world
// world
// ➜  lexer git:(main) ✗ "echo " world
// zsh: command not found: echo 



// TEST
// ls || NO
// ls |  NO
// | ls  NO
// < file OK
// > file cat OK
// cat << END OK


// echo
//   ↓
// >>
//   ↓
// attend WORD
//   ↓
// voit >
//   ↓
// SYNTAX ERROR


// TODO : Si aucune commande mais que des redirections, ca marche ?