
// void	here_doc(t_info *info, char **av, int i, char **envp)
// {
// 	char	**env;
// 	char	**cmd_options;

// 	env = split_environ(envp);
// 	while (++i < info->ac - 1)
// 	{
// 		cmd_options = ft_split(av[i], ' ');
// 		info->path = path_access(env, cmd_options[0]);
// 		if (i == 2) //heredoc은 first_e필요없음
// 			first_heredoc(&info, av, i, envp);
// 		else if (i == info->ac - 2)
// 			last_heredoc(&info, av, i, envp);
// 		// heredoc last_e도 따로 처리해야함 APPEND땜시
// 		else
// 			other_execution(&info, av, i, envp);
// 	}
// }

// void	multiple_pipe(t_info *info, char **av, int i, char **envp)
// {
// 	while (++i < ac - 1)
// 	{
// 		// << multipel pipe >>
// 		cmd_options = ft_split(av[i], ' ');
// 		info.path = path_access(env, cmd_options[0]);
// 		// if (i == cmd1) //TODO 2가 아니고 cmd1
// 		if (i == 2) //heredoc은 first_e필요없음
// 			first_execution(&info, av, i, envp);
// 		else if (i == ac - 2)
// 			last_execution(&info, av, i, envp);
// 		else
// 			other_execution(&info, av, i, envp);
// 	}
// }
