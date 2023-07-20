/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:52:00 by seok              #+#    #+#             */
/*   Updated: 2023/07/20 17:36:01 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h> //read, write
# include <stdio.h> // BUFSIZ, perror
// # include <string.h> //strerror
# include <sys/errno.h> //errno
# include <stdlib.h> //exit
# include <fcntl.h>

typedef enum e_fd
{
	READ = 0,
	WRITE
}t_fd;

#endif