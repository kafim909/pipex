/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 09:18:33 by mtournay          #+#    #+#             */
/*   Updated: 2021/11/08 10:46:54 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	process_1(t_data *v, char **argv, char **envp)
{
	int	i;

	i = 0;
	dup2(v->fd_1, 0);
	dup2(v->fd_pipe[1], 1);
	close(v->fd_pipe[0]);
	close(v->fd_pipe[1]);
	if (!get_cmd(argv[2], envp, v))
		return (0);
	while ((execve(v->env_tab[i], v->argvec, envp) == -1) && v->env_tab[i])
		i++;
	return (1);
}

int	process_2(t_data *v, char **argv, char **envp)
{
	int	i;

	i = 0;
	dup2(v->fd_pipe[0], 0);
	dup2(v->fd_2, 1);
	close(v->fd_pipe[0]);
	close(v->fd_pipe[1]);
	if (!get_cmd(argv[3], envp, v))
		return (0);
	while ((execve(v->env_tab[i], v->argvec, envp) == -1) && v->env_tab[i])
		i++;
	return (1);
}

void	fd_opening(t_data *v, char **argv)
{
	v->fd_1 = open(argv[1], O_RDWR);
	if (v->fd_1 == -1)
	{
		perror("wrong filename");
		free(v);
		exit(0);
	}
	v->fd_2 = open(argv[4], O_RDWR);
	if (v->fd_2 == -1)
	{
		perror("wrong filename");
		free(v);
		exit(0);
	}	
}

void	init(t_data *v, int argc, char **argv)
{
	if (argc != 5)
	{
		perror("oops, wrong number of arguments");
		free(v);
		exit(0);
	}
	if (pipe(v->fd_pipe) == -1)
	{
		perror("Error in pipe mounting");
		free(v);
		exit(0);
	}
	fd_opening(v, argv);
}

int	main(int argc, char **argv, char *envp[])
{
	t_data	*v;
	int		i;

	v = malloc(sizeof(t_data));
	if (!v)
		return (0);
	i = 0;
	init(v, argc, argv);
	v->pid = fork();
	if (v->pid < 0)
		return (end_process(v));
	if (v->pid == 0)
		if (!process_1(v, argv, envp))
			return (end_process(v));
	v->pid_2 = fork();
	if (v->pid_2 < 0)
		return (end_process(v));
	if (v->pid_2 == 0)
		if (!process_2(v, argv, envp))
			return (end_process(v));
	waitpid(v->pid, NULL, 0);
	end_process(v);
	return (0);
}
