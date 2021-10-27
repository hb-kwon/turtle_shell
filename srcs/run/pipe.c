/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 22:33:46 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/10/27 15:47:53 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// pipe
#include "minishell.h"

void child_process(t_mini *shell)
{
    int     i;
	t_mini *next_shell;
	t_cmd	*temp_cmd;
	t_cmd	*temp_next_cmd;
	int ret;

	ret = EXIT_SUCCESS;

	temp_cmd = shell->cmd;
	temp_next_cmd = temp_cmd->next;

	if (temp_cmd->pipe_flag == 1)
	{
		dup2(temp_next_cmd->fds[1], STDOUT);
		close(temp_next_cmd->fds[1]);
	}
	if (temp_cmd->fds[0] != 0)
	{
		dup2(temp_cmd->fds[0], STDIN);
		close(temp_cmd->fds[0]);
	}
    i = -1;
    while (++i < BLTIN_NUM)
	{
		if (!ft_strcmp(temp_cmd->token->arg, blt_str(i)))
		{
			run_blt(shell, i);
			break ;
		}
	}
	exit(ret);
}

int pipe_process(t_mini *shell)
{
	pid_t	pid;
	int		status;
	// t_mini *next_shell;
	t_cmd	*temp_cmd;
	t_cmd	*temp_next_cmd;

	temp_cmd = shell->cmd;
	temp_next_cmd = temp_cmd->next;
	if(temp_cmd->pipe_flag == 1)
	{
		temp_next_cmd->pre_flag = 1;
		pipe(temp_next_cmd->fds);
	}
	pid = fork();
	if(pid == 0)
		child_process(shell);
	waitpid(pid, &status, 0);
	if(temp_cmd->pipe_flag == 1)
		close(temp_next_cmd->fds[1]);
	if(temp_cmd->fds[0] != 0)
		close(temp_cmd->fds[0]);
	shell->cmd = shell->cmd->next;
	return 0;
}
