/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:53:10 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/06 20:45:08 by ysong            ###   ########.fr       */
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

void	run_inner_child(t_mini *shell, int *rd_fds)
{
	char	**buff;
	char	**paths;
	char	*path;
	int		i;
	struct stat s;
	
	i = 0;
	// printf("test_all %d\n",i++);
	pipe_process(shell);
	if (!redirect_process(shell, rd_fds))
		exit (1);
	buff = make_buff(shell);
	path = find_path(shell, find_token(shell, COMMAND));
	if (stat(path, &s) == 0)
	{
		if (execve(path, buff, shell->envp) == -1)
			exit(EXIT_FAILURE);
	}
	ft_free(buff);
	ft_free(paths);
	exit(EXIT_SUCCESS);
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
	int status;
	int	old_fds[2];
	int rd_fds[2];

	save_old_fds(old_fds);
	pipe(shell->cmd->fds);
	g_mini.pid = fork();
	if (g_mini.pid == 0)
		run_inner_child(shell, rd_fds);
	else if (g_mini.pid == -1)
		print_error1("fork error", strerror(errno));
	else
	{
		run_inner_parent(shell);
		redirect_close(rd_fds);
		pipe_restore(shell, old_fds);
	}
	// shell->cmd = shell->cmd->next;
	return (1);
}
