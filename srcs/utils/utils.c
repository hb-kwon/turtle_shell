/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysong <ysong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:30:16 by ysong             #+#    #+#             */
/*   Updated: 2021/11/18 20:21:37 by ysong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	turn_on_flag(int *flag, int quote, int idx)
{
	if (*flag & quote)
		*flag ^= quote;
	else
		*flag |= quote;
	idx++;
	return (idx);
}

static int	get_cnt_buff(t_mini *shell)
{
	t_token	*temp;
	int		cnt;

	temp = shell->cmd->token;
	cnt = 0;
	while (temp)
	{
		if (temp->type == COMMAND || temp->type == ARGUMENT)
			cnt++;
		if (temp->next)
			temp = temp->next;
		else
			break ;
	}
	return (cnt);
}

char	**make_buff(t_mini *shell)
{
	t_token	*temp;
	char	**buff;
	int		i;
	int		j;

	i = 0;
	j = get_cnt_buff(shell);
	buff = (char **)malloc(sizeof(char *) * (j + 1));
	if (!buff)
		return (NULL);
	temp = shell->cmd->token;
	while (temp)
	{
		if (temp->type == COMMAND || temp->type == ARGUMENT)
			buff[i++] = temp->arg;
		if (temp->next)
			temp = temp->next;
		else
			break ;
	}
	buff[j] = NULL;
	return (buff);
}

void	save_old_fds(int *old_fds)
{
	old_fds[0] = dup(STDIN_FILENO);
	old_fds[1] = dup(STDOUT_FILENO);
}

void	set_fileno(t_mini *shell, int *fileno)
{
	if (shell->cmd->prev && shell->cmd->prev->pipe_flag && \
		!shell->cmd->next)
		(*fileno)= STDOUT_FILENO;
	else if (shell->cmd->next && !shell->cmd->prev)
		(*fileno)= STDIN_FILENO;
	else if (shell->cmd->next && shell->cmd->prev)
		(*fileno)= shell->cmd->prev->fds[1];
	else
		(*fileno)= STDIN_FILENO;
}
