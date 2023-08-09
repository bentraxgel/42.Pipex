/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:29:00 by seok              #+#    #+#             */
/*   Updated: 2023/08/08 21:36:42 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_exit(int this)
{
	if (close(this) == ERROR)
		my_error("close fail");
}

pid_t	do_fork_pipe(t_info *info)
{
	pid_t	pid;

	if (pipe(info->fd) == ERROR)
		my_error("Fail pipe");
	pid = fork();
	if (pid == ERROR)
		my_error("Fail fork");
	return (pid);
}

int	main(int ac, char *av[], char **envp)
{
	int		i;
	t_info	info;

	if (ac < 5)
		my_error("Not enough argument count");
	else if (ac != 5)
		my_error("this program is mandatory pipe");
	info.ac = ac;
	save_restore_fd(&info, SAVE);
	i = 2;
	info.env = split_environ(envp);
	infile_execution(&info, av, i, envp);
	i++;
	outfile_execution(&info, av, i, envp);
	save_restore_fd(&info, RESTORE);
	my_free(info.env);
	i = 0;
	while (i++ < ac - 3)
		wait(NULL);
}
