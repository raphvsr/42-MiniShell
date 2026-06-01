
#include "minishell.h"
#include <stdio.h>

// int main(void)
// {
// 	char *str;

// 	str = readline("minishell>");
// 	printf("%s", str);
// 	return (0);
// }


// #include "../minishell.h"

// Prototypes for testing (or make sure it's in your minishell.h)
int b_echo(char **args);

int main(void)
{
    // Test Case 1: Simple echo ("echo Hello World")
    char *test1[] = {"echo", "Hello", "World", NULL};
    ft_putstr_fd("--- Test 1 (Standard) ---\n", 1);
    b_echo(test1);

    // Test Case 2: Echo with -n flag ("echo -n No Newline Here")
    char *test2[] = {"echo", "-n", "No", "Newline", "Here", NULL};
    ft_putstr_fd("\n--- Test 2 (-n Flag) ---\n", 1);
    b_echo(test2);
    ft_putstr_fd("[This text should be right next to it if -n worked!]\n", 1);

    // Test Case 3: Echo with multiple -n flags ("echo -n -n -n Multi flags")
    char *test3[] = {"echo", "-n", "-n", "-n", "Multi", "flags", NULL};
    ft_putstr_fd("\n--- Test 3 (Multiple -n) ---\n", 1);
    b_echo(test3);
    ft_putstr_fd("[No newline here either]\n", 1);

    // Test Case 4: Empty echo ("echo")
    char *test4[] = {"echo", NULL};
    ft_putstr_fd("\n--- Test 4 (Empty) ---\n", 1);
    b_echo(test4);

    return (0);
}