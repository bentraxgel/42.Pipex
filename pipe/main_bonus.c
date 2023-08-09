/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:29:00 by seok              #+#    #+#             */
/*   Updated: 2023/08/08 22:19:14 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	info.ac = ac;
	save_restore_fd(&info, SAVE);
	i = 1;
	if (ft_strncmp(av[i], "here_doc", 9) == 0)
	{
		i++;
		info.limiter = ft_strjoin(av[i], "\n");
		here_doc(&info, av, i, envp);
		ac--;
	}
	else
		multiple_pipe(&info, av, i, envp);
	save_restore_fd(&info, RESTORE);
	free(info.limiter);
	my_free(info.env);
	i = 0;
	while (i++ < ac - 3)
		wait(NULL);
}
