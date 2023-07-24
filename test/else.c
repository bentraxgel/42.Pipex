#include "pipex.h"
void	exec_process(char *cmd[]);

int	main()
{
	// int	fd[2];

	// pipe(fd);
	int	in = open("infile", O_RDONLY);
	dup2(in, STDIN_FILENO);
	char *cmd[] = {"cat", "-e", NULL};
	for (int i = 0; i < 3; i++)
	{
		exec_process(cmd);
	}
	int	fd[2];

	pipe(fd);
	int outfile_fd = open("outfile", O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(outfile_fd, STDOUT_FILENO);
	execve("/bin/cat", cmd, 0);
}

void	exec_process(char *cmd[])
{
	// printf("%d %d\n", fd[WRITE], fd[READ]);
	pid_t	pid;
	int	fd[2];

	pipe(fd);
	pid = fork();
	if (pid == CHILD)
	{
		close(fd[READ]);
		dup2(fd[WRITE], STDOUT_FILENO);
		execve("/bin/cat", cmd, 0);
	}
	else
	{
		waitpid(pid, NULL, WNOHANG);
		// wait(NULL);
		close(fd[WRITE]);
		dup2(fd[READ], STDIN_FILENO);
	}
}