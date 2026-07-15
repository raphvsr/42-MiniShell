

// cd with only a relative or absolute path

#include "../minishell.h"

int b_cd(char **argv, t_env **env_list)
{
    char old_pwd[PATH_MAX];
    char new_pwd[PATH_MAX];

    if (argv[1] == NULL)
        return (write(STDERR_FILENO, "cd: path is needed\n", 19), 1);
    if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
            return (perror("cd"), 1);
    if (chdir(argv[1]) == -1)
        return (perror("cd"), 1);
    if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
            return (perror("cd"), 1);
    env_set_value(*env_list, "OLDPWD", old_pwd);
    env_set_value(*env_list, "PWD", new_pwd);
    return (0);
}
