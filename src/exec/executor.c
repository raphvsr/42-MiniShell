
#include "minishell.h"



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

static void cprocess(t_cmd *cmd, char **array_env)
{
	if (access(cmd->argv[0], F_OK) != 0) // if we cant find the cmd
	{
		perror(cmd->argv[0]);
		exit(127);
	}
	if (access(cmd->argv[0], X_OK) != 0) // if we cant exec the cmd
	{
		perror(cmd->argv[0]);
		exit(126);
	}
	execve(cmd->argv[0], cmd->argv, array_env);
	perror("execve");	// if execve succeed everything else is destroyed
	exit (1);			// so it will erase both those lines
}


int exec_cmd(t_cmd *cmd, t_env **env_list)
{
	char	**array_env;
	pid_t	pid;
	int 	status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return 0;
	if (ft_strchr(cmd->argv[0], '/'))
	{
		printf("in command"); // if child process
		array_env = env_to_array(*env_list);
		pid = fork(); // commands delete all memory and replace it so we must create a child (clone) to sacrifice himself
		if (pid < 0)
			return (perror("minishell: fork"), 1);
		if (pid == 0)
			cprocess(cmd, array_env);
		waitpid(pid, &status, 0);
		return 0;
	}
	return -1;
}

int executor(char **args, t_env **env_list, t_cmd **cmd)
{
	if (execute_builtin(args, env_list) == 0)
		return 0;
	if (exec_cmd(*cmd, env_list) == 0)
		return 0;
	printf("not a builtin or command");
	return 0;
}
