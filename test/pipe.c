/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:10:54 by seok              #+#    #+#             */
/*   Updated: 2023/07/20 15:28:54 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main()
{
	char buffer[BUFSIZ];
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe error");
		exit(0);
	}

	pid_t	pid;
	pid = fork();

	if (pid == -1)
	{
		perror("fork error");
		exit(0);
	}
	else if (pid == 0) //child process
	{
		write(fd[WRITE], "child write", BUFSIZ);
		// sleep(2);
		// exit(0);
	}
	read(fd[READ], buffer, BUFSIZ);
	printf("perent : %s\n", buffer);
	// printf("he");
	write(fd[WRITE], "letter", BUFSIZ);
	printf("%d %d\n", fd[READ], fd[WRITE]);
	exit(0);
}