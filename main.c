/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:29:00 by seok              #+#    #+#             */
/*   Updated: 2023/08/02 13:30:33 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**split_environ(char **envp)
{
	// char	**env;
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) != NULL)
			break;
	}
	envp[i] = ft_strtrim(envp[i], "PATH=");
	// env = ft_split(envp[i], ':');
	return (ft_split(envp[i], ':'));
}
// char	**split_environ(char **envp)
// {
// 	char	**env;
// 	int		i;

// 	i = -1;
// 	while (envp[++i])
// 	{
// 		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) != NULL)
// 			break;
// 	}
// 	envp[i] = ft_strtrim(envp[i], "PATH=");
// 	env = ft_split(envp[i], ':');
// 	return (env);
// }

void	leaks(void) {
	system("leaks pipex");
}

int	main(int ac, char *av[], char **envp)
{
	atexit(leaks);
	int		i;
	t_info	info;

	if (ac < 5)
		my_error("Not enough argument count");
	info.ac = ac;
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
		while (++i < ac - 1)
		{
			/* multipel pipe */
			if (i == 2)
				infile_execution(&info, av, i, envp);
			else if (i == ac - 2)
				outfile_execution(&info, av, i, envp);
			else
				cmd_execution(&info, av, i, envp);
		}
	}
	/* fd 원복 */
}

// void	cmd_execution(int ac, char **av, t_info *info, char **envp)
// {
// 	//여기에 때려넣어?
// }