/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 10:39:01 by mtournay          #+#    #+#             */
/*   Updated: 2021/11/08 10:39:37 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_data
{
	int		fd_1;
	int		fd_2;
	char	**env_tab;
	char	**argvec;
	char	**envvec;
	int		fd_pipe[2];
	int		pid;
	int		pid_2;

}				t_data;

char	*cat_dup(char *dst, char *src);
int		get_cmd(char *argv, char **envp, t_data *v);
int		end_process(t_data *v);
#endif