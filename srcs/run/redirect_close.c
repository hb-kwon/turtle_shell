/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 02:59:57 by ysong             #+#    #+#             */
/*   Updated: 2021/11/11 03:32:36 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_close(int *rd_fds)
{
	if (rd_fds[0] > 0)
		close(rd_fds[0]);
	if (rd_fds[1] > 0)
		close(rd_fds[1]);
}

void	redirect_restore(int *rd_fds, int *old_fds)
{
	if (rd_fds[0] > 0)
	{
		dup2(old_fds[0], STDIN_FILENO);
		close(rd_fds[0]);
		close(old_fds[0]);
	}
	if (rd_fds[1] > 0)
	{
		dup2(old_fds[1], STDOUT_FILENO);
		close(rd_fds[1]);
		close(old_fds[1]);
	}
}
