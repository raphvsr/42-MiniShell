
#include "minishell.h"



int execute_builtin(t_cmd *cmd, t_env **env_list)
{
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		return (b_echo(cmd->argv));
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		return (b_cd(cmd->argv, env_list));
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		return (b_pwd());
   if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
	   return (b_export(cmd->argv, env_list));
	if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		return (b_unset(cmd->argv, env_list));
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (b_env(env_list));
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		return (b_exit(cmd->argv, env_list));
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


int exec_slashcmd(t_cmd *cmd, t_env **env_list)
{
	char	**array_env;
	pid_t	pid;
	int 	status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return 0;
	if (ft_strchr(cmd->argv[0], '/')) // if child process
	{
		array_env = env_to_array(*env_list);
		pid = fork(); // commands delete all memory and replace it so we must create a child (clone) to sacrifice himself
		if (pid < 0)
			return (perror("minishell: fork"), 1);
		if (pid == 0)
			cprocess(cmd, array_env);
		waitpid(pid, &status, 0); // wait for child
		return -1;
	}
	return -1;
}

int exec_cmd(t_cmd *cmd, t_env **env_list)
{
	char	**array_env;
	pid_t	pid;
	int		status;
	t_env	*path;

	path = env_find(*env_list, "PATH");
	if (!path || !path->value)
		return (perror("minishell: path"), -1);
	printf("%s", path->value);
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return -1;

	printf("in command"); // if child process
	array_env = env_to_array(*env_list);
	pid = fork(); // commands delete all memory and replace it so we must create a child (clone) to sacrifice himself
	if (pid < 0)
		return (perror("minishell: fork"), 1);
	if (pid == 0)
		cprocess(cmd, array_env);
	waitpid(pid, &status, 0);
	return 0;

	return -1;
}

int executor(t_cmd **cmd, t_env **env_list)
{

	if (exec_slashcmd(*cmd, env_list) == 0)
		return 0;
	if (execute_builtin(*cmd, env_list) == 0)
		return 0;
	if (exec_cmd(*cmd, env_list) == 0)
		return 0;
	printf("not a builtin or command");
	return 0;
}
