/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:52:00 by seok              #+#    #+#             */
/*   Updated: 2023/07/30 16:30:21 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h> //read, write
# include <stdio.h> // BUFSIZ, perror
// # include <string.h> //strerror
# include <sys/errno.h> //errno
# include <stdlib.h> //exit
# include <fcntl.h> //open
# include <stdbool.h>

typedef enum e_fd
{
	READ = 0,
	WRITE
}t_fd;

typedef enum e_prc
{
	ERROR = -1,
	CHILD = 0,
//	Parent
	
}t_prc;

typedef struct s_info
{
	int		stdin_fd;
	int		stdout_fd;
	int		infile_fd;
	int		outfile_fd;
	int 	fd[2];
	int		ac;
	char	*path;
	char	*limiter;
}t_info;

// main.c
char	**split_environ(char **envp);


// execution.c
//void	multiple_pipe(t_info *info, char **av, int i, char **envp);
void	infile_execution(t_info *info, char **av, int idx, char **envp);
void	cmd_execution(t_info *info, char **av, int idx, char **envp);
void	outfile_execution(t_info *info, char **av, int idx, char **envp);
char	*path_access(char **env, char *cmd_options);
char	*str_cmd(char **cmd_options); //TODO 필요한지 체크

// heredoc.c
void	here_doc(t_info *info, char **av, int idx, char **envp);
void	input_heredoc(t_info *info);
void	outfile_heredoc(t_info *info, char **av, int idx, char **envp);
#endif