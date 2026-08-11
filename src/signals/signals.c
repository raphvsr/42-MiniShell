// TODO

#include <signal.h>

void sigint_handler(int signal)
{
	
}


void init_signals()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
