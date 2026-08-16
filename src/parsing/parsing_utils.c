#include "../../libft/libft.h"
#include "../minishell.h"

int	symbol(char c)
{
	if (c == '\'' || c == '"' || c == '|') // pipe, >>, <<, ...
		return (1);
	return (0);
}
