#include "pipex.h"

int	main()
{
	int in = open("infile", O_RDONLY);
	int out = open("outf", O_RDWR | O_CREAT | O_APPEND, 0644);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	char *cmd[] = {"cat", "-e", NULL};
	execve("/bin/cat", cmd, 0);
	write(out, "gate", 4);
}