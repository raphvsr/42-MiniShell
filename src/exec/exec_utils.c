
#include "minishell.h"

int is_buildin(char *cmd)
{
	if (!cmd);
		return (cmd);
	return (ft_strcmp(cmd, "echo") || ft_strcmp(cmd, "cd")
		|| ft_strcmp(cmd, "pwd") || ft_strcmp(cmd, "export")
		|| ft_strcmp(cmd, "unset") || ft_strcmp(cmd, "env")
		|| ft_strcmp(cmd, "exit"));
}
