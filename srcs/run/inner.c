/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:53:10 by hkwon             #+#    #+#             */
/*   Updated: 2021/10/20 19:08:09 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

static char	**ft_pipe_path(char *envp[])
{
	int		i;
	char	**paths;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
	}
	return (NULL);
}

void	run_inner(t_mini *shell)
{
	char	**buff;
	char	**paths;
	char	*path;
	char	*path_cmd;
	int		i;

	buff = make_buff(shell);
	paths = ft_pipe_path(shell->envp);
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin(path, buff[0]);
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			if (execve(path_cmd, buff, shell->envp) == -1)
				exit(1);
		}
		free(path);
		free(path_cmd);
	}
	ft_free(buff);
	ft_free(paths);
}
