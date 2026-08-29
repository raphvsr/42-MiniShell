
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


static char *f_cmdpath(char *cmd, t_env *env_list)
{
	t_env *path;
	char **paths_values;
	char *half;
	char *full;
	int i;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = env_find(env_list, "PATH");
	if(!path || !path->value)
		return (NULL);
	paths_values = ft_split(path->value, ':');
	i = -1;
	while (paths_values && paths_values[++i])
	{
		half = ft_strjoin(paths_values[i], "/");
		full = ft_strjoin(half, cmd);
		free(half);
		if (full && access(full, F_OK) == 0)
			return (free_array(paths_values), full);
		free(full);
	}
	return (free_array(paths_values), NULL);
}


static void cprocess(char *cmd_path, t_cmd *cmd, char **array_env)
{
	if (exec_redirs(cmd->redirs) != 0)
		exit(1);
	if (!cmd_path)
		err_exit(cmd->argv[0], ": command not found", 127);
	if (access(cmd_path, F_OK) != 0) // if we cant exec the cmd
	{
		perror(cmd->argv[0]);
		exit(127);
	}
		if (access(cmd_path, X_OK) != 0) // if we cant exec the cmd
	{
		perror(cmd->argv[0]);
		exit(126);
	}
	execve(cmd_path, cmd->argv, array_env);
	perror("minishell: execve");	// if execve succeed everything else is destroyed
	exit (1);						// so it will erase both those lines
}


int exec_cmd(t_cmd *cmd, t_env **env_list)
{
	char	*cmd_path;
	char	**array_env;
	pid_t	pid;
	int 	status;

	cmd_path = f_cmdpath(cmd->argv[0], *env_list);
	array_env = env_to_array(*env_list);
	pid = fork();

	if (pid < 0)
	{
		perror("minishell: fork");
		free(cmd_path);
		return (free_array(array_env), 1);
	}
	if (pid == 0)
		cprocess(cmd_path, cmd, array_env);
	waitpid(pid, &status, 0); // wait for child
	free(cmd_path);
	free_array(array_env);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return 0;
}

int executor(t_cmd **cmd, t_env **env_list)
{
	int status;

	if (!cmd || !*cmd || !(*cmd)->argv || !(*cmd)->argv[0])
		return (0);
	if (heredoc(*cmd) != 0)
		return (1);
	if (is_buildin == 0) // if it was a builtin
	{
		int in = dup(0);
		int out = dup(1);
		if (exec_redirs((*cmd)->redirs) != -1)
			status = 1;
		else
			status = execute_builtin(*cmd, env_list);

	}
	return (status);
	return (exec_cmd(*cmd, env_list));
}
