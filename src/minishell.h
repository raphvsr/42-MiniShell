#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <dirent.h>

typedef enum e_redir_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	int				was_quoted;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	char			*value;
	int				type;
	int				quoted;
	struct s_token	*next;
}	t_token;

t_env	*init_env(char **envp);
void	free_lenv(t_env *env_list);
t_env	*env_find(t_env *env_list, char *key);
int		env_set_value(t_env *env_list, char *key, char *value);
int		env_rm_value(t_env **env_list, char *key);
void	env_add_back(t_env **env_list, t_env *new_node);
int		env_add_value(t_env **env_list, char *key, char *value);
char	*env_key(char *env_str);
char	*env_value(char *env_str);
int		count_env(t_env *env_list);
char	**env_to_array(t_env *env_list);

int		execute_builtin(t_cmd *cmd, t_env **env_list, int status);
int		is_buildin(char *cmd);
int		b_pwd(void);
int		b_cd(char **argv, t_env **env_list);
int		b_echo(char **args);
int		b_exit(char **args, t_env **env_list, int last_status);
int		b_env(t_env **env_list);
int		b_unset(char **args, t_env **env_list);
int		b_export(char **args, t_env **env_list);

void	init_signals(void);
extern volatile sig_atomic_t	g_signal;
void	init_csignals(void);
void	init_signals_exec(void);

void	free_token(t_token **list);
void	add_back(t_token **list, t_token *new);
int		sym(char c);
int		find_end_quote(char *line, int *i);
t_token	*lexer(char *line);

int		parsing(t_token **tokens, t_cmd **head);

void	free_argv(char **argv);
void	free_redirs(t_redir *redir);
void	free_cmd(t_cmd **cmd);
void	add_back_cmd(t_cmd **list, t_cmd *new);
void	add_back_redir(t_redir **list, t_redir *new);
int		count_word_token(t_token *tmp);
char	*clean_token(t_token *token);
char	*new_line(char *line, int start, int end);

void	free_array(char **array);
void	err_exit(char *cmd, char *msg, int code);
void	err_warn(char *msg1, char *cmd, char *msg2);

int		executor(t_cmd **cmd, t_env **env_list, int status);
int		exec_redirs(t_redir *redirs);
int		exec_one_builtin(t_cmd *cmd, t_env **env_list, int status);
int		exec_pipe(t_cmd *cmd, t_env **env_list, int status);
int		heredoc(t_cmd *cmd);
char	*f_cmdpath(char *cmd, t_env *env_list);
void	cprocess(char *cmd_path, t_cmd *cmd, char **array_env);
int		childs_status(pid_t last_pid);
void	close_herdocs(t_cmd *cmd);

#endif
