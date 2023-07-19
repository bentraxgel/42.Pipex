#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(void)
{
	int	fd[2];
	if (pipe(fd) == -1)
		exit(1);

	int	pid1 = fork();
	if (pid1 < 0) //error
	{
		perror("error");
		exit(1);
	}
	/*child process*/
	if (pid1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1); //STDOUT
		close(fd[1]);
		execlp("ls", "ls", NULL);
	}

	int pid2 = fork();
	if (pid2 < 0)
	{
		perror("error");
		exit(1);
	}

	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0); //STDIN
		close(fd[0]);
		execlp("sort", "sort", NULL);
	}
	/*main에 있는 것을 닫아줘야 함*/
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}