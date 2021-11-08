/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:37:57 by mtournay          #+#    #+#             */
/*   Updated: 2021/11/08 10:46:52 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*cat_dup(char *dst, char *src)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(sizeof(char) * (ft_strlen(dst) + ft_strlen(src) + 2));
	if (!ret)
	{
		free(dst);
		return (NULL);
	}
	i = -1;
	j = 0;
	while (dst[++i])
		ret[i] = dst[i];
	ret[i++] = '/';
	while (src[j])
		ret[i++] = src[j++];
	ret[i] = '\0';
	free(dst);
	return (ret);
}

int	get_cmd(char *argv, char **envp, t_data *v)
{
	int	i;

	i = 0;
	v->argvec = ft_split(argv, ' ');
	if (!v->argvec)
		return (0);
	while (envp)
	{
		if (!ft_strncmp("PATH", *envp, 4))
			break ;
		envp++;
	}
	v->env_tab = ft_split(*envp + 5, ':');
	if (!v->env_tab)
		return (0);
	while (v->env_tab[i])
	{
		v->env_tab[i] = cat_dup(v->env_tab[i], v->argvec[0]);
		if (!v->env_tab[i])
			return (0);
		i++;
	}
	return (1);
}

int	end_process(t_data *v)
{
	close(v->fd_1);
	close(v->fd_2);
	close(v->fd_pipe[0]);
	close(v->fd_pipe[1]);
	free(v);
	return (0);
}
