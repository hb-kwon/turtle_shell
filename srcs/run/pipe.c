/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 22:33:46 by kwonhyukbae       #+#    #+#             */
/*   Updated: 2021/11/05 04:13:10 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// pipe
#include "minishell.h"

int pipe_process(t_mini *shell)
{
	t_cmd *temp;
	
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

void pipe_restore(t_mini *shell, int *old_fds)
{
	t_cmd * temp;
	
	temp = shell->cmd;
	if (temp->next || temp->prev)
	{
		if (temp->next && !temp->prev)
		{
			close (temp->fds[1]);
		}
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