/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kumamon <kumamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:29:00 by seok              #+#    #+#             */
/*   Updated: 2023/07/30 13:10:34 by kumamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**split_environ(char **envp)
{
	char	**env;
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) != NULL)
			break;
	}
	envp[i] = ft_strtrim(envp[i], "PATH=");
	env = ft_split(envp[i], ':');
	return (env);
}

int	main(int ac, char *av[], char **envp)
{
	int		i;
	char	**env;
	char	**cmd_options;
	t_info	info;
	char	*path;

	if (ac < 5)
		my_error("Not enough argument count");
	env = split_environ(envp);
	i = 1; //TODO 얘가 cmd1이 될 수 있도록 유도필요.
	if (ft_strncmp(av[i], "here_doc", 9) == 0)
	{
		i++;
		printf("ehre");
		here_doc(&info, av[i]);
		printf("HERE\n");
	}
	// int cmd1 = i;
	// printf("cmd1 = %d", cmd1);
	// exit(0);

	// printf("ac : %d\tav[2] : %s\tav[%d] : %s\n", ac, av[2], ac - 2, av[ac - 2]);
	// cmd_setting
	// cmd_execution(ac, av, &info, envp);
	while (++i < ac - 1)
	{
		cmd_options = ft_split(av[i], ' ');
		path = path_access(env, cmd_options[0]);
		// if (i == cmd1) //TODO 2가 아니고 cmd1
		if (i == 2) //heredoc은 first_e필요없음
			first_execution(&info, av, i, envp, path);
		else if (i == ac - 2)
			last_execution(&info, av, i, envp, path);
		else
			other_execution(&info, av, i, envp, path);
	}
}

// void	cmd_execution(int ac, char **av, t_info *info, char **envp)
// {
// 	//여기에 때려넣어?
// }