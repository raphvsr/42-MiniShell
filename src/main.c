
#include "minishell.h"
#include <stdio.h>

int main(void)
{
	char *str;

	str = readline("minishell>");
	printf("%s", str);
	return (0);
}
