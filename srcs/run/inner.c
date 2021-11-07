/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:53:10 by hkwon             #+#    #+#             */
/*   Updated: 2021/11/07 18:27:24 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_inner_child(t_mini *shell, char **buff, int *rd_fds)
{
	char	*path;
	struct stat s;

	pipe_process(shell);
	if (!redirect_process(shell, rd_fds))
		exit (1);
	path = find_path(shell, find_token(shell, COMMAND));
	int i = -1;
	t_mini *temp = shell;
	printf("inner path :%s\n", path);
	while (buff[++i])
	{
		printf("inner buff :%s\n", buff[i]);
		temp->cmd->token = temp->cmd->token->next;
	}
	if (stat(path, &s) == 0)
	{
		if (execve(path, buff, shell->envp) == -1)
			exit(EXIT_FAILURE);
	}
	// ft_free(buff);
	// ft_free(paths);
	exit(EXIT_SUCCESS);
}

static void	run_inner_parent(t_mini *shell, char **buff)
{
	int	status;

	wait(&status);
	if (status >> 8 == 255)
		g_mini.exit_status = 255;
	else if (g_mini.sig_on)
		g_mini.exit_status = status + 128;
	else if (status >> 8 != 0)
		g_mini.exit_status = status >> 8;
	else
		g_mini.exit_status = 0;
	ft_free(buff);
}

int	run_inner(t_mini *shell)
{
	char	**buff;
	int	old_fds[2];
	int rd_fds[2];

	save_old_fds(old_fds);
	buff = make_buff(shell);
	int i = -1;
	while (buff[++i])
		printf("buff[%d] : %s\n", i, buff[i]);
	pipe(shell->cmd->fds);
	g_mini.pid = fork();
	if (g_mini.pid == 0)
		run_inner_child(shell, buff, rd_fds);
	else if (g_mini.pid == -1)
		print_error1("fork error", strerror(errno));
	else
	{
		run_inner_parent(shell, buff);
		redirect_close(rd_fds);
		pipe_restore(shell, old_fds);
	}
	return (1);
}
