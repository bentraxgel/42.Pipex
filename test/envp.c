#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

extern char **environ;

int main(int ac, char *av[], char **envp)
{
	char	**new;
	char	command[] = "ls";
	int		i;

	new = (char **)malloc(sizeof(char *) * (ac + 1));
	new[0] = command;

	for (i = 1; i < ac; i++)
		new[i] = av[i];
	new[i] = NULL;
	// new[ac] = NULL;
	if (fork() != 0)
	{
		if (execve("/bin/ls", new, envp) == -1)
		{
			printf("프로그램 실행 에러 : %s\n", strerror(errno));
			return (1);
		}
	// open(execve("/bin/ls", new, 0), O_CREAT);
	}
	printf("출력 안되는 것\n");
	return (0);
}
