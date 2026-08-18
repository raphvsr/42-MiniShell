#include "minishell.h"


t_cmd	*lexer(char *line)
{
	t_cmd	*current; // to remove
	t_cmd	*command;
	char	**str;
	int		i;

	command = malloc(sizeof(t_cmd));
	if (!command)
		return (0);

	// add_history(line);  // better here ?
	str = split_line(line, ' ');
	command->argv = str;

	// printf("%s\n", command.argv[1]);

	i = 0;
	current = command;
	while (current->argv[i])
	{
		printf("%s\n", current->argv[i]);
		i++;
	}

	return (command);
}

// int	main()
// {
// 	t_cmd	*command;
// 	char	*line;

// 	// init_signals();
// 	command = NULL;
// 	while (1)
// 	{
// 		line = readline("p0ubelle> ");
// 		if (!line)
// 		{
// 			printf("exit\n");
// 			break;
// 		}
// 		if (*line) // no need ?
// 		{
// 			add_history(line);
// 			if (!lexer(command, line))
// 				return (0);
// 			// char **args;
// 			// args = ft_split(line, ' ');
// 			// if (command->argv && command->argv[0])
// 			// {
// 			// 	execute_builtin(command->argv, &env);
// 			// }

// 		}
// 		free(line);
// 	}
// 	return 0;
// }

//cc lexer.c ../../../libft/ft_split.c -lreadline
//echo "nevermind" || grep "never mind"
