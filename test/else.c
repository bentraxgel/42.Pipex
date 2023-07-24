#include "pipex.h"
void	exec_process(char *cmd[]);

void	leak()
{
	system("leaks -q a.out");
}

void	last(char **cmd)
{
	int outfile_fd = open("outfile", O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(outfile_fd, STDOUT_FILENO);
	// dup2(outfile_fd, fd[READ]);
	execve("/bin/sleep", cmd, 0);
}

int	main()
{
	atexit(leak);
	// int	fd[2];

	// pipe(fd);
	int	in = open("infile", O_RDONLY);
	dup2(in, STDIN_FILENO);
	char *cmd[] = {"sleep", "1000", NULL};
	for (int i = 0; i < 2; i++)
	{
		exec_process(cmd);
	}
	// int	fd[2];

	// pipe(fd);

	// while(1)
	// 	printf("1");
	last(cmd);
	// exit(0);
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
		close(fd[WRITE]);//TODO 닫아!
		execve("/bin/sleep", cmd, 0);
	}
	else
	{
		waitpid(pid, NULL, WNOHANG);
		// wait(NULL);
		close(fd[WRITE]);
		dup2(fd[READ], STDIN_FILENO);
	}
}