
#include "minishell.h"

int executor(char **args, t_env **env_list)
{
	if (execute_builtin(args, env_list) == 0)
		return 0;
	printf("not a builtin");
	return 0;
}

int execute_builtin(char **args, t_env **env_list)
{
	if (ft_strncmp(args[0], "echo", 5) == 0)
		return (b_echo(args));
	if (ft_strncmp(args[0], "cd", 3) == 0)
		return (b_cd(args, env_list));
	if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (b_pwd());
   if (ft_strncmp(args[0], "export", 7) == 0)
	   return (b_export(args, env_list));
	if (ft_strncmp(args[0], "unset", 6) == 0)
		return (b_unset(args, env_list));
	if (ft_strncmp(args[0], "env", 4) == 0)
		return (b_env(env_list));
	if (ft_strncmp(args[0], "exit", 5) == 0)
		return (b_exit(args, env_list));
	return (-1); // not a buildin
}

int exec_cmd(t_cmd *cmd, t_env *env)
{
	char **array_env;

	array_env = env_to_array(env);
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return 0;
	// int pid = fork();	// commands delete all memory and replace it so we must create a child (clone) to sacrifice himself
	// if (pid == 0)

	if (ft_strchr(cmd->argv[0], '/'))
	{
		if (access(cmd->argv[0], F_OK) == 0)
			if (access(cmd->argv[0], X_OK) == 0)
				execve(cmd->argv[0], cmd->argv, array_env);
			else
				exit (126);
		else
			exit (127);
		return 0;
	}
	else
	{
		return  0;
	}
}
