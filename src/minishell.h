
#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
#include <linux/limits.h>

typedef struct s_env {
    char            *key;
    char            *value;
    struct s_env    *next;
} t_env;


int main(void);


// env ($printenv)
t_env *init_env(char **envp);
void free_lenv(t_env *env_list);

// buildins
int b_pwd();
int b_echo(char **args);
int b_exit(char **args, t_env **env_list);


#endif