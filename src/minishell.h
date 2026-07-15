
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


int main(void);


// env ($printenv)
t_env *init_env(char **envp);
void free_lenv(t_env *env_list);
t_env *env_find(t_env *env_list, char *key);
int env_set_value(t_env *env_list, char *key, char *value);
int env_rm_value(t_env **env_list, char *key);
void env_add_back(t_env **env_list, t_env *new_node);
int env_add_value(t_env **env_list, char *key, char *value);

// buildins
int b_pwd();
int b_cd(char **argv, t_env **env_list);
int b_echo(char **args);
int b_exit(char **args, t_env **env_list);
int b_env(t_env **env_list);
int b_unset(char **args, t_env **env_list);


#endif
