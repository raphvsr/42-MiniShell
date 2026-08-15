#include "../../minishell.h"


#include "../../../libft/libft.h"

int main()
{
	t_cmd *command;
	char **str;
	char *line;
	int i;

	command = malloc(sizeof(t_cmd *));
	if (!command)
		return (0);

	while (1)
	{
		line = readline("SHELL : ");
		if (!line){
			printf("aie\n");
			break;}

		str = ft_split(line, ' ');
		command->argv = str;
		// printf("%s\n", command.argv[1]);
		


		t_cmd *current;
		int i;
		
		i = 0;
		current = command;
		while (current->argv[i])
		{
			printf("%s\n", current->argv[i]);
			i++;
		}
		// FREE SPLIT
		free(line);
	}
	// 	t_cmd *current;
	// i = 0;
	// 	current = command;
	// 	while (current->argv[i])
	// 	{
	// 		printf("%s\n", current->argv[i]);
	// 		i++;
	// 	}

	// i = 0;
	// while (str[i])
	// {
	// 	printf("%s\n", str[i]);
	// 	i++;
	// }
	// printf("%s\n", *command.argv[2]);   // different
	// printf("%s\n", command.argv[2]);

	free(str);
	return (0);
}

//cc parser.c ../../../libft/ft_split.c -llineline
//echo "nevermind" || grep "never mind"