/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kheda <kheda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 02:45:59 by kheda             #+#    #+#             */
/*   Updated: 2026/09/14 15:33:07 by kheda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_redir(t_redir **head, t_token **tmp, t_env *env, int exit_status)
{
	t_redir	*redir;
	char	*new;

	if (!(*tmp)->next || (*tmp)->next->type != TOKEN_WORD) // >> > NO AND >> < NO AND > > NO AND < < NO, so protected.
		return (free_redirs(*head), 0); // ERREUR SYNTAXE
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (free_redirs(*head), 0); // ERREUR SYNTAXE
	redir->type = (*tmp)->type;
	redir->was_quoted = (*tmp)->next->quoted;
	redir->file = clean_token((*tmp)->next);
	if (redir->was_quoted != 1 && redir->type != REDIR_HEREDOC)
	{
		new = expander(redir->file, redir->was_quoted, env, exit_status);
		if (!new)
			return (free(redir->file), free_redirs(*head), free(redir), 0);
		free(redir->file);
		redir->file = new;
	}
	redir->heredoc_fd = -1;
	redir->next = NULL;
	add_back_redir(head, redir);
	*tmp = (*tmp)->next->next;
	return (1);
}

static char	*fill_argv(t_token **tmp, t_env *env, int exit_status)
{
	char	*s;
	char	*new;

	s = clean_token(*tmp);
	if (!s)
		return (NULL);
	new = expander(s, (*tmp)->quoted, env, exit_status);
	if (!new)
		return (NULL);
	free(s);
	s = new;
	*tmp = (*tmp)->next;
	return (s);
}

static t_cmd *create_cmd(t_token **tmp, t_env *env, int exit_status)
{
	t_cmd	*command;
	int		i;

	command = malloc(sizeof(t_cmd));
	if (!command)
		return (NULL);
	command->redirs = NULL;
	command->argv = malloc(sizeof(char *) * (count_word_token(*tmp) + 1));
	if (!command->argv)
	{
		free(command);
		command = NULL;
		return (NULL);
	}
	i = 0;
	while ((*tmp) && (*tmp)->type != TOKEN_PIPE)
	{
		if ((*tmp)->type == TOKEN_WORD)
		{
			command->argv[i] = fill_argv(tmp, env, exit_status);
			if (!command->argv[i])
			{
				command->argv[i] = NULL;
				free_argv(command->argv);
				free_redirs(command->redirs);
				free(command);
				command = NULL;
				return (NULL);
			}
			i++;
			// *tmp = (*tmp)->next;// maybe not here
		}
		else
		{
			if (!add_redir(&command->redirs , tmp, env, exit_status))
			{
				command->argv[i] = NULL;
				free_argv(command->argv);
				free(command);
				command = NULL;
				return (NULL);
			}
		}
	}
	command->argv[i] = NULL;
	command->next = NULL;
	return (command);
}

// if (!(command)->argv)
	// {
	// 	free(command);
	// 	command = NULL;
	// 	return(NULL);
	// }
	// if (!add_redirs(&command->redirs , tmp))
	// {
	// 	free_argv(command->argv);
	// 	free(command);
	// 	command = NULL;
	// 	return (NULL);
	// }

int	parsing(t_token **tokens, t_cmd **head, t_env *env, int exit_status)
{
	t_token		*tmp;
	t_cmd		*new_cmd;

	if (!tokens || (*tokens)->type == TOKEN_PIPE)
		return (0);
	tmp = *tokens;
	while (tmp)
	{
		new_cmd = create_cmd(&tmp, env, exit_status);
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
// TODO : Le vrai souci ici : (*tmp)->quoted est un flag global pour tout le token — mais si le token est mixte (abc"$USER"def)


// TEST
// ➜  lexer git:(main) ✗ echo abc"$USER"ghi
// abckhedaghi
// ➜  lexer git:(main) ✗ echo abc'$USER'ghi
// abc$USERghi
// ➜  lexer git:(main) ✗ echo "abc"$USER"ghi"
// abckhedaghi
// ➜  lexer git:(main) ✗ echo "abc'$USER'ghi"
// abc'kheda'ghi
// ➜  lexer git:(main) ✗ echo "abc'$USER'ghi"


// bash-5.1# echo abc"$USER"ghi
// abcghi
// bash-5.1# echo abc'$USER'ghi
// abc$USERghi
// bash-5.1# echo "abc"$USER"ghi"
// abcghi
// bash-5.1# echo "abc'$USER'ghi"
// abc''ghi
// bash-5.1# echo "abc'$USER'ghi"
// abc''ghi
