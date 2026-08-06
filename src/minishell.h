
#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <linux/limits.h>

typedef struct s_env {
    char            *key;
    char            *value;
    struct s_env    *next;
} t_env;


// 1. struct de redirections (<, >, >>, <<)
typedef struct s_redir
{
    int             type; // REDIR_IN (0), REDIR_OUT (1), APPEND (2), HEREDOC (3)
    char            *file; // nom fichier ou délimiteur du yheredoc
    struct s_redir  *next;
}   t_redir;

// 2. Pour chaque commande du pipeline (séparées par des pipes '|')
typedef struct s_cmd
{
    char            **argv;     // Tableau d'arguments (ex: {"ls", "-la", NULL})
    t_redir         *redirs;   // Liste chaînée des redirections de cette commande
    struct s_cmd    *next;     // Commande suivante après le '|' (NULL si dernière)
}   t_cmd;




int main(int ac, char **av, char **envp);

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


// buildins
int execute_builtin(char **args, t_env **env_list); // detecter les buildins
int b_pwd();
int b_cd(char **argv, t_env **env_list);
int b_echo(char **args);
int b_exit(char **args, t_env **env_list);
int b_env(t_env **env_list);
int b_unset(char **args, t_env **env_list);
int b_export(char *arg, t_env **env_list);


#endif



