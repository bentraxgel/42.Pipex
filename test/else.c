#include "pipex.h"
//TODO 되는것
void	last(char **cmd)
{
	int outfile_fd = open("outfile", O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(outfile_fd, STDOUT_FILENO);
	char *cmd1[] = {"cat", "-e", NULL};
	execve("/bin/cat", cmd, 0);
}

void	exec_process(char *cmd[], int i, char *cmd1[])
{
	pid_t	pid;
	int	fd[2];
	int	status;

	pipe(fd);
	pid = fork();
	printf("[%d] pipe %d %d\n", i, fd[READ], fd[WRITE]);
	if (pid == CHILD)
	{
		close(fd[READ]);
		dup2(fd[WRITE], STDOUT_FILENO);
		if (i == 0)
			execve("/usr/bin/yes", cmd1, 0);
		if (i == 1)
		{
			char *a = "head ";
			char *b = "-3";
			char *cmd2[] = {a, b, NULL};
			execve("/usr/bin/head", cmd2, 0);
		}
		execve("/bin/cat", cmd, 0);
	}
	else
	{
		waitpid(pid, &status, WNOHANG);
		close(fd[WRITE]);
		dup2(fd[READ], STDIN_FILENO);
		close(fd[READ]);
	}

}

int	main()
{
	int	in = open("infile", O_RDONLY);
	dup2(in, STDIN_FILENO);
	char *cmd[] = {"cat", "-e", NULL};
	char *cmd1[] = {"yes", NULL};
	// int	fd[2];

	// pipe(fd);
	for (int i = 0; i < 5; i++)
	{
		printf("while[%d]  ", i);
		exec_process(cmd, i, cmd1);
	}
	// close(fd[READ]);
	// close(fd[WRITE]);
	last(cmd);
}
