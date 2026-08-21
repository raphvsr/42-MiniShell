
#include "minishell.h"

void	err_exit(char *cmd, char *msg, int code)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putendl_fd(msg, 2);
    exit(code);
}


void	free_array(char **array)
{
	int i;

	if (!array)
		return ;
	i = 0;
	while(array[i])
		free(array[i++]);
	free(array);
}
