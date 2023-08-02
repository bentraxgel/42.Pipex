/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:29:00 by seok              #+#    #+#             */
/*   Updated: 2023/08/02 16:56:37 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	do_fork_pipe(t_info *info)
{
	pid_t	pid;

	pipe(info->fd);
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
	info.ac = ac;
	save_restore_fd(&info, SAVE);
	i = 1;
	if (ft_strncmp(av[i], "here_doc", 9) == 0)
	{
		i++;
		info.limiter = ft_strjoin(av[i], "\n");
		here_doc(&info, av, i, envp);
	}
	else
	{
		info.env = split_environ(envp);
		multiple_pipe(&info, av, i, envp);
	}
	save_restore_fd(&info, RESTORE);
}
