#include "pipex.h"

void	last(char **cmd)
{
	int outfile_fd = open("outfile", O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(outfile_fd, STDOUT_FILENO);
	char *cmd1[] = {"ls", NULL};
	execve("/bin/cat", cmd, 0);
}

void	exec_process(char *cmd[])
{
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
		close(fd[WRITE]);
		dup2(fd[READ], STDIN_FILENO);
	}
}

int	main()
{
	int	in = open("infile", O_RDONLY);
	dup2(in, STDIN_FILENO);
	char *cmd[] = {"cat", "-e", NULL};
	int	fd[2];

	pipe(fd);
	for (int i = 0; i < 5; i++)
	{
		exec_process(cmd);
	}
	close(fd[READ]);
	close(fd[WRITE]);
	last(cmd);
}
