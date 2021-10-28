/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:53:10 by hkwon             #+#    #+#             */
/*   Updated: 2021/10/28 17:33:33 by ysong            ###   ########.fr       */
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

void	run_inner_child(t_mini *shell)
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

static void	run_inner_parent(t_mini *shell)
{
	int	status;

	wait(&status);
	if (status >> 8 == 255)
		g_mini.exit_status = 255;
	// else if (g_mini.signal_on)
	// 	g_mini.exit_status = status + 128;
	else if (status >> 8 != 0)
		g_mini.exit_status = status >> 8;
	else
		g_mini.exit_status = 0;
}

int	run_inner(t_mini *shell)
{
	g_mini.pid = fork();
	if (g_mini.pid == 0)
		run_inner_child(shell);
	else if (g_mini.pid == -1)
		print_error1("fork error", strerror(errno));
	else
		run_inner_parent(shell);
	return (1);
}
