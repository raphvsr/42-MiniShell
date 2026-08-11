// TODO

#include "../minishell.h"

volatile sig_atomic_t g_signal = 0;

void sigint_handler(int signal)
{
	(void)signal;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


void init_signals(void)
{
	signal(SIGINT, sigint_handler);  // for CTRL + C
	signal(SIGQUIT, SIG_IGN);  // for CTRL + \ (SIGN_IGN = signal ignore)
}


void init_child_signals(void)
{
    signal(SIGINT, SIG_DFL); // for child process we put back normal signals
    signal(SIGQUIT, SIG_DFL);
}
