
#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
// # include <linux/limits.h>

typedef struct s_env {
	char            *key;
	char            *value;
	struct s_env    *next;
} t_env;


// redirections
typedef enum e_redir_type
{
	REDIR_IN,      // <
	REDIR_OUT,     // >
	REDIR_APPEND,  // >>
	REDIR_HEREDOC  // <<
}   t_redir_type;



// 1. struct de redirections (<, >, >>, <<)
typedef struct s_redir
{
	t_redir_type    type;
	char            *file;        // heredoc file name or heredoc delimiter
	int             was_quoted;   // 1 if ' ' or " " 0 if not
	int             heredoc_fd;   // heredoc filedescriptor (-1 if not a heredoc)
	struct s_redir  *next;
}   t_redir;


// 2. Pour chaque commande du pipeline (séparées par des pipes '|')
typedef struct s_cmd
{
	char            **argv;       // {"ls", "-la", NULL}
	t_redir         *redirs;      // liste des redirections
	struct s_cmd    *next;        // commande suivante après le pipe '|'
}   t_cmd;



// env ($printenv)
t_env *init_env(char **envp);
void free_lenv(t_env *env_list);
t_env *env_find(t_env *env_list, char *key);
int env_set_value(t_env *env_list, char *key, char *value);
int env_rm_value(t_env **env_list, char *key);
void env_add_back(t_env **env_list, t_env *new_node);
int env_add_value(t_env **env_list, char *key, char *value);
char *env_key(char *env_str);
char *env_value(char *env_str);
int count_env(t_env *env_list);
char	**env_to_array(t_env *env_list);


// buildins
int execute_builtin(t_cmd *cmd, t_env **env_list);
int	b_pwd();
int	b_cd(char **argv, t_env **env_list);
int	b_echo(char **args);
int	b_exit(char **args, t_env **env_list); // TODO: int lstatus
int	b_env(t_env **env_list); // TODO
int	b_unset(char **args, t_env **env_list);
int	b_export(char **args, t_env **env_list);

// signals
void init_signals(void);

// parsing
// int		symbol(char c);
char	**split_line(char const *s, char c);
t_cmd	*lexer(char *line);


// error
void	free_array(char **array);
void	err_exit(char *cmd, char *msg, int code);

// exec
int executor(t_cmd **cmd, t_env **env_list);
int exec_redirs(t_redir *redirs);


#endif



