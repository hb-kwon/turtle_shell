/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkwon <hkwon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 22:33:46 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/11/11 22:22:18 by hkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_process(t_mini *shell)
{
	t_cmd	*temp;

	temp = shell->cmd;
	if (temp->next || temp->prev)
	{
		if (temp->next && !temp->prev)
		{
			dup2(temp->fds[1], STDOUT_FILENO);
		}
		else if (temp->next && temp->prev)
		{
			dup2(temp->fds[1], STDOUT_FILENO);
			dup2(temp->prev->fds[0], STDIN_FILENO);
		}
		else if (!temp->next && temp->prev)
		{
			dup2(temp->prev->fds[0], STDIN_FILENO);
		}
	}
	return (0);
}

void	pipe_restore(t_mini *shell, int *old_fds)
{
	t_cmd	*temp;

	temp = shell->cmd;
	if (temp->next || temp->prev)
	{
		if (temp->next && !temp->prev)
			close (temp->fds[1]);
		else if (temp->next && temp->prev)
		{
			close(temp->prev->fds[0]);
			close(temp->fds[1]);
		}
		else if (!temp->next && temp->prev)
		{
			dup2(old_fds[1], STDOUT_FILENO);
			close(temp->prev->fds[0]);
		}
		else if (!temp->next && temp->prev)
		{
			dup2(old_fds[1], STDOUT_FILENO);
			close(temp->prev->fds[0]);
			close(temp->fds[1]);
			close(temp->fds[0]);
		}
	}
}

static void	pipe_blt_child(t_mini *shell, int rd_fds[2], int i, char *cmd)
{
	pipe_process(shell);
	if (!redirect_process(shell, rd_fds))
		exit(1);
	(*blt_func(i))(shell);
	if (i == 6 && !check_cmd(cmd))
		print_error_blt(cmd);
	exit(0);
}

void	pipe_blt_run(int i, t_mini *shell)
{
	int		status;
	int		rd_fds[2];
	int		old_fds[2];
	char	*cmd;

	cmd = shell->cmd->token->arg;
	save_old_fds(old_fds);
	pipe(shell->cmd->fds);
	g_mini.pid = fork();
	if (g_mini.pid == 0)
		pipe_blt_child(shell, rd_fds, i, cmd);
	else if (g_mini.pid == -1)
		print_error1("pid", "fork error");
	else
	{
		wait(&status);
		if (status >> 8 != 0)
			g_mini.exit_status = status >> 8;
		redirect_close(rd_fds);
		pipe_restore(shell, old_fds);
	}
}
