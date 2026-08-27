#include "minishell.h"

// Helper function to create a redirection node
t_redir *create_redir(t_redir_type type, char *file)
{
	t_redir *r = malloc(sizeof(t_redir));
	r->type = type;
	r->file = file;
	r->was_quoted = 0;
	r->heredoc_fd = -1;
	r->next = NULL;
	return r;
}

int main(int ac, char **av, char **envp)
{
	(void)ac; (void)av;
	t_env *env = init_env(envp);

	printf("========================================\n");
	printf("TEST 1: Output Redirection: ls > out.txt\n");
	printf("========================================\n");
	{
		t_cmd cmd;
		char *args[] = {"ls", "-la", NULL};
		cmd.argv = args;
		cmd.redirs = create_redir(REDIR_OUT, "out.txt");
		cmd.next = NULL;
		t_cmd *cmd_ptr = &cmd;
		executor(&cmd_ptr, &env);
		printf("Check out.txt content:\n");
		system("head -n 5 out.txt");
	}

	printf("\n========================================\n");
	printf("TEST 2: Append Redirection: echo 'APPEND' >> out.txt\n");
	printf("========================================\n");
	{
		t_cmd cmd;
		char *args[] = {"echo", "--- APPENDED LINE ---", NULL};
		cmd.argv = args;
		cmd.redirs = create_redir(REDIR_APPEND, "out.txt");
		cmd.next = NULL;
		t_cmd *cmd_ptr = &cmd;
		executor(&cmd_ptr, &env);
		printf("Check tail of out.txt:\n");
		system("tail -n 3 out.txt");
	}

	printf("\n========================================\n");
	printf("TEST 3: Input Redirection: grep 'APPENDED' < out.txt\n");
	printf("========================================\n");
	{
		t_cmd cmd;
		char *args[] = {"grep", "APPENDED", NULL};
		cmd.argv = args;
		cmd.redirs = create_redir(REDIR_IN, "out.txt");
		cmd.next = NULL;
		t_cmd *cmd_ptr = &cmd;
		executor(&cmd_ptr, &env);
	}

	printf("\n========================================\n");
	printf("TEST 4: Heredoc: cat << EOF\n");
	printf("Type lines, then type EOF to finish:\n");
	printf("========================================\n");
	{
		t_cmd cmd;
		char *args[] = {"cat", NULL};
		cmd.argv = args;
		cmd.redirs = create_redir(REDIR_HEREDOC, "EOF");
		cmd.next = NULL;
		t_cmd *cmd_ptr = &cmd;
		executor(&cmd_ptr, &env);
	}

	free_lenv(env);
	return 0;
}
