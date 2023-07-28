/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:52:00 by seok              #+#    #+#             */
/*   Updated: 2023/07/28 21:10:34 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "libft/libft.h"
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
	int	stdin_fd;
	int	stdout_fd;
	int	infile_fd;
	int	outfile_fd;
	int fd[2];
}t_info;

// execution.c
void	here_doc(t_info *info, char *limiter);
void	first_execution(t_info *info, char **av, int idx, char **envp, char *path);
void	other_execution(t_info *info, char **av, int idx, char **envp, char *path);
char	*path_access(char **env, char *cmd_options);
char	*str_cmd(char **cmd_options);
void	last_execution(t_info *info, char **av, int idx, char **envp, char *path);

#endif