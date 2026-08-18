

// cd with only a relative or absolute path

#include "minishell.h"

int b_cd(char **argv, t_env **env_list)
{
	char old_pwd[PATH_MAX];
	char new_pwd[PATH_MAX];
	char *target_path;

	if (argv[1] == NULL || ft_strncmp(argv[1], "~", 2) == 0)
	{
		t_env *node = env_find(*env_list, "HOME");
		if (!node || !node->value)
			return (write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28), 1);
		target_path = node->value;
	}
	else
		target_path = argv[1];

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
			return (perror("cd"), 1);

	if (chdir(target_path) == -1)
		return (perror("cd"), 1);

	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
			return (perror("cd"), 1);

	env_set_value(*env_list, "OLDPWD", old_pwd);
	env_set_value(*env_list, "PWD", new_pwd);
	return (0);
}
