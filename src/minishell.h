
#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_env {
    char            *key;
    char            *value;
    struct s_env    *next;
} t_env;



int main(void);



#endif